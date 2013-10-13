import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    anchors.fill: parent
    anchors.margins: 8

    property alias isInactive: list.isInactive
    //property alias memberState: handler.memberState -- Member.inactive <--- doesent work :-( Why? FIXME

    id:root

    SplitView {
        anchors.fill: parent

        id: mainLayout

        MemberList {
            Layout.fillHeight: true

            id: list
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
