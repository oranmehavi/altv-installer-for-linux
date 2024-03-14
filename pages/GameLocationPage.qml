import QtQuick
import "../components"

Item {

    property string installQuestion: qsTr("Select your GTA V location")

    Text {
        id: title
        anchors {
            top: parent.top
            left: parent.left
            topMargin: 45
            leftMargin: 50
        }

        text: installQuestion
        color: "white"
        font.pixelSize: 26
    }

    InstallerPlatformButton {
        id: steam
        width: 130
        height: 50
        anchors {
            left: parent.left
            top: title.bottom
        }

        buttonText: "Steam"

        onClicked: {
            steam.background.border.color = steam.borderColor
        }
    }

    InstallerButtonLeft {
        id: leftButton
        height: 42
        anchors {
            left: parent.left
            bottom: parent.bottom
            leftMargin: 50
            bottomMargin: 50
            verticalCenter: rightButton.verticalCenter
        }

        buttonText: qsTr("Shortcuts")

        onClicked: stackview.pop()
    }

    InstallerButtonRight {
        id: rightButton
        height: 42
        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: 50
            bottomMargin: 50
        }
        enabled: false
        buttonText: qsTr("Confirm")
    }
}
