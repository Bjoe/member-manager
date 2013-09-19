import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import membermanager 1.0

Item {

    GridLayout {
        anchors.fill: parent

        columns: 2

        TableView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: handler.debtModel
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
                role: "email"
                title: qsTr("Email")
            }

            TableViewColumn {
                role: "debit"
                title: qsTr("Beiträge")
            }
        }

        ColumnLayout {
            Layout.fillHeight: true
            CheckBox {
                id: memberState
                text: qsTr("Gelöscht")
            }
            Button {
                text: "Calculate"
                onClicked: handler.onCalculate()
            }
        }
    }

    FeeDebtHandler {
        id: handler
    }

    function onDatabaseReady() {
        handler.onDatabaseReady()
    }
}
