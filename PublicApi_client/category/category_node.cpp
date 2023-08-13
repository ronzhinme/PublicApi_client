#include "category_node.h"

CategoryNode::CategoryNode(QObject *parent)
    : DataModels::TreeNode(parent)
{
    connect(this, &DataModels::TreeNode::sigChildrenCountChanged, this, &CategoryNode::onChildrenCountChanged_);

    setName("");
    onChildrenCountChanged_();
}

CategoryNode::CategoryNode(const QString &name, QObject *parent)
    : DataModels::TreeNode(parent)
{
    connect(this, &DataModels::TreeNode::sigChildrenCountChanged, this, &CategoryNode::onChildrenCountChanged_);

    setName(name);
    onChildrenCountChanged_();
}

const QHash<int, QByteArray> CategoryNode::roles()
{
    static const QHash<int, QByteArray> hash
    {
        {CategoryNode::Role::Name, "name"},
        {CategoryNode::Role::IsEmpty, "isEmpty"}
    };

    return hash;
}

QString CategoryNode::name() const
{
    return get(roles().value(Role::Name)).toString();
}

void CategoryNode::setName(const QString &val)
{
    set(roles().value(Role::Name), val);
}

bool CategoryNode::isEmpty() const
{
    return get(roles().value(Role::IsEmpty)).toBool();
}

void CategoryNode::onChildrenCountChanged_()
{
    set(roles().value(Role::IsEmpty), getChildren().isEmpty());
}
