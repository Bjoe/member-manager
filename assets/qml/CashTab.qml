import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import membermanager 1.0

Item {

    ColumnLayout {
        anchors.fill: parent

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
                    handler.onCashSelected(row)
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true
            title: qsTr("Buchen")

            GridLayout {
                anchors.fill: parent
                columns: 4

                Text { text: qsTr("Valuta") }
                TextField {
                    readOnly: true
                    text: handler.cashAccount.valuta
                }

                Text { text: qsTr("Betrag") }
                TextField {
                    Layout.fillWidth: true
                    readOnly: true
                    text: handler.cashAccount.value
                }

                Text { text: qsTr("Bezeichnung") }
                TextField {
                    Layout.columnSpan: 3
                    Layout.fillWidth: true
                    readOnly: true
                    text: handler.cashAccount.purpose
                }

                Text { text: qsTr("Mitglied") }
                ComboBox {
                    textRole: "name"
                    model: memberHandler.memberProxyModel
                    onCurrentIndexChanged: {
                        console.debug( currentText + " selected")
                        memberHandler.onMemberSelected(currentIndex)
                    }
                }
                CheckBox {
                    text: qsTr("Gelöscht")
                    Layout.columnSpan: 2
                }

                Text { text: qsTr("Beitrag") }
                Text { text: qsTr("Spende") }
                Text { text: qsTr("CCC Beitrag") }
                Text { text: qsTr("Gebühr") }

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
                    Layout.fillWidth: true
                    id: tax
                    text: "0"
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

    function onDatabaseReady() {
        handler.onDatabaseReady()
    }
}
