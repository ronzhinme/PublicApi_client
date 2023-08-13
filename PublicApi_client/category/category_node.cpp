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
        {CategoryNode::Role::Extra, "extra"},
        {CategoryNode::Role::IsEmpty, "isEmpty"},
        {CategoryNode::Role::Icon, "icon"},
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

QUrl CategoryNode::icon() const
{
    return get(roles().value(Role::Icon)).toUrl();
}

void CategoryNode::onChildrenCountChanged_()
{
    set(roles().value(Role::IsEmpty), getChildren().isEmpty());
    set(roles().value(Role::Icon), getChildren().isEmpty()
        ? QUrl("qrc:/category/icons/file-earmark.svg")
        : QUrl("qrc:/category/icons/folder.svg"));

    set(roles().value(Role::Extra), "Extra");
}
