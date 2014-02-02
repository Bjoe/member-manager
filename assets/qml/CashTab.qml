import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0
import membermanager 1.0

Item {

    id:root

    signal statusMessage(string msg);
    signal progress(double value);

    property var selectedYear;

    SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical

        id: mainLayout

        GroupBox {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 150

            id: cashGroup
            title: qsTr("Konto")

            ColumnLayout {
                anchors.fill: parent
                RowLayout {
                    Text { text: qsTr("Jahr") }
                    ComboBox { // TODO is there any Calendar Controls in QML?
                        id: year
                        model: ListModel {
                            id: yearList
                            Component.onCompleted: {
                                var year = 2014; // TODO Date().toLocaleString("dd.MM.yyyy");
                                root.selectedYear = year;
                                console.debug("Jahr", year)
                                for (var i = 0 ; i < 13 ; ++i) {
                                    append({"year": year - i, "text": year - i})
                                }
                            }
                        }
                        onCurrentIndexChanged: {
                            var element = yearList.get(currentIndex);
                            console.debug("Selected year", element.year);
                            root.selectedYear = element.year;
                            handler.selectYear(root.selectedYear);
                        }
                    }

                    Button {
                        id: importButton
                        text: qsTr("Import SWIFT")

                        onClicked: fileDialog.open();
                    }
                }

                TableView {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    id: cashTable

                    TableViewColumn {
                        role: "valuta"
                        title: qsTr("Valuta")
                    }

                    TableViewColumn {
                        role: "value"
                        title: qsTr("Betrag")
                    }

                    TableViewColumn {
                        role: "transactionText"
                        title: qsTr("Transaktion Typ")
                    }

                    TableViewColumn {
                        role: "remoteName"
                        title: qsTr("Name")
                    }

                    TableViewColumn {
                        role: "purpose"
                        title: qsTr("Bezeichnung")
                    }

                    TableViewColumn {
                        role: "state"
                        title: qsTr("Status")
                    }

                    TableViewColumn {
                        role: "memberId"
                        title: qsTr("Mitglieder Nr")
                    }

                    model: handler.cashProxyModel

                    onActivated: handler.onSelectedRow(row)
                }
            }

        }

        GroupBox {
            Layout.fillWidth: true
            Layout.minimumHeight: 400

            id: bookGroup
            title: qsTr("Buchen")

            SplitView {
                anchors.fill: parent
                orientation: Qt.Horizontal

                id: rowLayout

                MemberList {
                    id: list

                    onSelectedMemberId: memberHandler.onSelectedMemberId(id);
                }

                Item {
                    Layout.minimumWidth: 400

                    GridLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        columns: 3

                        Text {
                            Layout.columnSpan: 2
                            text: qsTr("Transactions Daten")
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("Bezeichnung")
                        }

                        Text { text: qsTr("Valuta") }
                        DateField {
                            readOnly: true
                            value: handler.cashAccount.valuta
                        }

                        TextArea {
                            Layout.rowSpan: 9
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            readOnly: true
                            text: handler.cashAccount.purpose
                        }


                        Text { text: qsTr("Betrag") }
                        AmountField {
                            readOnly: true
                            value: handler.cashAccount.value
                        }

                        Text {
                            Layout.columnSpan: 2
                            text: qsTr("Mitglieds Daten")
                        }

                        Text { text: qsTr("MitgliedsNr") }
                        TextField {
                            id: memberId
                            text: memberHandler.member.memberId
                        }

                        Text { text: qsTr("Beitrag") }
                        AmountField {
                            id: fee
                            value: memberHandler.contribution.fee
                        }

                        Text { text: qsTr("Spende") }
                        AmountField {
                            id: donation
                            value: memberHandler.contribution.donation
                        }

                        Text { text: qsTr("CCC Beitrag") }
                        AmountField {
                            id: additional
                            value: memberHandler.contribution.additionalFee
                        }

                        Text { text: qsTr("CCC Spende") }
                        AmountField {
                            id: additionalDonation
                            value: memberHandler.contribution.additionalDonation
                        }


                        Text { text: qsTr("Gebühr/Sonstiges") }
                        AmountField {
                            id: tax
                            value: 0
                        }

                        Item {
                            Layout.fillHeight: true
                            Layout.columnSpan: 2
                        }

                        Button {
                            Layout.columnSpan: 2

                            id: bookButton

                            text: qsTr("Buchen")

                            onClicked: {
                                var sum = Number(0.0);
                                sum += Number(fee.readValue());
                                sum += Number(donation.readValue());
                                sum += Number(additional.readValue());
                                sum += Number(additionalDonation.readValue());
                                sum += Number(tax.readValue());

                                console.debug("Summe " + sum + " Betrag " + handler.cashAccount.value);
                                if(sum === handler.cashAccount.value) {
                                    fee.textColor = "black";
                                    donation.textColor = "black";
                                    additional.textColor = "black";
                                    additionalDonation.textColor = "black";
                                    tax.textColor = "black";

                                    persister.cashAccount = handler.cashAccount;
                                    persister.memberId = memberId.text;
                                    persister.fee = fee.readValue();
                                    persister.donation = donation.readValue();
                                    persister.additional = additional.readValue();
                                    persister.additionalDonation = additionalDonation.readValue();
                                    persister.tax = tax.readValue();

                                    persister.onBooked();
                                    onRefresh();
                                } else {
                                    fee.textColor = "red";
                                    donation.textColor = "red";
                                    additional.textColor = "red";
                                    additionalDonation.textColor = "red";
                                    tax.textColor = "red";
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: qsTr("Read SWIFT file")
        onAccepted: handler.onImport(fileDialog.fileUrl);
        nameFilters: [ "MT940 (*.txt)", "All files (*)" ]
        selectedNameFilter: "MT940 (*.txt)"
    }

    CashImportHandler {
        id: handler

        onStatusMessage: root.statusMessage(message);
        onProgress: root.progress(value);
        onCashAccountModelChanged: handler.selectYear(root.selectedYear);
    }

    BalancePersistHandler {
        id: persister
    }

    MemberHandler {
        id: memberHandler
    }

    function onRefresh() {
        list.onRefresh();

        var row = cashTable.currentRow;
        handler.onRefresh();
        if(row > -1) {
            cashTable.selection.select(row);
        }
        cashTable.currentRow = row;
    }
}
