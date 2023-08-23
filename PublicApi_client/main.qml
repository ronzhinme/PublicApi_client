import QtQuick
import QtQuick.Controls

import category

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
            model: CategoryTree {
                id: categoriesTreeModel
            }

            SplitView.minimumWidth: 100
            SplitView.preferredWidth: 200
            SplitView.maximumWidth: 300
        }

        Item {
            id: rightPanel
            readonly property var selectedCategoryNode: Object.assign(categoriesTreeModel.getNode(navigator.selectionModel.currentIndex))
            Column {
                Text {
                    text: rightPanel.selectedCategoryNode.name
                }
                Text {
                    text: rightPanel.selectedCategoryNode.link
                }
                Text {
                    text: rightPanel.selectedCategoryNode.description
                }
            }
        }
    }
}
