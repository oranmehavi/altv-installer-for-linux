import QtQuick
import "../components"

Item {

    property string installQuestion: qsTr("Do you need shortcuts?")


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


    InstallerCheckBox {
        id: checkBoxOne
        anchors {
            top: title.bottom
            left: parent.left
            topMargin: 20
            leftMargin: 50
        }

        checkBoxText: qsTr("Add shortcut to desktop")
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

        buttonText: qsTr("alt:V Folder")

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

        buttonText: qsTr("Game location")
    }

}
