import QtCore
import QtQuick
import QtQuick.Dialogs
import Configuration
import "../components"

Item {

    property string installQuestion: qsTr("Where to install alt:V Multiplayer?")
    property string permissionsWarningText:
        qsTr("Do not select a folder with restricted permissions (like /usr) or a folder with non lating symbols.
Usage of those folders may lead to unexpected side effects")

    property string nonEmptyErrorText: qsTr("Selected folder should be empty")

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

    InstallerRadioButton {
        id: optionOne
        anchors {
            top: title.bottom
            left: parent.left
            topMargin: 20
            leftMargin: 50
        }

        checked: true
        optionName: qsTr("Recommended location")

        onClicked: Configuration.modInstallLocation = Configuration.recommendedLocation
    }

    Text {
        id: recommendedLocation
        anchors {
            top: title.bottom
            left: optionOne.right
            topMargin: 25
            leftMargin: 10
        }
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignVCenter
        text: Configuration.recommendedLocation
        color: "grey"
    }

    InstallerRadioButton {
        id: optionTwo
        anchors {
            top: optionOne.bottom
            left: parent.left
            topMargin: 15
            leftMargin: 50
        }

        optionName: qsTr("I want to choose it myself")

        onClicked: {
            Configuration.modInstallLocation = ""
            folderPicker.text = ""
        }

    }

    InstallerButtonRight {
        id: rightButton
        buttonText: qsTr("Shortcuts")
        height: 42
        anchors {
            right: parent.right
            bottom: parent.bottom
            bottomMargin: 50
            rightMargin: 50
        }

        onClicked: stackview.push(shortcutPage)

        enabled: Configuration.isEmpty && folderPicker.text != ""
    }

    InstallerDropDown {
        id: dropDown
        width: rightButton.implicitWidth
        height: 42
        anchors {
            left: parent.left
            bottom: parent.bottom
            bottomMargin: 50
            leftMargin: 50
            verticalCenter: rightButton.verticalCenter
        }
    }

    FolderPickerButton {
        id: folderPicker
        width: 700
        height: 50
        anchors {
            top: optionTwo.bottom
            left: parent.left
            topMargin: 20
            leftMargin: 50
        }

        visible: optionTwo.checked

        onClicked: modPath.open()
    }

    Row {
        id: warningMessage
        anchors {
            top: folderPicker.bottom
            left: parent.left
            right: parent.right
            topMargin: 20
            leftMargin: 50
            rightMargin: 50
        }
        spacing: 5
        visible: optionTwo.checked

        Image {
            id: warningImage
            source: Qt.resolvedUrl("../images/warning.svg")
            sourceSize: Qt.size(20, 20)
        }

        Text {
            id: permissionsWarning
            color: "white"
            text: permissionsWarningText
        }
    }

    Row {
        anchors {
            top: folderPicker.visible ? warningMessage.bottom : optionTwo.bottom
            left: parent.left
            right: parent.right
            topMargin: folderPicker.visible ? 20 : 40
            leftMargin: folderPicker.visible ? 50 : 60
            rightMargin: 50
        }
        spacing: 5
        visible: !Configuration.isEmpty

        Image {
            id: errorImage
            source: Qt.resolvedUrl("../images/error.svg")
            sourceSize: Qt.size(20, 20)
        }

        Text {
            id: nonEmptyError
            color: "red"
            text: nonEmptyErrorText
        }

    }


    FolderDialog {
        id: modPath
        currentFolder: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
        onAccepted: {
            var path = selectedFolder.toString()
            path = path.replace("file://","")
            folderPicker.text = path
            Configuration.modInstallLocation = path
        }
    }
}
