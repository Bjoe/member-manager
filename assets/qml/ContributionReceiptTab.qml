import QtQuick 2.1
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {

    RowLayout {
        anchors.fill: parent

        MemberList {
            id: list
            width: 400
            Layout.fillHeight: true

            onSelectedMemberId: {
                contributionReceipt.memberId = id;
            }
        }

        ContributionReceipt {
            Layout.fillHeight: true
            Layout.fillWidth: true

            id: contributionReceipt
        }
    }

    function onRefresh() {
        list.onRefresh();
    }
}
