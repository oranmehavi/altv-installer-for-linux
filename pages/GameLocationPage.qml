import QtQuick
import QtQuick.Controls
import Configuration
import "../components"

Item {

    property string installQuestion: qsTr("Select your GTA V location")
    property string errorText: qsTr("The folder of your GTA V installation on Steam could not be found automatically. Please select it manaully.")

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

    ButtonGroup {
        id: platforms
    }

    InstallerPlatformButton {
        id: steam
        width: 250
        height: 50
        anchors {
            top: title.bottom
            left: parent.left
            topMargin: 50
            leftMargin: 50
        }
        ButtonGroup.group: platforms
        buttonText: "Steam"

        onClicked: {
            Configuration.findGameInstallationPath("Steam")
            Configuration.platformName = "Steam"
        }
    }

    Text {

        id: gameNotFoundError
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        anchors {
            top: title.bottom
            left: steam.right
            right: parent.right
            topMargin: 50
            leftMargin: 40
            rightMargin: 50
            verticalCenter: steam.verticalCenter
        }

        text: errorText
        color: "white"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignVCenter
        font.pixelSize: 14

        visible: !Configuration.isGameFound
    }

    FolderPickerButton {
        id: gameInstallation
        width: 400
        height: 50

        anchors {
            top: gameNotFoundError.visible ? gameNotFoundError.bottom : title.bottom
            right: parent.right
            topMargin: gameNotFoundError.visible ? 20 : 50
            rightMargin: 60
        }

        needsElide: false
        text: Configuration.gameInstallLocation
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
