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
            implicitHeight: categoryName.height
            implicitWidth: tree.width

            TapHandler {
                onTapped: {
                    tree.toggleExpanded(index)
                }
            }

            Text {
                visible: !isEmpty
                anchors.verticalCenter: categoryName.verticalCenter
                text: "▸"
                font.pointSize: 14
                rotation: tree.isExpanded(index) ? 90 : 0
            }

            Text {
                id: categoryName
                x: 20
                text: name
            }
        }
    }
}
