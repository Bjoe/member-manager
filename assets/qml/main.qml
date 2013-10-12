import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: mainWindow
    title: qsTr("Member Mmanager")
    width: 800
    height: 600

    signal qmlSettingsTriggered()
    signal qmlOpenSqlFile(string filename)
    signal refresh()

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

            Item{
                MemberTab {
                    anchors.fill: parent
                    anchors.margins: 8

                    id: activeMember
                    isInactive: false
                }
                Connections {
                    target: mainWindow
                    onRefresh: activeMember.onRefresh()
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

            Item {
                MemberTab {
                    anchors.fill: parent
                    anchors.margins: 8

                    id: inActiveMember
                    isInactive: true
                }
                Connections {
                    target: mainWindow
                    onRefresh: inActiveMember.onRefresh()
                }
            }
        }

        Tab {
            title: "Offene Beiträge"
            id: feeDebtTab

            Item {
                MembersFeeDebt {
                    anchors.fill: parent
                    anchors.margins: 8

                    id: feeDebt
                }
                Connections {
                    target: mainWindow
                    onRefresh: feeDebt.onRefersh()
                }
            }
        }

        Tab {
            title: "Beitrags Buchung"
            id: conrtibutionTab

            Item {
                ContributionTab {
                    anchors.fill: parent
                    anchors.margins: 8

                    id: contribution
                }
                Connections {
                    target: mainWindow
                    onRefresh: contribution.onRefresh()
                }
            }
        }

        Tab {
            title: "Kasse"
            id: cashTab

            Item {
                CashTab {
                    anchors.fill: parent
                    anchors.margins: 8

                    id: cash
                }
                Connections {
                    target: mainWindow
                    onRefresh: cash.onRefresh()
                }
            }
        }
    }

    function onDatabaseReady() {
        console.debug("Database load.")
        mainWindow.refresh();
    }
}
