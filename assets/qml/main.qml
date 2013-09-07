import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0

ApplicationWindow {
    id: mainWindow
    title: qsTr("Member Mmanager")
    width: 800
    height: 600

    signal qmlSettingsTriggered()
    signal qmlOpenSqlFile(string filename)
    signal databaseReady()

    FileDialog {
        id: fileDialog
        title: qsTr("SQLite File öffnen")
        onAccepted: mainWindow.qmlOpenSqlFile(fileDialog.fileUrl)
    }

    Action {
        id: openFileAction
        text: qsTr("Open File")
        tooltip: qsTr("Öffne SQLite Datei")
        onTriggered: fileDialog.open()
    }

    Action {
        id: openDbAction
        text: qsTr("Open DB")
        tooltip: qsTr("Öffne Datenbank")
    }

    Action {
        id: openSettings
        text: qsTr("Settings")
        tooltip: qsTr("Öffne Einstellungen")
        onTriggered: mainWindow.qmlSettingsTriggered()
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Datei")
            MenuItem {
                action: openFileAction
            }

            MenuItem {
                action: openDbAction
            }

            MenuSeparator {
            }

            MenuItem {
                action: openSettings
            }

            MenuSeparator {
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit()
            }
        }
    }

    TabView {
        anchors.fill: parent

        Tab {
            id: members
            title: "Members"

            onStatusChanged: {
                if (members.status == Loader.Ready) {
                    console.debug('Members Tab Loaded')
                }
            }

            RowLayout {
                id: mainLayout
                anchors.fill: parent
                anchors.margins: 8

                MemberList {
                    id: activeMemberList
                    width: 400
                    Layout.fillHeight: true

                    memberList: activeMemberHandler.proxyModel
                }

                MemberDetail {
                    id: activeMemberDetailView

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                MemberHandler {
                    id: activeMemberHandler

                    onMemberChanged: {
                        console.debug("Member changed")
                        var member = activeMemberHandler.member
                        console.debug("Member state: " + activeMemberHandler.memberState)
                        console.debug("Member name: " + member.name)
                        activeMemberDetailView.name = member.name
                    }
                }

                Connections {
                    target: mainWindow
                    onDatabaseReady: activeMemberHandler.onDatabaseReady()
                }

                Connections {
                    target: activeMemberList
                    onMemberSelected: activeMemberHandler.onMemberSelected(row)
                }
            }
        }

        Tab {
            title: "Inactive Members"
            id: inactiveMembers

            onStatusChanged: {
                if (members.status == Loader.Ready) {
                    console.debug('Inactive Members Tab Loaded')
                }
            }

            RowLayout {
                id: inactiveMembersLayout
                anchors.fill: parent
                anchors.margins: 8

                MemberList {
                    id: inacitveMemberList
                    width: 400
                    Layout.fillHeight: true

                    memberList: inactiveMemberHandler.proxyModel
                }


                MemberDetail {
                    id: inactiveMembersView

                    width: 400
                    Layout.fillHeight: true
                }

                MemberHandler {
                    id: inactiveMemberHandler
                    // memberState: Member.inactive <--- doesent work :-( Why? FIXME
                    isInactive: true

                    onMemberChanged: {
                        console.debug("Member changed")
                        var member = inactiveMemberHandler.member
                        console.debug("Member state: " + inactiveMemberHandler.memberState)
                        console.debug("Member name: " + member.name)
                        inactiveMembersView.name = member.name
                    }
                }

                Connections {
                    target: mainWindow
                    onDatabaseReady: inactiveMemberHandler.onDatabaseReady()
                }

                Connections {
                    target: inacitveMemberList
                    onMemberSelected: inactiveMemberHandler.onMemberSelected(row)
                }
            }
        }
    }

    function onDatabaseReady() {
        console.debug("Database load.")
        mainWindow.databaseReady();
    }
}
