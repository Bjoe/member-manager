import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
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
                text: "Calculate"
                onClicked: handler.onCalculate()
            }
            CheckBox {
                id: memberState
                text: qsTr("Gelöscht")
            }
        }

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
    }

    FeeDebtHandler {
        id: handler

        onStatusMessage: root.statusMessage(message);
        onProgress: root.progress(value);
    }

    function onRefresh() {
        handler.onRefresh()
    }
}
