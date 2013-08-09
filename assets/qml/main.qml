import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.0

ApplicationWindow {
    id: mainWindow
    title: qsTr("Member Mmanager")
    width: 640
    height: 480

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
}
