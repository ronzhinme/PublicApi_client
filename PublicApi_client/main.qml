import QtQuick
import QtQuick.Controls

import category

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Public API client")

    CategoryTree {
        id: treeModel
    }

    TreeView {
        id: tree
        anchors.fill: parent
        model: treeModel

        delegate: Item
        {
            implicitHeight: categoryItem.height
            implicitWidth: tree.width

            TapHandler {
                onTapped: {
                    tree.toggleExpanded(index)
                }
            }

            Text {
                id: indicator
                visible: !isEmpty
                anchors.verticalCenter: rowItem.verticalCenter
                text: "▸"
                font.pointSize: 14
                rotation: tree.isExpanded(index) ? 90 : 0
            }

            Row {
                id: rowItem
                height: image.height
                anchors.left: indicator.right
                anchors.leftMargin: 5
                spacing: 5

                Row {
                    id: categoryItem
                    spacing: 5
                    Image {
                        id: image
                        source: icon
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: categoryName
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Row {
                    id: extraItem
                    Text {
                        text: extra
                    }
                }
            }
        }
    }
}
