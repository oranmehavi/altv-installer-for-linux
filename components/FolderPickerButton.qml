import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Button {

    id: root

    required property bool needsElide
    property color buttonHovered: "#1f1f1f"
    property color buttonColor: "#1b1c1c"

    contentItem: Text {
        anchors {
            left: parent.left
            right: icon.left
            leftMargin: 15
            rightMargin: 5
        }

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignVCenter
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        elide: needsElide ? Text.ElideRight : Text.ElideNone
        text: root.text
        font.pointSize: 11
        color: "white"
    }


    indicator: Image {
        id: icon
        source: Qt.resolvedUrl("../images/folderIcon.svg")
        x: root.width - width - 15
        y: root.topPadding + (root.availableHeight - height) / 2
        sourceSize: Qt.size(24, 24)
    }

    background: Rectangle {
        color: root.hovered && !root.down ? buttonHovered : buttonColor
        opacity: 0.9
        radius: 10
    }
}

