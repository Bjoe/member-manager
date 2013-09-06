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
                    console.log('Members Tab Loaded')
                }
            }

            RowLayout {
                id: mainLayout
                anchors.fill: parent
                anchors.margins: 8

                Item {
                    id: placeholder
                    width: 400
                    Layout.fillHeight: true
                    MemberView {
                        anchors.fill: parent
                        //anchors.margins: 8
                        //enabled: false
                    }
                }

                MemberDetail {
                    id: detailView

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    //anchors.fill: parent
                    //anchors.margins: 8

                }

                MemberHandler {
                    id: memberHandler

                    onMemberChanged: {
                        console.debug("Member changed")
                        var member = memberHandler.member
                        console.debug("Member state: " + memberHandler.memberState)
                        console.debug("Member name: " + member.name)
                        detailView.name = member.name
                    }

                    onProxyModelChanged: {
                        console.debug("Model reloaded")
                        placeholder.children[0].destroy()
                        var component = Qt.createComponent("MemberView.qml")
                        var memberView = component.createObject(placeholder, { "anchors.fill": placeholder})
                        memberView.memberList = memberHandler.proxyModel
                        memberView.memberSelected.connect(memberHandler.onMemberSelected)
                    }
                }

                Connections {
                    target: mainWindow
                    onDatabaseReady: memberHandler.onDatabaseReady()
                }
            }
        }

        Tab {
            title: "Inactive Members"
            id: inactiveMembers

            onStatusChanged: {
                if (members.status == Loader.Ready) {
                    console.log('Inactive Members Tab Loaded')
                }
            }

            RowLayout {
                id: inactiveMembersLayout
                anchors.fill: parent
                anchors.margins: 8

                Item {
                    id: inactiveMembersPlaceholder
                    width: 400
                    Layout.fillHeight: true
                    MemberView {
                        anchors.fill: parent
                        //anchors.margins: 8
                        //enabled: false
                    }
                }

                MemberDetail {
                    id: inactiveMembersView

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    //anchors.fill: parent
                    //anchors.margins: 8

                }

                MemberHandler {
                    id: inactiveMemberHandler
                    // memberState: Member.inactive <--- doesent work :-(
                    isInactive: true

                    onMemberChanged: {
                        console.debug("Member changed")
                        var member = inactiveMemberHandler.member
                        console.debug("Member state: " + inactiveMemberHandler.memberState)
                        console.debug("Member name: " + member.name)
                        inactiveMembersView.name = member.name
                    }

                    onProxyModelChanged: {
                        console.debug("Model reloaded")
                        inactiveMembersPlaceholder.children[0].destroy()
                        var component = Qt.createComponent("MemberView.qml")
                        var memberView = component.createObject(inactiveMembersPlaceholder, { "anchors.fill": inactiveMembersPlaceholder})
                        memberView.memberList = inactiveMemberHandler.proxyModel
                        memberView.memberSelected.connect(inactiveMemberHandler.onMemberSelected)
                    }
                }

                Connections {
                    target: mainWindow
                    onDatabaseReady: inactiveMemberHandler.onDatabaseReady()
                }
            }
        }
    }

    function onDatabaseReady() {
        console.debug("Database load.")
        mainWindow.databaseReady();
    }
}
