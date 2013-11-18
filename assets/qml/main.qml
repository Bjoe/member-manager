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

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Datei")
            MenuItem {
                action: openFileAction
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

        id: tabView

        enabled: false

        Tab {
            id: membersTab
            title: "Members"

            Item{
                MemberTab {
                    anchors.fill: parent

                    id: activeMember
                }
                Connections {
                    target: mainWindow
                    onRefresh: activeMember.onRefresh()
                }
                Connections {
                    target: membersTab
                    onLoaded: activeMember.onRefresh()
                }
                Connections {
                    target: activeMember
                    onDatabaseChanged: mainWindow.refresh()
                }
            }

        }

        Tab {
            title: qsTr("Spenden Quittung")
            id: contributonReceiptTab

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
                Connections {
                    target: contributonReceiptTab
                    onLoaded: contributionReceipt.onRefresh()
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
                Connections {
                    target: feeDebtTab
                    onLoaded: feeDebt.onRefresh()
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
                Connections {
                    target: cashTab
                    onLoaded: cash.onRefresh()
                }
                Connections {
                    target: cash
                    onDatabaseChanged: mainWindow.refresh()
                }
            }
        }
    }

    function onDatabaseReady() {
        mainWindow.refresh();
        statusBar.message("Database loaded");
        statusBar.progress(1);
        tabView.enabled = true;
    }
}
