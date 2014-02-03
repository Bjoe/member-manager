import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0
import membermanager 1.0

Item {
    anchors.fill: parent
    anchors.margins: 8

    id:root

    signal statusMessage(string msg);
    signal progress(double value);

    ColumnLayout {
        anchors.fill: parent
        spacing: 4

        RowLayout {
            Layout.fillWidth: true
            spacing: 4

            Button {
                text: qsTr("Aktualisieren")
                onClicked: handler.refresh()
            }

            Label {
                text: qsTr("Buchungs Info")
            }

            TextField {
                id: accountingInfo
                text: handler.accountingInfo
            }

            Label {
                text: qsTr("Verwendungszweck")
            }

            TextField {
                id: purpose
                text: handler.purpose
            }

            Button {
                text: qsTr("Buchen")
                onClicked: fileDialog.open()
            }
        }

        TableView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: handler.accountingDataList

            TableViewColumn {
                role: "memberId"
                title: qsTr("Mitglieds Nr")
            }

            TableViewColumn {
                role: "firstname"
                title: qsTr("Vorname")
            }

            TableViewColumn {
                role: "name"
                title: qsTr("Name")
            }

            TableViewColumn {
                role: "fee"
                title: qsTr("Beitrag")
            }

            TableViewColumn {
                role: "donation"
                title: qsTr("Spende")
            }

            TableViewColumn {
                role: "additionalFee"
                title: qsTr("CCC Beitrag")
            }

            TableViewColumn {
                role: "additionalDonation"
                title: qsTr("CCC Spende")
            }

            TableViewColumn {
                role: "amortization"
                title: qsTr("Schulden")
            }

            TableViewColumn {
                role: "accountingReference"
                title: qsTr("Rechnungs Nr.")
            }

            TableViewColumn {
                role: "purpose"
                title: qsTr("Verwendunsgszweck")
            }

            TableViewColumn {
                role: "accountingInfo"
                title: qsTr("Buchungs Info")
            }

        }
    }

    FileDialog {
        id: fileDialog
        title: qsTr("Save SEPA and Buchungen")
        onAccepted: handler.book(fileDialog.fileUrl)
        nameFilters: [ "SEPA (*.xml)", "All files (*)" ]
        selectedNameFilter: "SEPA (*.xml)"
    }

    AccountingHandler {
        id: handler

        onStatusMessage: root.statusMessage(message);
        onProgress: root.progress(value);
    }

    function reset() {
        handler.reset();
    }
}
