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
            text: "🗕"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: window.showMinimized();
        }
        ToolButton {
            text: "🗙"
            background: Rectangle {
                color: "transparent"
            }
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: window.close()
        }
    }
}
