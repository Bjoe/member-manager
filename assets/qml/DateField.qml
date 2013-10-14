import QtQuick 2.0
import QtQuick.Controls 1.0

TextField {
    property date value

    id: field
    text: value.toLocaleDateString(Qt.locale("de_DE"), "dd.MM.yyyy")
    inputMethodHints: Qt.ImhDate
    inputMask: "99.99.9999"

    // Example from http://www.w3resource.com/javascript/form/javascript-date-validation.php
    function readDate() {
        console.debug("Read date", text);
        var values = field.text.replace(/ /g,"");
        console.debug("date", values);
        if(values === "..") {
            return;
        }
        var dateValues = values.split(".");
        var dd = dateValues[0];
        var mm = dateValues[1];
        var yy = dateValues[2];

        if(!(mm >= 1 || mm <= 12)) {
            console.debug("Invalid date format!", dd, mm, yy);
            field.state = 'invalid';
            return;
        }

        if ( (mm == 2) &&
                ! ((!(yy % 4) && yy % 100) || !(yy % 400)) &&
                (dd >= 29)) {
            console.debug("Invalid date format!", dd, mm, yy);
            field.state = 'invalid';
            return;
        }

        var validDays = [31,29,31,30,31,30,31,31,30,31,30,31];
        if (dd > validDays[mm - 1]) {
            console.debug("Invalid date format!", dd, mm, yy);
            field.state = 'invalid';
            return;
        }

        field.state = '';
        console.debug("Valid date", dd, mm, yy);
        return new Date(yy,mm - 1,dd);
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
