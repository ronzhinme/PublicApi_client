import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Public API client")

    ToolBar {
        id: toolbar

        Row {
            anchors.fill: parent
            ToolButton {
                text: qsTr("Get categories")
                onClicked: {
                    navigator.requestCategries()
                }
            }
        }
    }

    SplitView {
        anchors.top: toolbar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        orientation: Qt.Horizontal

        Navigator {
            id: navigator
            SplitView.minimumWidth: 100
            SplitView.preferredWidth: 200
            SplitView.maximumWidth: 300
        }

        Rectangle {
            color: "red"
        }
    }
}
