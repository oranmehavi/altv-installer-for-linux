import QtQuick
import QtQuick.Controls

Button {
    id: root

    required property string buttonText
    property color buttonColor: "#191919"
    property color borderColor: "#08ae40"

    text: buttonText
    leftPadding: 15
    rightPadding: 15
    checkable: true
    contentItem:  Text {
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignVCenter
        text: root.text
        font.pointSize: 11
        color: "white"
    }

    background: Rectangle {
        color: buttonColor
        opacity: 0.9
        radius: 10
        border.color: root.hovered || root.checked ? borderColor : "transparent"
        border.width: 1

        Behavior on border.color { PropertyAnimation {duration: 100} }
    }
}
