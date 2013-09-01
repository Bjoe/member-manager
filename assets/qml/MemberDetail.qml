import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item {
    id: memberDetail

    property alias name: nameField.text
    TextField {
        id: nameField
    }
/*    TabView {
        anchors.fill: memberDetail

        Tab {
            title: "Daten"

            ColumnLayout {
                RowLayout {
                    Text {
                        text: "Name:"
                    }

                }
            }
        }

        Tab {
            title: "Beitrag"
        }

        Tab {
            title: "Info"
        }
    } */
}
