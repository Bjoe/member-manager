import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0


ColumnLayout {

    id: memberDetail

    //property Member member
    //property Contribution contribution
    //property BankAccount bankAccount
    //property ProxyTableModel balanceListModel
    //property ProxyTableModel contributionListModel

    property alias member: handler.member
    property alias contribution: handler.contribution
    property alias bankAccount: handler.bankAccount
    property alias balanceListModel: handler.balanceProxyModel
    property alias contributionListModel: handler.contributionProxyModel

    signal read()
    signal newMember()
    signal saveMember()
    signal clear()

    TabView {
        Layout.fillWidth: true
        Layout.fillHeight: true

        Tab {
            title: qsTr("Daten")

            ColumnLayout {
                id: dataTab
                anchors.fill: parent
                spacing: 4

                GroupBox {
                    title: qsTr("Allgemeine Daten")
                    Layout.fillWidth: true

                    GridLayout {
                        columns: 2

                        anchors.fill: parent

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
                    Layout.fillHeight: truenameField
                    Layout.fillWidth: true
                }

                function onClear() {
                    console.debug("clear");

                    memberIdField.text = "";
                    nameField.text = "";
                    firstNameField.text = "";
                    nicknameField.text = "";
                    streetField.text = "";
                    cityField.text = "";
                    zipcodeField.text = "";
                    referenceField.text = "";
                    emailField.text = "";
                    entryDateField.text = "";
                    cancelationDateField.text = "";
                    // TODO stateField.checked = false;

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
                    member.entryDate = entryDateField.text
                    // TODO member.cancellationDate = cancelationDateField.text
                    member.state = "A" // TODO stateField.checked
                }

                Connections {
                    target: memberDetail
                    onRead: dataTab.onRead()
                }

                Connections {
                    target: memberDetail
                    onClear: dataTab.onClear()
                }
            }
        }

        Tab {
            title: qsTr("Beitrag")

            ColumnLayout {
                id: contributionTab
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
                            text: contribution.fee
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
                        TextField {
                            Layout.fillWidth: true

                            id: validFromField
                            text: contribution.validFrom
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

                function onClear() {
                    console.debug("Clear");

                    feeField.text = "0";
                    donationField.text = "0";
                    additionalFeeField.text = "0";
                    additionalDonationField.text = "0";
                    amortizationField.text = "0";
                    validFromField.text = "";
                    contributionStateField.checked = "N";
                    bankNameField.text = "";
                    accountNrField.text = "";
                    bankCodeField.text = "";
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
                    contribution.validFrom = validFromField.text

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

                Connections {
                    target: memberDetail
                    onClear: contributionTab.onClear()
                }
            }
        }

        Tab {
            title: qsTr("Beiträge")

            ColumnLayout {
                anchors.fill: parent
                spacing: 4

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
            title: qsTr("Spenden Quittung")

            ContributionReceipt {
                memberId: member.memberId
            }
        }

        Tab {
            title: qsTr("Info")

            ColumnLayout {
                id: infoTab
                anchors.fill: parent
                spacing: 4

                Text { text: qsTr("Info") }
                TextField {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    id: infoField

                    text: member.info
                }

                function onClear() {
                    console.debug("clear")
                    infoField.text = "";
                }

                function onRead() {
                    console.debug("Read");
                    member.info = infoField.text
                }

                Connections {
                    target: memberDetail
                    onRead: infoTab.onRead()
                }

                Connections {
                    target: memberDetail
                    onClear: infoTab.onClear()
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
                //memberDetail.clear();
            }
        }
        Button {
            id: saveButton
            text: qsTr("Alles Speichern")

            onClicked: {
                console.debug("signal read")
                memberDetail.read();
                console.debug("save");
                member.save();
                bankAccount.save();
                contribution.save();
                memberDetail.saveMember();
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
