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

            memberList: handler.memberProxyModel
        }

        MemberDetail {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: view

            member: handler.member
            bankAccount: handler.bankAccount
            contribution: handler.contribution
            balanceListModel: handler.balanceProxyModel
            contributionListModel: handler.contributionProxyModel
        }
    }

    MemberHandler {
        id: handler
    }

    Connections {
        target: list
        onMemberSelected: handler.onMemberSelected(row)
    }

    function onDatabaseReady() {
        handler.onDatabaseReady()
    }
}
