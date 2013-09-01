import QtQuick 2.1
import QtQuick.Controls 1.0

Item {
    id: memberViewMain

    signal memberSelected(int row)
    property alias memberList: memberViewList.model

    TableView {
        id: memberViewList
        anchors.fill: memberViewMain

        TableViewColumn{
            role: "memberId"
            title: "Mitglieds Nr."
            width: 100
        }

        TableViewColumn{
            role: "name"
            title: "Name"
            width: 100
        }
        TableViewColumn{
            role: "firstname"
            title: "First name"
            width: 200
        }
        TableViewColumn{
            role: "nickname"
            title: "Nickname"
            width: 200
        }

        onActivated: {
            console.debug("Activate row: "+ row)
            memberSelected(row)
        }
    }
}
