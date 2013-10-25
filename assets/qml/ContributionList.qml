import QtQuick 2.1
import QtQuick.Controls 1.0

TableView {
    id: contributionViewList

    property alias contributionList: contributionViewList.model

    TableViewColumn{
        role: "fee"
        title: qsTr("Beitrag")
        width: 100
    }

    TableViewColumn{
        role: "donation"
        title: qsTr("Spende")
        width: 100
    }

    TableViewColumn{
        role: "additionalFee"
        title: qsTr("CCC Beitrag")
        width: 100
    }

    TableViewColumn{
        role: "additionalDonation"
        title: qsTr("CCC Spende")
        width: 100
    }

    TableViewColumn{
        role: "validFrom"
        title: qsTr("Gültig ab")
        width: 100
    }

    TableViewColumn{
        role: "info"
        title: qsTr("Info")
        width: 100
    }
}
