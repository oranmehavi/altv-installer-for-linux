import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {

    id: header
    anchors {
        top: parent.top
        right: parent.right
        left: parent.left
    }

    DragHandler {
        id: handler
        onActiveChanged: if (active) {
                             acceptedButtons = window.startSystemMove() ? Qt.NoButton : Qt.LeftButton
                         } else {
                             acceptedButtons = Qt.LeftButton
                         }
    }
    RowLayout {
        spacing: 0
        Layout.alignment: Qt.AlignRight
        ToolButton {
            background: Rectangle {
                color: toolButton.hovered ? "grey" : "transparent"
            }

            id: toolButton
            contentItem: Text {
                text: "🗕"
                color: "white"
                font.pixelSize: 22
            }

            onClicked: window.showMinimized();
        }
        ToolButton {
            id: close
            Layout.leftMargin: 10

            background: Rectangle {
                color: close.hovered ? "red" : "transparent"
                topRightRadius: 10
            }

            contentItem: Text {
                id: s
                text: "🗙"
                color: "white"
                font.pixelSize: 22
            }

            onClicked: window.close()
        }
    }
}
