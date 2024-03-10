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
    font.pixelSize: 16
    leftPadding: 20
    rightPadding: 20
    topPadding: 15
    bottomPadding: 15
    contentItem: RowLayout {
        spacing: 5
        Text {
            text: root.text
            color: "white"
        }

        Image {
            source: Qt.resolvedUrl("../images/rightArrow.svg")
            sourceSize: Qt.size(16, 16)
        }
    }


    background: Rectangle {
        color: root.hovered && !root.down ? buttonColor : buttonHovered
        opacity: 0.9
        radius: 10
        border.color: borderColor
        border.width: 1

        Behavior on color { PropertyAnimation {duration: 150} }
    }


}

