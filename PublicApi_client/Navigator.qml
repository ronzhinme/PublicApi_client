import QtQuick

import category
import web_request

TreeView {
    id: tree
    selectionModel: ItemSelectionModel{}

    function requestCategries() {
        webRequest.requestGetJson(webRequest.url_get_categories)
    }

    WebRequest {
        id: webRequest

        readonly property string url_get_categories: "https://api.publicapis.org/categories"
        readonly property string url_get_category_entries: "https://api.publicapis.org/entries?category="
    }

    Connections {
        target: webRequest

        function onSigRequestError(url, err, httpCode) {
            //console.log("======== [", url,"] Request error: ", err, httpCode)
        }

        function onSigRequestCompleted(url, reply) {
            //console.log("======== [", url, "] Request reply: ", reply)

            if(url.includes(webRequest.url_get_categories)){
                categoriesTreeModel.fromJson(reply)
            }

            if(url.includes(webRequest.url_get_category_entries)){
                categoriesTreeModel.entriesFromJson(url, reply)
            }
        }
    }

    clip: true
    model: categoriesTreeModel
    delegate: Item
    {
        implicitHeight: rowItem.height
        implicitWidth: tree.width

        TapHandler {
            onTapped: {
                if(!isEmptyRole) toggleExpanded(index)
                else {
                    switch(typeRole)
                    {
                    case 0: webRequest.requestGetJson(webRequest.url_get_category_entries + nameRole)
                        break
                    case 1:
                        break
                    }
                }
            }
        }

        Text {
            id: indicator
            visible: !isEmptyRole
            anchors.verticalCenter: rowItem.verticalCenter
            text: "▸"
            font.pointSize: 14
            rotation: isExpanded(index) ? 90 : 0
        }



        Row {
            id: rowItem
            height: image.height
            anchors.left: indicator.right
            anchors.leftMargin: 5
            spacing: 5

            Item {
                Rectangle {
                    color: tree.currentRow === index ? "skyblue" : "transparent"
                    anchors.fill: categoryItem
                }

                Row {
                    id: categoryItem
                    spacing: 5
                    Image {
                        id: image
                        source: iconRole
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: categoryName
                        text: nameRole
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }
}
