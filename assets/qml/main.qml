import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    id: mainWindow
    title: qsTr("Membermanager")
    width: 640
    height: 480

    signal qmlSettingsTriggered()

    menuBar: MenuBar {
        Menu {
            title: qsTr("Datei")
            MenuItem {
                text: qsTr("Open File")
            }

            MenuItem {
                text: qsTr("Open DB")
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Settings")
                onTriggered: mainWindow.qmlSettingsTriggered();
            }

            MenuSeparator {}

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

}
