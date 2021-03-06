import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    anchors.fill: parent
    anchors.margins: 8

    id:root

    SplitView {
        anchors.fill: parent

        id: mainLayout

        MemberList {
            Layout.fillHeight: true

            id: list

            onSelectedMemberId: view.selectedMemberId(id)
        }

        MemberDetail {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 400
            Layout.minimumHeight: 750

            id: view

            onRefresh: list.refresh();
        }
    }

    function reset() {
        list.reset();
        view.reset();
    }
}
