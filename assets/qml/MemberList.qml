import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    Layout.minimumWidth: 250

    id: root

    signal selectedMemberId(var id)

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8

        id: mainLayout

        TableView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            id: memberViewList

            model: handler.memberProxyModel
            sortIndicatorVisible: true

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
                width: 120
            }
            TableViewColumn{
                role: "nickname"
                title: qsTr("Nickname")
            }

            onActivated: handler.selectedRow(row);
        }

        RowLayout {
            Button { // TODO is there any TableView.changeSort.... SIGNAL in QML?
                text: qsTr("Sort/Refresh")
                onClicked: refresh();
            }

            CheckBox {
                id: memberState
                text: qsTr("Inactive")
            }
        }
    }

    MemberListHandler {
        id: handler

        onSelectMemberId: root.selectedMemberId(id);

        // handler.memberState -- Member.inactive <--- doesent work :-( Why? FIXME
    }

    function refresh() {
        handler.isInactive = memberState.checked;
        handler.refresh(memberViewList.getColumn(memberViewList.sortIndicatorColumn).role, memberViewList.sortIndicatorOrder);
    }

    function reset() {
        handler.reset();
    }
}
