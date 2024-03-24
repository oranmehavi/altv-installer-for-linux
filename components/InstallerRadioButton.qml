import QtQuick
import QtQuick.Controls


RadioButton {
    required property string optionName
    property color indicatorBackgroundColor: "#202020"
    property color indicatorColor: "#08ae40"

    id: control
    text: optionName
    font.pointSize: 11
    indicator: Rectangle {
        implicitWidth: 26
        implicitHeight: 26
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        color: indicatorBackgroundColor
        radius: 13


        Rectangle {
            width: 14
            height: 14
            x: 6
            y: 6
            radius: 7
            color: indicatorColor
            visible: control.checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: "white"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
