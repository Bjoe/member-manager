import QtQuick 2.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    property alias isInactive: list.isInactive
    //property alias memberState: handler.memberState -- Member.inactive <--- doesent work :-( Why? FIXME

    RowLayout {
        id: mainLayout
        anchors.fill: parent

        MemberList {
            id: list
            width: 400
            Layout.fillHeight: true
        }

        MemberDetail {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: view
        }
    }

    Connections {
        target: list
        onSelectedMemberId: view.selectedMemberId(id)
    }

    function onRefresh() {
        list.onRefresh();
    }
}
