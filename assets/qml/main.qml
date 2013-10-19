import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: mainWindow
    title: qsTr("Member Mmanager")
    width: 1024
    height: 748

    signal qmlSettingsTriggered()
    signal qmlOpenSqlFile(string filename)
    signal refresh()

    FileDialog {
        id: fileDialog
        title: qsTr("SQLite File öffnen")
        onAccepted: {
            statusBar.progress(0.1);
            mainWindow.qmlOpenSqlFile(fileDialog.fileUrl);
        }
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

    statusBar: StatusBar {
            id: statusBar

            RowLayout {
                ProgressBar {
                    id: statusBarProgress
                }
                Label {
                    id: statusBarMessage
                }
            }

            function message(msg) {
                statusBarMessage.text = msg;
            }

            function progress(value) {
                if(value === 0) {
                    statusBarProgress.value = value;
                } else {
                    statusBarProgress.value += value;
                }
            }
        }

    TabView {
        anchors.fill: parent
        anchors.margins: 2

        Tab {
            id: members
            title: "Members"

            Item{
                MemberTab {
                    anchors.fill: parent

                    id: activeMember
                    isInactive: false
                }
                Connections {
                    target: mainWindow
                    onRefresh: activeMember.onRefresh()
                }
                Connections {
                    target: activeMember
                    onDatabaseChanged: mainWindow.refresh()
                }
            }

        }

        Tab {
            title: "Inactive Members"
            id: inactiveMembers

            Item {
                MemberTab {
                    anchors.fill: parent

                    id: inActiveMember
                    isInactive: true
                }
                Connections {
                    target: mainWindow
                    onRefresh: inActiveMember.onRefresh()
                }
                Connections {
                    target: inActiveMember
                    onDatabaseChanged: mainWindow.refresh()
                }
            }
        }

        Tab {
            title: qsTr("Spenden Quittung")

            Item {
                ContributionReceiptTab {
                    anchors.fill: parent

                    id: contributionReceipt

                    onStatusMessage: statusBar.message(msg);
                    onProgress: statusBar.progress(value);
                }
                Connections {
                    target: mainWindow
                    onRefresh: contributionReceipt.onRefresh()
                }
            }
        }

        Tab {
            title: "Offene Beiträge"
            id: feeDebtTab

            Item {
                MembersFeeDebt {
                    anchors.fill: parent

                    id: feeDebt

                    onStatusMessage: statusBar.message(msg);
                    onProgress: statusBar.progress(value);
                }
                Connections {
                    target: mainWindow
                    onRefresh: feeDebt.onRefresh()
                }
            }
        }

        Tab {
            title: "Beitrags Buchung"
            id: conrtibutionTab

            Item {
                ContributionTab {
                    anchors.fill: parent

                    id: contribution

                    onStatusMessage: statusBar.message(msg);
                    onProgress: statusBar.progress(value);
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

                    id: cash

                    onStatusMessage: statusBar.message(msg);
                    onProgress: statusBar.progress(value);
                }
                Connections {
                    target: mainWindow
                    onRefresh: cash.onRefresh()
                }
            }
        }
    }

    function onDatabaseReady() {
        mainWindow.refresh();
        statusBar.message("Databese loaded");
        statusBar.progress(1);
    }
}
