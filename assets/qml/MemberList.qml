import QtQuick 2.1
import QtQuick.Controls 1.0

TableView {
    id: memberViewList

    signal memberSelected(int row)
    property alias memberList: memberViewList.model

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
        memberSelected(row)
    }
}
