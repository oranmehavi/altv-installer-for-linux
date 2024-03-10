import QtQuick
import QtQuick.Controls

Item {

    StackView {
        id: stackview
        anchors.fill: parent

        initialItem: "../pages/InstallLocationPage.qml"
    }

}
