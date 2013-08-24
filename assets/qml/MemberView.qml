import QtQuick 2.1
import QtQuick.Controls 1.0

Item {
    id: memberViewMain
    width: 500
    height: 500

    Text { text: currentDateTime }

    TableView {
        id: memberViewList
        anchors.fill: memberViewMain
        anchors.margins: 11

        TableViewColumn{ role: "name"  ; title: "Name" ; width: 100 }
        TableViewColumn{ role: "firstname" ; title: "First name" ; width: 200 }

        model: memberTable
    }
}
