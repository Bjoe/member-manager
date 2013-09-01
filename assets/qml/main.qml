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
    }

    MemberHandler {
        id: memberHandler

        onMemberChanged: {
            console.debug("Member changed")
            var member = memberHandler.member
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

    function onDatabaseReady() {
        console.debug("Database load.")
        memberHandler.onDatabaseReady();
    }
}
