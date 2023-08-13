#include "category_tree.h"
#include "category_node.h"

CategoryTree::CategoryTree(QObject *parent)
    : DataModels::TreeModel(parent)
{
    setHeaderNames({tr("Category")});
    setRoleNames(CategoryNode::roles());
    setFlags({Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable});

//    test fill
    for(auto i = 0; i < 5; ++i)
    {
        auto root = getNode({});
        auto node = new CategoryNode(QString("First_Item_%1").arg(i), root);
        for(auto j = 0; j < 5; ++j)
        {
            node->insert(new CategoryNode(QString("Child_Item_%1").arg(j), node));
        }

        insertNode(node, root);
    }
}
