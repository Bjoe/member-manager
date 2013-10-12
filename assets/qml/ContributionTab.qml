import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0
import membermanager 1.0

Item {
    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            Button {
                text: qsTr("Aktualisieren")
                onClicked: onRefresh()
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
        title: qsTr("Save DTAUS and Buchungen")
        onAccepted: handler.book(fileDialog.fileUrl)
    }

    AccountingHandler {
        id: handler
    }

    function onRefresh() {
        handler.accountingInfo = accountingInfo.text
        handler.purpose = purpose.text
        handler.onRefresh()
    }
}
