#include "category_tree.h"
#include "category_node.h"

CategoryTree::CategoryTree(QObject *parent)
    : DataModels::TreeModel(parent)
{
    setHeaderNames({tr("Category")});
    setRoles(CategoryRoles::roles());
    setFlags({Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable});

//    test fill
    for(auto i = 0; i < 5; ++i)
    {
        auto node = new CategoryNode(QString("First_Item_%1").arg(i), this);
        auto root = getNode({});
        for(auto j = 0; j < 5; ++j)
        {
            auto childNode = new CategoryNode(QString("Child_Item_%1").arg(j), nullptr);
            insertNode(childNode, node);
        }

        insertNode(node, root);
    }
}
