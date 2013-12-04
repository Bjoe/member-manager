import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import membermanager 1.0

Item {
    property alias member: handler.member
    property alias contribution: handler.contribution
    property alias bankAccount: handler.bankAccount
    property alias sepaAccount: handler.sepaAccount
    property alias balanceListModel: handler.balanceProxyModel
    property alias contributionListModel: handler.contributionProxyModel

    property var memberState;
    property var contributionState;
    property bool valid;
    property bool readOnly;

    signal read()
    signal databaseChanged()

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
                                readOnly: memberDetail.readOnly
                                placeholderText: "Nr"
                            }

                            Text {text: qsTr("Name:") }
                            TextField {
                                Layout.fillWidth: true

                                id: nameField
                                text: member.name
                                placeholderText: "Mitglied Nachname"
                            }

                            Text {text: qsTr("Vorname:") }
                            TextField {
                                Layout.fillWidth: true

                                id: firstNameField
                                text: member.firstname
                                placeholderText: "Mitglied Vorname"
                            }

                            Text {text: qsTr("Nickname:") }
                            TextField {
                                Layout.fillWidth: true

                                id: nicknameField
                                text: member.nickname
                                placeholderText: "Mitglied nickname"
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
                                placeholderText: "Straße"
                            }

                            Text {text: qsTr("Stadt:") }
                            TextField {
                                Layout.fillWidth: true

                                id: cityField
                                text: member.city
                                placeholderText: "Stadt"
                            }

                            Text {text: qsTr("Postleitzahl:") }
                            TextField {
                                Layout.fillWidth: true

                                id: zipcodeField
                                text: member.zipCode
                                placeholderText: "Postleitzahl in (99999)"
                                inputMask: "99999"
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
                                placeholderText: "CCC Mitgliedsnummer"
                                validator: IntValidator {
                                    bottom: 0;
                                }
                            }

                            Text {text: qsTr("Email:") }
                            TextField {
                                Layout.fillWidth: true

                                id: emailField
                                text: member.email
                                placeholderText: "Email Adresse"
                            }

                            Text {text: qsTr("Eintritts Datum:") }
                            DateField {
                                Layout.fillWidth: true

                                id: entryDateField
                                value: member.entryDate
                                placeholderText: "Eintritts Datum in (tt.mm.jjjj)"
                            }

                            Text {text: qsTr("Austritts Datum:") }
                            DateField {
                                Layout.fillWidth: true

                                id: cancelationDateField
                                value: member.cancellationDate
                                placeholderText: "Austritts Datum in (tt.mm.jjjj)"
                            }

                            Text {text: qsTr("Gelöscht/Deaktiviert") }
                            CheckBox {
                                Layout.fillWidth: true

                                id: stateField

                                checkedState: memberDetail.memberState
                            }
                        }
                    }

                    Item {
                        // Only for Spacing. Is there a better way?
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                    function onRead() {
                        console.debug("Read data valid =", memberDetail.valid);

                        member.memberId = memberIdField.text;
                        member.name = nameField.text;
                        member.firstname = firstNameField.text;
                        member.nickname = nicknameField.text;
                        member.street = streetField.text;
                        member.city = cityField.text;
                        member.zipCode = zipcodeField.text;
                        member.reference = referenceField.text;
                        member.email = emailField.text;

                        var entryDate = entryDateField.readDate();
                        console.debug("Entry Date", entryDate);
                        if(entryDate === undefined) {
                            memberDetail.valid = false;
                        } else {
                            member.entryDate = entryDate;
                        }

                        var cancelationDate = cancelationDateField.readDate();
                        console.debug("Cancelation Date", cancelationDate);
                        if(cancelationDate !== undefined) {
                            member.cancellationDate = cancelationDate;
                        }

                        if(stateField.checked) {
                            member.state = 'I';
                        } else {
                            member.state = 'A';
                        }
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
                            AmountField {
                                Layout.fillWidth: true

                                id: feeField
                                value: contribution.fee
                            }

                            Text {text: qsTr("Spende:") }
                            AmountField {
                                Layout.fillWidth: true

                                id: donationField
                                value: contribution.donation
                            }

                            Text {text: qsTr("CCC Beitrag:") }
                            AmountField {
                                Layout.fillWidth: true

                                id: additionalFeeField
                                value: contribution.additionalFee
                            }

                            Text {text: qsTr("CCC Spenden Anteil") }
                            AmountField {
                                Layout.fillWidth: true

                                id: additionalDonationField
                                value: contribution.additionalDonation
                            }

                            Text {text: qsTr("Schulden Beitrag") }
                            AmountField {
                                Layout.fillWidth: true

                                id: amortizationField
                                value: contribution.amortization
                            }

                            Text {text: qsTr("Info:") }
                            TextField {
                                Layout.fillWidth: true

                                id: contributionInfoField
                                text: contribution.info
                                placeholderText: "Info text"
                            }

                            Text {text: qsTr("Gültig ab:") }
                            DateField {
                                Layout.fillWidth: true

                                id: validFromField
                                value: contribution.validFrom
                                placeholderText: "Gültig ab in (tt.mm.yyyy)"
                            }

                            Button {
                                text: qsTr("Neuer Beitrag")
                                onClicked: handler.onNewContribution()
                            }
                        }
                    }

                    GroupBox {
                        title: qsTr("SEPA Verbindung")
                        Layout.fillWidth: true

                        GridLayout {
                            anchors.fill: parent
                            anchors.margins: 8

                            columns: 2

                            Text {text: qsTr("Basislastschrift") }
                            CheckBox {
                                Layout.fillWidth: true
                                id: contributionStateField

                                checkedState: memberDetail.contributionState
                            }

                            Text {text: qsTr("IBAN:") }
                            TextField {
                                Layout.fillWidth: true

                                id: ibanField
                                text: sepaAccount.iban
                                placeholderText: "IBAN Id"
                            }

                            Text {text: qsTr("BIC:") }
                            TextField {
                                Layout.fillWidth: true

                                id: bicField
                                text: sepaAccount.bic
                                placeholderText: "BIC Id"
                            }

                            Text {text: qsTr("Mandate Date:") }
                            DateField {
                                Layout.fillWidth: true

                                id: mandateDateField
                                value: sepaAccount.mandateDate
                                placeholderText: "Mandate Unterschrift (tt.mm.yyyy)"
                            }

                            Text {text: qsTr("Typ") }
                            ComboBox {
                                Layout.fillWidth: true

                                id: sequenceTypeField
                                model: sequenceTypeChoice
                            }

                            ListModel {
                                id: sequenceTypeChoice
                                ListElement {
                                    text: "Erste Lastschrift";
                                    type: "FIRST";
                                }
                                ListElement {
                                    text: "Folgelastschrift";
                                    type: "FOLLOWING"
                                }
                                /*ListElement {
                                    text: "Letzte Lastschrift";
                                    type: "LAST";
                                }
                                ListElement {
                                    text: "Einmallastschrift";
                                    type: "ONCE";
                                }*/
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

                            Text {text: qsTr("Name:") }
                            TextField {
                                Layout.fillWidth: true

                                id: bankNameField
                                text: bankAccount.name
                                placeholderText: "Name der Bank"
                            }

                            Text {text: qsTr("Konto Nr.:") }
                            TextField {
                                Layout.fillWidth: true

                                id: accountNrField
                                text: bankAccount.accountNumber
                                placeholderText: "Kontonummer"
                                validator: IntValidator {
                                    bottom: 0;
                                }
                            }

                            Text {text: qsTr("BLZ:") }
                            TextField {
                                Layout.fillWidth: true

                                id: bankCodeField
                                text: bankAccount.code
                                placeholderText: "Bankleitzahl"
                                inputMask: "99999999"
                            }
                        }
                    }

                    Item {
                        // Only for Spacing. Is there a better way?
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }

                    function onRead() {
                        console.debug("Read contribution valid =", memberDetail.valid);

                        contribution.memberId = member.memberId;
                        contribution.fee = feeField.readValue();
                        contribution.donation = donationField.readValue();
                        contribution.additionalFee = additionalFeeField.readValue();
                        contribution.additionalDonation = additionalDonationField.readValue();
                        contribution.amortization = amortizationField.readValue();
                        contribution.info = contributionInfoField.text;

                        var validFrom = validFromField.readDate();
                        console.debug("Valid From", validFrom);
                        if(validFrom === undefined) {
                            memberDetail.valid = false;
                        } else {
                            contribution.validFrom = validFrom;
                        }

                        if(contributionStateField.checked) {
                            member.collectionState = 'K';
                        } else {
                            member.collectionState = 'P';
                        }

                        bankAccount.memberId = member.memberId
                        bankAccount.name = bankNameField.text
                        bankAccount.accountNumber = accountNrField.text
                        bankAccount.code = bankCodeField.text

                        sepaAccount.memberId = member.memberId;
                        sepaAccount.iban = ibanField.text;
                        sepaAccount.bic = bicField.text;
                        var index = sequenceTypeField.currentIndex;
                        var type = sequenceTypeChoice.get(index).type;
                        console.debug(type);
                        sepaAccount.sequenceState = type;
                        var mandateDate = mandateDateField.readDate();
                        console.debug("MandateDate", mandateDate);
                        if(mandateDate === undefined) {
                            memberDetail.valid = false;
                        } else {
                            sepaAccount.mandateDate = mandateDate;
                        }
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

                        onRightClicked: mymenu.popup();

                        Menu {
                            id: mymenu
                            title: "Context Menu"

                            MenuItem {
                                text: qsTr("Copy selection")
                                onTriggered: handler.copyBalanceToClipboard(balanceView.currentRow)
                            }
                            MenuItem {
                                text: qsTr("Copy All")
                                onTriggered: handler.copyAllBalanceToClipboard()
                            }
                        }
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
                    handler.onNewMember();
                    memberDetail.readOnly = false;
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
                        sepaAccount.save();
                        contribution.save();
                        memberDetail.readOnly = true;
                        memberDetail.databaseChanged();
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
        memberDetail.readOnly = true;
        handler.onSelectedMemberId(id);

        if(handler.member.collectionState === 'K') {
            memberDetail.contributionState = Qt.Checked;
        } else {
            memberDetail.contributionState = Qt.Unchecked;
        }

        if(handler.member.state === 'I') {
            memberDetail.memberState = Qt.Checked;
        } else {
            memberDetail.memberState = Qt.Unchecked;
        }
    }
}
