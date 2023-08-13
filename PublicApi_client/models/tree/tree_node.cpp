#include "tree_node.h"
#include "qvariant.h"

#include <QUuid>

namespace DataModels
{

TreeNode::TreeNode(QObject *parent)
    : QObject(parent)
    , root_(nullptr)
    , id_(qHash(QUuid::createUuid()))
{
}

void TreeNode::setRoot(TreeNode *node)
{
    root_ = node;
}

TreeNode* TreeNode::getRoot() const
{
    return root_;
}

TreeNode* TreeNode::getChild(int index) const
{
    if(index < 0 || index >= children_.count())
    {
        return nullptr;
    }

    return children_.at(index);
}

bool TreeNode::insert(TreeNode* node, int pos)
{
    if(pos > children_.count())
    {
        return false;
    }

    if(pos < 0)
    {
        pos = children_.count();
    }

    node->setRoot(this);
    children_.insert(pos, node);
    emit sigChildrenCountChanged();
    return true;
}

bool TreeNode::remove(TreeNode* node)
{
    if(!node)
    {
        return false;
    }

    const auto isOk = children_.removeOne(node);
    emit sigChildrenCountChanged();
    return isOk;
}

void TreeNode::clear()
{
    qDeleteAll(children_);
    children_.clear();
    emit sigChildrenCountChanged();
}

QList<TreeNode*> TreeNode::getChildren() const
{
    return children_;
}

int TreeNode::pos(bool fromRoot) const
{
    if(fromRoot)
    {
        auto totalPosition = pos(false);
        if(!root_)
        {
            return totalPosition;
        }

        return totalPosition + root_->pos(true) + 1;
    }
    else
    {
        return root_ ? root_->children_.indexOf(this) : 0;
    }
}

uint TreeNode::getId() const
{
    return id_;
}

void TreeNode::set(const QString &propertyName, const QVariant &val)
{
    setProperty(propertyName.toStdString().c_str(), val);
    emit sigPropertyChanged(propertyName, val);
}

QVariant TreeNode::get(const QString &propertyName) const
{
    return property(propertyName.toStdString().c_str());
}

}
