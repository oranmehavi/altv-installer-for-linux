import QtQuick
import QtQuick.Controls

Item {

    //anchors.fill: parent
    StackView {
        id: stackview
        anchors.fill: parent

        initialItem: "InstallLocationPage.qml"
    }

}
