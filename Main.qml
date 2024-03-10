import QtQuick
import "components"

Window {
    id: window
    visible: true
    flags: Qt.FramelessWindowHint
    width: 800
    height: 600
    maximumWidth: width
    maximumHeight: height
    minimumWidth: width
    minimumHeight: height
    color: "transparent"


    Rectangle {
        color: Qt.darker("green")
        anchors.fill: parent
        radius: 10
    }

    TitleBar {
        id: titleBar
    }

    Loader {
        id: mainLoader
        anchors {
            top: titleBar.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        source: "components/StackViewComponent.qml"
    }
}
