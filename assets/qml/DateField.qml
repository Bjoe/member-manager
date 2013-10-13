import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

TextField {
    property date value

    id: field
    text: value.toLocaleDateString(Qt.locale("de_DE"), "dd.MM.yyyy")
    inputMethodHints: Qt.ImhDate
    inputMask: "99.99.9999"

    // Example from http://www.w3resource.com/javascript/form/javascript-date-validation.php
    function parseValue() {
        var dateValues = text.split(".");
        var dd = dateValues[0];
        var mm = dateValues[1];
        var yy = dateValues[2];

        var validDays = [31,28,31,30,31,30,31,31,30,31,30,31];
        if(mm === 1 || mm > 2) {
            if (dd > validDays[mm - 1]) {
                console.debug("Invalid date format!");
                field.state = 'invalid';
                return false;
            } else {
                field.state = '';
                value = new Date(yy,mm,dd);
                return true;
            }
        }
        if (mm === 2) {
            var lyear = false;
            if ( (!(yy % 4) && yy % 100) || !(yy % 400)) {
                lyear = true;
            }
            if ((lyear == false) && (dd >= 29)) {
                console.debug("Invalid date format!");
                field.state = 'invalid';
                return false;
            }
            if ((lyear == true) && (dd > 29)) {
                console.debug("Invalid date format!");
                field.state = 'invalid';
                return false;
            }
        } else {
            console.debug("Invalid date format!");
            field.state = 'invalid';
            return false;
        }
    }

    states: [
        State {
            name: "invalid"
            PropertyChanges {
                target: field
                textColor: "red"
            }
        }
    ]
}
