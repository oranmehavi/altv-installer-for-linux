import QtQuick
import "../components"

Item {

    Text {

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: progress.top
            bottomMargin: 30
        }

        text: qsTr("Installing")
        color: "white"
        font.pixelSize: 20
    }

    InstallerProgressBar {
        id: progress

        anchors.centerIn: parent
    }

}
