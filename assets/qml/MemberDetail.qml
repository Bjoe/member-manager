import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    property alias member: handler.member
    property alias contribution: handler.contribution
    property alias bankAccount: handler.bankAccount
    property alias balanceListModel: handler.balanceProxyModel
    property alias contributionListModel: handler.contributionProxyModel

    property bool valid;

    signal read()
    signal newMember()
    signal saveMember()
    signal clear()

    id: memberDetail

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 4

        TabView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Tab {
                title: qsTr("Daten")

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 8
                    spacing: 4

                    id: dataTab

                    GroupBox {
                        Layout.fillWidth: true

                        title: qsTr("Allgemeine Daten")

                        GridLayout {
                            anchors.fill: parent
                            anchors.margins: 8

                            columns: 2

                            Text {text: qsTr("Mitgliedsnummer:") }
                            TextField {
                                Layout.fillWidth: true

                                id: memberIdField
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
                            anchors.fill: parent
                            anchors.margins: 8

                            columns: 2

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
                            anchors.fill: parent
                            anchors.margins: 8

                            columns: 2

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
                            DateField {
                                Layout.fillWidth: true

                                id: entryDateField
                                value: member.entryDate
                            }

                            Text {text: qsTr("Austritts Datum:") }
                            DateField {
                                Layout.fillWidth: true

                                id: cancelationDateField
                                value: member.cancellationDate
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

                    function onRead() {
                        console.debug("Read");

                        member.memberId = memberIdField.text
                        member.name = nameField.text;
                        member.firstname = firstNameField.text
                        member.nickname = nicknameField.text
                        member.street = streetField.text
                        member.city = cityField.text
                        member.zipCode = zipcodeField.text
                        member.reference = referenceField.text
                        member.email = emailField.text

                        if(entryDateField.parseValue()) {
                            member.entryDate = entryDateField.value;
                        } else {
                            memberDetail.valid = false;
                        }

                        if(cancelationDateField.parseValue()) {
                            member.cancellationDate = cancelationDateField.value
                        }

                        // TODO member.cancellationDate = cancelationDateField.text
                        member.state = "A" // TODO stateField.checked
                    }

                    Connections {
                        target: memberDetail
                        onRead: dataTab.onRead()
                    }

                }
            }

            Tab {
                title: qsTr("Beitrag")

                ColumnLayout {
                    id: contributionTab
                    anchors.fill: parent
                    anchors.margins: 8
                    spacing: 4

                    GroupBox {
                        title: qsTr("Beiträge")
                        Layout.fillWidth: true

                        GridLayout {
                            anchors.fill: parent
                            anchors.margins: 8

                            columns: 2

                            Text {text: qsTr("Beitrag:") }
                            TextField {
                                Layout.fillWidth: true

                                id: feeField
                                text: contribution.fee
                                validator: DoubleValidator {
                                    decimals: 2
                                    locale: Qt.locale("de_DE")
                                }
                            }

                            Text {text: qsTr("Spende:") }
                            TextField {
                                Layout.fillWidth: true

                                id: donationField
                                text: contribution.donation
                            }

                            Text {text: qsTr("CCC Beitrag:") }
                            TextField {
                                Layout.fillWidth: true

                                id: additionalFeeField
                                text: contribution.additionalFee
                            }

                            Text {text: qsTr("CCC Spenden Anteil") }
                            TextField {
                                Layout.fillWidth: true

                                id: additionalDonationField
                                text: contribution.additionalDonation
                            }

                            Text {text: qsTr("Schulden Beitrag") }
                            TextField {
                                Layout.fillWidth: true

                                id: amortizationField
                                text: contribution.amortization
                            }

                            Text {text: qsTr("Info:") }
                            TextField {
                                Layout.fillWidth: true

                                id: contributionInfoField
                                text: contribution.info
                            }

                            Text {text: qsTr("Gültig ab:") }
                            DateField {
                                Layout.fillWidth: true

                                id: validFromField
                                value: contribution.validFrom
                            }
                        }
                    }

                    GroupBox {
                        title: qsTr("Bank Verbindung")
                        Layout.fillWidth: true

                        GridLayout {
                            anchors.fill: parent
                            anchors.margins: 8

                            columns: 2

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
                                text: bankAccount.name
                            }

                            Text {text: qsTr("Konto Nr.:") }
                            TextField {
                                Layout.fillWidth: true

                                id: accountNrField
                                text: bankAccount.accountNumber
                            }

                            Text {text: qsTr("BLZ:") }
                            TextField {
                                Layout.fillWidth: true

                                id: bankCodeField
                                text: bankAccount.code
                            }
                        }
                    }


                    Item {
                        // Only for Spacing. Is there a better way?
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                    function onRead() {
                        console.debug("Read");

                        contribution.memberId = member.memberId
                        contribution.fee = feeField.text
                        contribution.donation = donationField.text
                        contribution.additionalFee = additionalFeeField.text
                        contribution.additionalDonation = additionalDonationField.text
                        contribution.amortization = amortizationField.text
                        contribution.info = contributionInfoField.text

                        if(validFromField.parseValue()) {
                            contribution.validFrom = validFromField.value
                        } else {
                            memberDetail.valid = false;
                        }

                        member.collectionState = "K"; //contributionStateField.checked

                        bankAccount.memberId = member.memberId
                        bankAccount.name = bankNameField.text
                        bankAccount.accountNumber = accountNrField.text
                        bankAccount.code = bankCodeField.text
                    }

                    Connections {
                        target: memberDetail
                        onRead: contributionTab.onRead()
                    }
                }
            }

            Tab {
                title: qsTr("Beiträge")

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 8

                    Text { text: qsTr("Contributon List") }
                    ContributionList {
                        Layout.fillWidth: true

                        id: contributionView
                        contributionList: contributionListModel
                    }

                    Text { text: qsTr("Balance List") }
                    BalanceList {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        id: balanceView
                        balanceList: balanceListModel
                    }
                }
            }

            Tab {
                title: qsTr("Info")

                ColumnLayout {
                    id: infoTab
                    anchors.fill: parent
                    anchors.margins: 8

                    Text { text: qsTr("Info") }
                    TextArea {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        id: infoField

                        text: member.info
                    }

                    function onRead() {
                        console.debug("Read");
                        member.info = infoField.text
                    }

                    Connections {
                        target: memberDetail
                        onRead: infoTab.onRead()
                    }
                }
            }

        }
        RowLayout {

            Button {
                text: qsTr("Neues Mitglieds")

                onClicked: {
                    console.debug("new member")
                    memberDetail.newMember();
                }
            }
            Button {
                id: saveButton
                text: qsTr("Alles Speichern")

                onClicked: {
                    console.debug("signal read")
                    memberDetail.valid = true;
                    memberDetail.read();
                    if(memberDetail.valid) {
                        console.debug("save");
                        member.save();
                        bankAccount.save();
                        contribution.save();
                        memberDetail.saveMember();
                    } else {
                        console.debug("error");
                    }
                }
            }
        }
    }

    MemberHandler {
        id: handler
    }

    function selectedMemberId(id) {
        handler.onSelectedMemberId(id);
    }
}
