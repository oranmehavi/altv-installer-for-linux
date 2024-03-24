import QtQuick
import QtQuick.Controls

ComboBox {
    id: control
    model: ["English"]
    //model: LanguageModel
    //textRole: "language"
    //onActivated: LanguageModel.setLanguage(currentValue["locale"])
    leftPadding: 10
    font.pointSize: 11
    delegate: ItemDelegate {
        id: itemDelegate
        width: control.width
        contentItem: Text {
            text: modelData//model[control.textRole]
            color: "white"
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        hoverEnabled: true
        highlighted: control.highlightedIndex === index
        background: Rectangle {
            anchors.fill: parent
            radius: 10
            color: itemDelegate.hovered ? Qt.lighter("#1b1b1b") : "transparent"
        }


    }

    contentItem: Text {
        padding: 0
        text: control.displayText
        font: control.font
        color: "white"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        color: control.hovered ? "#191919" : "#141414"
        opacity: 0.9
        border.color: "#484848"
        border.width: 1
        radius: 10
    }

    indicator: Image {
        source: Qt.resolvedUrl("../images/arrowDown.svg")
        x: control.width - width - control.rightPadding / 4
        y: control.topPadding + (control.availableHeight - height) / 2
    }

    popup: Popup {
        y: -implicitHeight - 3
        implicitWidth: control.width
        padding: 1
        contentItem: ListView {
            clip: true
            implicitHeight: control.count <= 4 ? contentHeight : (contentHeight / control.count) * 4
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color: "#141414"
            opacity: 0.7
            border.color: "#484848"
            radius: 5
        }
    }
}

