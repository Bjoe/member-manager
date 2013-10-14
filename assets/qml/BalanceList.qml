import QtQuick 2.1
import QtQuick.Controls 1.0

TableView {
    id: balanceViewList

    signal rightClicked()

    property alias balanceList: balanceViewList.model

    TableViewColumn{
        role: "account"
        title: qsTr("Konto")
        width: 100
    }

    TableViewColumn{
        role: "value"
        title: qsTr("Betrag")
        width: 100
    }

    TableViewColumn{
        role: "valuta"
        title: qsTr("Valuta")
        width: 100
    }

    TableViewColumn{
        role: "purpose"
        title: qsTr("Text")
        width: 100
    }

    TableViewColumn{
        role: "info"
        title: qsTr("Info")
        width: 100
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onClicked: balanceViewList.rightClicked()
    }
}
