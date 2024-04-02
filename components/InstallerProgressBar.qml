import QtQuick
import QtQuick.Controls
import DownloaderInstaller

ProgressBar {
    id: root

    from: 0
    to: 100

    value: DownloadInstaller.progress

    indeterminate: false

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 6
        color: "#1b1c1c"
        radius: 3
    }

    contentItem: Item {
        implicitWidth: 400
        implicitHeight: 4

        // Progress indicator for determinate state.
        Rectangle {
            width: root.visualPosition * parent.width
            height: parent.height
            radius: 2
            color: "white"
            visible: !root.indeterminate
        }

        // Scrolling animation for indeterminate state.
        Item {
            anchors.fill: parent
            visible: root.indeterminate
            clip: true

            Row {
                spacing: 20

                Repeater {
                    model: 1

                    Rectangle {
                        color: "white"
                        width: 100
                        height: root.height
                    }
                }
                XAnimator on x {
                    from: -150
                    to: 400
                    duration: 3000
                    loops: Animation.Infinite
                    running: root.indeterminate
                }
            }
        }
    }
}
