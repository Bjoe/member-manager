import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import membermanager 1.0

Item {

    id:root

    property int memberId

    signal statusMessage(string msg);
    signal progress(double value);

    ColumnLayout {
        anchors.margins: 8
        anchors.fill: parent
        spacing: 4

        RowLayout {
            Text { text: qsTr("Quittung") }

            ComboBox { // TODO is there any Calendar Controls in QML?
                id: year
                model: ListModel {
                    id: yearList
                    Component.onCompleted: {
                        var year = 2013; // TODO Date().toLocaleString("dd.MM.yyyy");
                        console.debug("Jahr", year)
                        for (var i = 0 ; i < 8 ; ++i) {
                            append({"year": year - i})
                        }
                    }
                }

                onCurrentIndexChanged: root.onChanged();
            }

            Button {
                id: saveButton
                text: qsTr("Save")

                onClicked: {
                    fileDialog.open()
                }
            }
        }
        TableView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            id: balanceTable

            TableViewColumn {
                role: "account"
                title: qsTr("Buchung")
            }
            TableViewColumn {
                role: "valuta"
                title: qsTr("Datum")
            }
            TableViewColumn {
                role: "value"
                title: qsTr("Betrag")
            }
            TableViewColumn {
                role: "purpose"
                title: qsTr("Bezeichnung")
            }

            model: receipt.balanceList

            MouseArea {
                anchors.fill: parent

                acceptedButtons: Qt.RightButton

                onClicked: mymenu.popup()
            }
        }
        RowLayout {
            Text {
                text: qsTr("Summe")
            }
            TextField {
                readOnly: true
                text: receipt.sum
            }
        }
    }

    ContributionReceiptHandler {
        id: receipt

        onStatusMessage: root.statusMessage(message);
        onProgress: root.progress(value);
    }

    function onChanged() {
        var index = year.currentIndex;
        var yearText = yearList.get(index).year;
        receipt.createReceipt(memberId, yearText);
    }

    Menu {
        id: mymenu
        title: "Context Menu"

        MenuItem {
            text: qsTr("Remove selection")

            onTriggered: {
                receipt.removeRow(balanceTable.currentRow)
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: qsTr("Read tex file")
        onAccepted: receipt.saveReceipt(memberId, fileDialog.folder, fileDialog.fileUrl, year.currentText)
        nameFilters: [ "LaTex (*.tex)", "All files (*)" ]
        selectedNameFilter: "LaTex (*.tex)"
    }
}
