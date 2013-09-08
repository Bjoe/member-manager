import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    id: memberDetail

    property Member member

    TabView {
        anchors.fill: memberDetail

        Tab {
            title: qsTr("Daten")

            Item {
                anchors.fill: parent

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 4

                    GroupBox {
                        title: qsTr("Allgemeine Daten")
                        Layout.fillWidth: true

                        GridLayout {
                            columns: 2

                            anchors.fill: parent

                            Text {text: qsTr("Mitgliedsnummer:") }
                            Text {
                                Layout.fillWidth: true
                                text: member.memberId
                            }

                            Text {text: qsTr("Name:") }
                            TextField {
                                Layout.fillWidth: true

                                id: nameField
                                text: member.name
                            }

                            Text {text: qsTr("Vorname:") }
                            TextField {
                                Layout.fillWidth: true

                                id: firstNameField
                                text: member.firstname
                            }

                            Text {text: qsTr("Nickname:") }
                            TextField {
                                Layout.fillWidth: true

                                id: nicknameField
                                text: member.nickname
                            }
                        }
                    }

                    GroupBox {
                        title: qsTr("Adresse")
                        Layout.fillWidth: true

                        GridLayout {
                            columns: 2

                            anchors.fill: parent

                            Text {text: qsTr("Straße:") }
                            TextField {
                                Layout.fillWidth: true

                                id: streetField
                                text: member.street
                            }

                            Text {text: qsTr("Stadt:") }
                            TextField {
                                Layout.fillWidth: true

                                id: cityField
                                text: member.city
                            }

                            Text {text: qsTr("Postleitzahl:") }
                            TextField {
                                Layout.fillWidth: true

                                id: zipcodeField
                                text: member.zipCode
                            }
                        }
                    }

                    GroupBox {
                        title: qsTr("Sonstiges")
                        Layout.fillWidth: true

                        GridLayout {
                            columns: 2

                            anchors.fill: parent

                            Text {text: qsTr("Chaos Nr:") }
                            TextField {
                                Layout.fillWidth: true

                                id: referenceField
                                text: member.reference
                            }

                            Text {text: qsTr("Email:") }
                            TextField {
                                Layout.fillWidth: true

                                id: emailField
                                text: member.email
                            }

                            Text {text: qsTr("Eintritts Datum:") }
                            TextField {
                                Layout.fillWidth: true

                                id: entryDateField
                                text: member.entryDate
                            }

                            Text {text: qsTr("Austritts Datum:") }
                            TextField {
                                Layout.fillWidth: true

                                id: cancelationDateField
                                text: member.cancellationDate
                            }

                            Text {text: qsTr("Gelöscht/Deaktiviert") }
                            CheckBox {
                                Layout.fillWidth: true

                                id: stateField
                                checked: {
                                    if(member.state === Member.inactive)
                                        return true
                                    else
                                        return false
                                }
                            }
                        }
                    }

                    Item {
                        // Only for Spacing. Is there a better way?
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
            }
        }

        Tab {
            title: qsTr("Beitrag")

            Item {
                anchors.fill: parent

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 4

                    GroupBox {
                        title: qsTr("Beiträge")
                        Layout.fillWidth: true

                        GridLayout {
                            columns: 2

                            anchors.fill: parent

                            Text {text: qsTr("Beitrag:") }
                            TextField {
                                Layout.fillWidth: true

                                id: feeField
                                text: ""
                            }

                            Text {text: qsTr("Spende:") }
                            TextField {
                                Layout.fillWidth: true

                                id: donationField
                                text: ""
                            }

                            Text {text: qsTr("CCC Beitrag:") }
                            TextField {
                                Layout.fillWidth: true

                                id: additionalFeeField
                                text: ""
                            }

                            Text {text: qsTr("Info:") }
                            TextField {
                                Layout.fillWidth: true

                                id: contributionInfoField
                                text: ""
                            }

                            Text {text: qsTr("Gültig ab:") }
                            TextField {
                                Layout.fillWidth: true

                                id: validFromField
                                text: ""
                            }
                        }
                    }

                    GroupBox {
                        title: qsTr("Bank Verbindung")
                        Layout.fillWidth: true

                        GridLayout {
                            columns: 2

                            anchors.fill: parent

                            Text {text: qsTr("Einzug") }
                            CheckBox {
                                Layout.fillWidth: true
                                id: contributionStateField

                                checked: {
                                    if(member.collectionState === Member.known)
                                        return true
                                    else
                                        return false
                                }
                            }

                            Text {text: qsTr("Name:") }
                            TextField {
                                Layout.fillWidth: true

                                id: bankNameField
                                text: ""
                            }

                            Text {text: qsTr("Konto Nr.:") }
                            TextField {
                                Layout.fillWidth: true

                                id: accountNrField
                                text: ""
                            }

                            Text {text: qsTr("BLZ:") }
                            TextField {
                                Layout.fillWidth: true

                                id: bankCodeField
                                text: ""
                            }
                        }
                    }


                    Item {
                        // Only for Spacing. Is there a better way?
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
            }
        }

        Tab {
            title: qsTr("Info")

            Item {
                anchors.fill: parent

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 4

                    Text { text: qsTr("Info") }
                    TextField {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        id: infoField

                        text: member.info
                    }
                }
            }
        }
    }
}
