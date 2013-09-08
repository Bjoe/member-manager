import QtQuick 2.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    property alias isInactive: handler.isInactive
    //property alias memberState: handler.memberState -- Member.inactive <--- doesent work :-( Why? FIXME

    RowLayout {
        id: mainLayout
        anchors.fill: parent

        MemberList {
            id: list
            width: 400
            Layout.fillHeight: true

            memberList: handler.proxyModel
        }

        MemberDetail {
            id: view

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    MemberHandler {
        id: handler

        onMemberChanged: {
            console.debug("Member changed")
            var member = handler.member
            console.debug("Member state: " + handler.memberState)
            console.debug("Member name: " + member.name)
            view.member = member
        }
    }

    Connections {
        target: list
        onMemberSelected: handler.onMemberSelected(row)
    }

    function onDatabaseReady() {
        handler.onDatabaseReady()
    }
}
