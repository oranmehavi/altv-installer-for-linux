import QtQuick

Item {

    property string installQuestion: qsTr("Where to install alt:V Multiplayer?")

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
        id: one
        anchors {
            top: title.bottom
            left: parent.left
            topMargin: 20
            leftMargin: 50
        }

        checked: true

        optionName: qsTr("Recommended location")
    }

    InstallerRadioButton {
        id: two
        anchors {
            top: one.bottom
            left: parent.left
            topMargin: 15
            leftMargin: 50
        }

        optionName: qsTr("I want to choose it myself")
    }

}