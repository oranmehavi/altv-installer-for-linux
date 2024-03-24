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
        Layout.rightMargin: 3
        ToolButton {
            background: Rectangle {
                color: "transparent"
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
            Layout.leftMargin: 10

            background: Rectangle {
                color: "transparent"
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
