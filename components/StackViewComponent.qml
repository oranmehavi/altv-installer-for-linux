import QtQuick
import QtQuick.Controls
import "../pages"

Item {

    StackView {
        id: stackview
        anchors.fill: parent

        initialItem: "../pages/InstallLocationPage.qml"
    }

    ShortcutsPage {
        id: shortcutPage
        visible: false
    }

    GameLocationPage {
        id: gameLocationPage
        visible: false
    }

    ConfirmPage {
        id: confirmPage
        visible: false
    }
}
