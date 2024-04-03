import QtQuick
import DownloaderInstaller
import "../components"

Item {

    Text {

        id: header
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: progress.top
            bottomMargin: 50
        }

        text: qsTr("Installing")
        color: "white"
        font.pixelSize: 20
    }


    Text {

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: header.bottom
            topMargin: 15
        }

        text: qsTr("Placeholder")
        color: "grey"
        font.pointSize: 11

    }

    Text {

        anchors {
            top: progress.bottom
            left: progress.left
            topMargin: 15
        }

        text: DownloadInstaller.sizeDownloaded + " / " + DownloadInstaller.totalSize + " MB"
        color: "grey"
        font.pointSize: 11
    }

    Text {

        id: timeLeft

        anchors {
            top: progress.bottom
            right: progress.right
            topMargin: 15
        }

        text: "Placeholder"
        color: "grey"
        font.pointSize: 11
    }

    Text {
        id: speed

        anchors {
            top: timeLeft.bottom
            right: progress.right
            topMargin: 5
        }

        text: DownloadInstaller.speed
        color: "grey"
        font.pointSize: 11
    }

    InstallerProgressBar {
        id: progress

        anchors.centerIn: parent
    }

}
