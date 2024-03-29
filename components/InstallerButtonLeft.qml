import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Button {
    id: root

    required property string buttonText
    property color buttonHovered: "#1f1f1f"
    property color buttonColor: "#1b1c1c"
    property color borderColor: "#484848"

    text: buttonText
    leftPadding: 15
    rightPadding: 15
    contentItem: RowLayout {
        spacing: 5
        Image {
            source: Qt.resolvedUrl("../images/leftArrow.svg")
            sourceSize: Qt.size(16, 16)
        }


        Text {
            text: root.text
            font.pointSize: 11
            color: "white"
        }
    }


    background: Rectangle {
        color: root.hovered && !root.down ? buttonHovered : buttonColor
        opacity: 0.9
        radius: 10
        border.color: borderColor
        border.width: 1

        Behavior on color { PropertyAnimation {duration: 150} }
    }


}
