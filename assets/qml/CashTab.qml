import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import membermanager 1.0

Item {
    id:root
    anchors.fill: parent
    anchors.margins: 8

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        spacing: 4

        RowLayout {
            TableView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                TableViewColumn {
                    role: "valuta"
                    title: qsTr("Valuta")
                }
                TableViewColumn {
                    role: "value"
                    title: qsTr("Betrag")
                }
                TableViewColumn {
                    role: "purpose"
                    title: qsTr("Bezeichnung")
                }

                model: handler.cashProxyModel

                onActivated: {
                    console.debug("Activate row: " + row)
                    handler.onSelectedRow(row)
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true
            title: qsTr("Buchen")

            RowLayout {
                id: rowLayout
                anchors.fill: parent

                MemberList {
                    Layout.fillHeight: true

                    id: list
                }

                GridLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    columns: 5

                    Text { text: qsTr("Valuta") }
                    TextField {
                        readOnly: true
                        text: handler.cashAccount.valuta
                    }

                    Text { text: qsTr("Betrag") }
                    TextField {
                        readOnly: true
                        text: handler.cashAccount.value
                    }

                    Text {
                        Layout.fillWidth: true
                        text: qsTr("Bezeichnung")
                    }

                    Text { text: qsTr("Beitrag") }
                    Text { text: qsTr("Spende") }
                    Text { text: qsTr("CCC Beitrag") }
                    Text { text: qsTr("Gebühr") }

                    TextField {
                        Layout.rowSpan: 4
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        readOnly: true
                        text: handler.cashAccount.purpose
                    }

                    TextField {
                        id: fee
                        text: "0"
                    }
                    TextField {
                        id: donation
                        text: "0"
                    }
                    TextField {
                        id: additional
                        text: "0"
                    }
                    TextField {
                        id: tax
                        text: "0"
                    }

                    Item {
                        Layout.columnSpan: 4
                        Layout.fillHeight: true
                    }

                    Button {
                        Layout.columnSpan: 4
                        text: qsTr("Buchen")

                        onClicked: {
                            persister.cashAccount = handler.cashAccount
                            persister.memberId = memberId
                            persister.fee = fee.text
                            persister.donation = donation.text
                            persister.additional = additional.text
                            persister.tax = tax.text

                            persister.onBooked()
                        }
                    }

                }
            }
        }
    }

    CashImportHandler {
        id: handler
    }

    BalancePersisterHandler {
        id: persister
    }

    MemberHandler {
        id: memberHandler

        onMemberChanged: {
            fee.text = contribution.fee
            donation.text = contribution.donation
            additional.text = contribution.additionalFee + contribution.additionalDonation
            console.debug("Member Changed fee " + contribution.fee)
        }
    }

    Connections {
        target: list
        onSelectedMemberId: memberHandler.onSelectedMemberId(id)
    }

    function onRefresh() {
        list.onRefresh()
        handler.onRefresh()
    }
}
