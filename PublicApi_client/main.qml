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
        delegate: Text {
            width: 100
            height: 20
                text: display + " index: " + index
        }
    }
}
