import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    width: 500

    id: root

    property alias isInactive: handler.isInactive

    signal selectedMemberId(var id)

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8

        id: mainLayout

        TableView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            id: memberViewList

            model: handler.memberProxyModel
            sortIndicatorVisible: true

            TableViewColumn{
                role: "memberId"
                title: qsTr("Mitglieds Nr.")
                width: 100
            }

            TableViewColumn{
                role: "name"
                title: qsTr("Name")
                width: 100
            }
            TableViewColumn{
                role: "firstname"
                title: qsTr("First name")
                width: 120
            }
            TableViewColumn{
                role: "nickname"
                title: qsTr("Nickname")
            }

            onActivated: {
                console.debug("Activate row: "+ row)
                handler.onSelectedRow(row);
            }
        }

        Button { // TODO is there any TableView.changeSort.... SIGNAL in QML?
            text: qsTr("Sort/Refresh")
            onClicked: onRefresh();
        }
    }

    MemberListHandler {
        id: handler

        onSelectMemberId: root.selectedMemberId(id);
    }

    function onRefresh() {
        console.debug("refresh list")
        handler.onRefresh(memberViewList.getColumn(memberViewList.sortIndicatorColumn).role, memberViewList.sortIndicatorOrder);
        memberViewList.currentRow = -1;
    }
}
