#include "category_tree.h"
#include "category_node.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CategoryTree::CategoryTree(QObject *parent)
    : DataModels::TreeModel(parent)
{
    setHeaderNames({tr("Category")});
    setRoleNames(CategoryNode::roles());
    setFlags({Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable});
}

void CategoryTree::fromJson(const QByteArray &json)
{
    auto root = getNode({});
    root->clear();

    QJsonParseError jErr;
    const auto jDoc = QJsonDocument::fromJson(json, &jErr);

    if(jErr.error != QJsonParseError::NoError)
    {
        emit sigFromJsonError(jErr.errorString());
        return;
    }

    if(jDoc.isNull() || !jDoc.isObject())
    {
        return;
    }

    const auto jObj = jDoc.object();
    const auto count = jObj.value("count").toInt(0);
    if(count == 0)
    {
        return;
    }

    const auto jArr = jObj.value("categories");
    if(!jArr.isArray())
    {
        return;
    }

    const auto jCategories = jArr.toArray();
    for(const auto jCategory: jCategories)
    {
        if(!jCategory.isString())
        {
            continue;
        }

        insertNode(new CategoryNode(jCategory.toString(), CategoryNode::CategoryType::Group, root), root);
    }
}

void CategoryTree::entriesFromJson(const QString &url, const QByteArray &json)
{
    const QString categoryRequest = "category=";
    const auto categoryNameIndex = url.indexOf(categoryRequest);
    if(categoryNameIndex < 0 || json.isEmpty())
    {
        return;
    }

    auto root = getNode({});
    if(!root)
    {
        return;
    }

    const auto categoryName = url.mid(categoryNameIndex + categoryRequest.size());
    for(const auto child: root->getChildren())
    {
        auto node = static_cast<CategoryNode*>(child);
        if(node && categoryName.startsWith(node->getName()))
        {
            node->clear();
            emit sigChildrenCountChanged(getIndexByNode_(node), node->getChildren().count(), false);

            QJsonParseError jErr;
            const auto jDoc = QJsonDocument::fromJson(json, &jErr);
            if(jErr.error != QJsonParseError::NoError)
            {
                emit sigFromJsonError(jErr.errorString());
                return;
            }

            if(jDoc.isNull() || !jDoc.isObject())
            {
                return;
            }

            const auto jObj = jDoc.object();
            const auto count = jObj.value("count").toInt(0);
            if(count == 0)
            {
                return;
            }

            const auto jEntries = jObj.value("entries");
            if(!jEntries.isArray())
            {
                return;
            }

            const auto jEntriesArr = jEntries.toArray();
            for(const auto jEntry: jEntriesArr)
            {
                if(!jEntry.isObject())
                {
                    continue;
                }

                const auto jEntryObj = jEntry.toObject();
                auto entry = new CategoryNode(CategoryNode::CategoryType::Entry, node);
                entry->fromJson(QJsonDocument(jEntryObj).toJson(QJsonDocument::JsonFormat::Compact));
                insertNode(entry, node);

                const auto index = getIndexByNode_(node);
                emit dataChanged(index, index);
            }

            return;
        }
    }
}
