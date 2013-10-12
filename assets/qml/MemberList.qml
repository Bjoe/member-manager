import QtQuick 2.1
import QtQuick.Controls 1.0
import membermanager 1.0

TableView {
    id: memberViewList

    property alias isInactive: handler.isInactive

    signal selectedMemberId(var id)

    model: handler.memberProxyModel

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
        width: 200
    }
    TableViewColumn{
        role: "nickname"
        title: qsTr("Nickname")
        width: 200
    }

    onActivated: {
        console.debug("Activate row: "+ row)
        handler.onSelectedRow(row);
    }

    MemberListHandler {
        id: handler

        onSelectMemberId: {
            memberViewList.selectedMemberId(id);
        }
    }

    function onRefresh() {
        console.debug("refresh list")
        handler.onRefresh();
    }
}
