import QtQuick
import QtQuick.Controls

CheckBox {
    id: control
    checked: true

    required property string checkBoxText
    property color indicatorBackgroundColor: "#202020"

    text: checkBoxText
    font.pointSize: 11
    indicator: Rectangle {
        implicitWidth: 26
        implicitHeight: 26
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 10
        color: indicatorBackgroundColor

        ColorImage {
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            defaultColor: "#353637"
            color: "green"
            source: "qrc:/qt-project.org/imports/QtQuick/Controls/Basic/images/check.png"
            visible: control.checkState === Qt.Checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        color: "white"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
