import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Configuration
import "../components"

Item {

    property string installQuestion: qsTr("Confirm your preferences")

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


    ColumnLayout {

        anchors {
            top: title.bottom
            left: parent.left
            topMargin: 50
            leftMargin: 50
        }

        Text {
            text: qsTr("alt:V Location")
            color: "grey"
            font.pointSize: 11
        }

        Row {

            spacing: 10

            Text {
                id: modPath
                text: Configuration.modInstallLocation
                color: "white"
                font.pointSize: 11
            }

            Text {
                text: "(" + qsTr("Recommended") + ")"
                font.pointSize: 11
                color: "white"

                visible: Configuration.modInstallLocation == Configuration.recommendedLocation
            }
        }

        Text {
            Layout.topMargin: 15

            text: qsTr("GTA V Location")
            color: "grey"
            font.pointSize: 11
        }

        Row {
            spacing: 10

            Text {
                id: gamePath
                text: Configuration.gameInstallLocation
                color: "white"
                font.pointSize: 11
            }

            Text {
                text: "(" + Configuration.platformName + ")"
                font.pointSize: 11
                color: "white"
            }

        }

        Text {
            Layout.topMargin: 15

            text: qsTr("Add shortcut to desktop")
            font.pointSize: 11
            color: "grey"

            visible: Configuration.needsShortcut
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

        buttonText: qsTr("Game location")

        onClicked: stackview.pop()
    }

    Button {
        id: rightButton
        height: 42
        leftPadding: 15
        rightPadding: 15
        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: 50
            bottomMargin: 50
        }

        background: Rectangle {
            color: rightButton.hovered ? "#1f1f1f" : "#1b1c1c"
            opacity: 0.9
            radius: 10
            border.color: "#08ae40"
            border.width: 1

        }

        text: qsTr("Install")

        onClicked: {
            stackview.push(downloadPage)
        }
    }
}
