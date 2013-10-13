import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    anchors.fill: parent
    anchors.margins: 8

    id:root

    SplitView {
        anchors.fill: parent

        MemberList {
            Layout.fillHeight: true

            id: list

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
