import QtQuick 2.1
import QtQuick.Controls 1.0

TextField {
    property double value;

    id: field

    text: value.toLocaleString(Qt.locale("de_DE"));
    validator: DoubleValidator {
        bottom: 0
        decimals: 2
        locale: "de_DE"
        notation: DoubleValidator.StandardNotation
    }

    function readValue() {
        var value = field.text.replace(/\./g, "").replace(",",".");
        return value;
    }
}
