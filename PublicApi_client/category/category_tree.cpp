#include "category_tree.h"
#include "category_node.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CategoryTree::CategoryTree(QObject *parent)
    : DataModels::TreeModel(parent)
{
    setHeaderNames({tr("Category"), tr("Extra Column")});
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

    const auto jCategories = jObj.value("categories");
    if(!jCategories.isArray())
    {
        return;
    }

    for(const auto jCategory: jCategories.toArray())
    {
        if(!jCategory.isString())
        {
            continue;
        }

        insertNode(new CategoryNode(jCategory.toString(), root), root);
    }
}
