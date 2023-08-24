import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebView

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

        ColumnLayout {
            id: rightPanel
            readonly property var selectedCategoryNode: Object.assign(categoriesTreeModel.getNode(navigator.selectionModel.currentIndex))

            Text {
                id: nameText
                text: rightPanel.selectedCategoryNode.name
            }
            Text {
                id: linkText
                text: rightPanel.selectedCategoryNode.link
            }
            Text {
                id: descText
                text: rightPanel.selectedCategoryNode.description
            }
            Button {
                visible: linkText.text.length > 0
                text: qsTr("Run")
                onClicked: {
                    webView.url = linkText.text
                }
            }

            onSelectedCategoryNodeChanged: {
                webView.url = "about:blank"
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "gray"
            }

            WebView {
                id: webView
                Layout.fillHeight: true
                Layout.fillWidth: true

            }
        }
    }
}
