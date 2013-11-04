import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0
import membermanager 1.0

Item {

    id:root

    signal statusMessage(string msg);
    signal progress(double value);
    signal databaseChanged();

    property var selectedYear;
    property bool activateBookButton;

    SplitView {
        orientation: Qt.Vertical
        anchors.fill: parent

        id: mainLayout

        GroupBox { // TODO This is a quick fix, I dont understand SplitView or Layout managemend in QML
            title: "."
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent
                RowLayout {
                    Text { text: qsTr("Jahr") }
                    ComboBox { // TODO is there any Calendar Controls in QML?
                        id: year
                        model: ListModel {
                            id: yearList
                            Component.onCompleted: {
                                var year = 2013; // TODO Date().toLocaleString("dd.MM.yyyy");
                                root.selectedYear = year;
                                console.debug("Jahr", year)
                                for (var i = 0 ; i < 13 ; ++i) {
                                    append({"year": year - i})
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

                    onActivated: {
                        console.debug("Activate row: " + row)
                        handler.onSelectedRow(row)
                        root.activateBooking();
                    }
                }
            }

        }

        GroupBox {
            title: qsTr("Buchen")

            SplitView {
                anchors.fill: parent
                orientation: Qt.Horizontal

                id: rowLayout

                GroupBox { // TODO This is a quick fix, I dont understand SplitView or Layout managemend in QML
                    title: "."
                    Layout.minimumWidth: 300

                    MemberList {
                        anchors.fill: parent
                        id: list
                    }
                }

                GroupBox {  // TODO This is a quick fix, I dont understand SplitView or Layout managemend in QML
                    title: "."
                    Layout.minimumWidth: 20

                    GridLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        columns: 5

                        Text { text: qsTr("Valuta") }
                        DateField {
                            readOnly: true
                            value: handler.cashAccount.valuta
                        }

                        Text { text: qsTr("Betrag") }
                        AmountField {
                            readOnly: true
                            value: handler.cashAccount.value
                        }

                        Text {
                            Layout.fillWidth: true
                            text: qsTr("Bezeichnung")
                        }

                        Text { text: qsTr("Beitrag") }
                        Text { text: qsTr("Spende") }
                        Text { text: qsTr("CCC Beitrag") }
                        Text { text: qsTr("CCC Spende") }

                        TextArea {
                            Layout.rowSpan: 5
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            readOnly: true
                            text: handler.cashAccount.purpose
                        }

                        AmountField {
                            id: fee
                            value: 0
                        }
                        AmountField {
                            id: donation
                            value: 0
                        }
                        AmountField {
                            id: additional
                            value: 0
                        }
                        AmountField {
                            id: additionalDonation
                            value: 0
                        }

                        Text { text: qsTr("Gebühr") }
                        AmountField {
                            id: tax
                            value: 0
                        }
                        Item {
                            Layout.columnSpan: 3
                            Layout.fillHeight: true
                        }

                        Item {
                            Layout.columnSpan: 4
                            Layout.fillHeight: true
                        }

                        Button {
                            id: bookButton

                            Layout.columnSpan: 4
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
                                    persister.memberId = memberHandler.member.memberId;
                                    persister.fee = fee.readValue();
                                    persister.donation = donation.readValue();
                                    persister.additional = additional.readValue();
                                    persister.additionalDonation = additionalDonation.readValue();
                                    persister.tax = tax.readValue();

                                    persister.onBooked();
                                    root.databaseChanged();
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

        onMemberChanged: {
            tax.value = 0;
            fee.value = 0;
            donation.value = 0;
            additional.value = 0;
            additionalDonation.value = 0;

            fee.value = contribution.fee;
            donation.value = contribution.donation;
            additional.value = contribution.additionalFee;
            additionalDonation.value = contribution.additionalDonation;

            console.debug("Changed to member id: " + memberHandler.member.memberId);
            root.activateBooking();
        }
    }

    Connections {
        target: list
        onSelectedMemberId: memberHandler.onSelectedMemberId(id)
    }

    function onRefresh() {
        list.onRefresh()
        handler.onRefresh()
        cashTable.currentRow = -1;
        bookButton.enabled = false;
        root.activateBookButton = false;
    }

    function activateBooking() {
        bookButton.enabled = (true & root.activateBookButton);
        root.activateBookButton = true;
    }
}
