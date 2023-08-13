#include "tree_model.h"

namespace DataModels
{

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , root_(new TreeNode(this))
{
}

TreeModel::~TreeModel()
{
    root_->clear();
}

void TreeModel::setFlags(QVector<Qt::ItemFlags> &&flags)
{
    flags_ = std::move(flags);
}

TreeNode *TreeModel::getNode(const QModelIndex &index) const
{
    return index.isValid()
            ? static_cast<DataModels::TreeNode*>(index.internalPointer())
            : root_.get();
}

void TreeModel::setRoleNames(const QHash<int, QByteArray> &roles)
{
    roles_.clear();
    roles_ = roles;
}
QStringList TreeModel::getHeaderNames() const
{
    return headerNames_;
}

void TreeModel::setHeaderNames(const QStringList &val)
{
    headerNames_ = val;
    columnCount_ = headerNames_.count();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    auto root = getNode(parent);
    auto child = root->getChild(row);
    return child ? createIndex(row, column, child) : QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
    {
        return QModelIndex();
    }

    const auto node = getNode(child);
    if(!node)
    {
        return QModelIndex();
    }

    const auto root = node->getRoot();
    return (root && root != root_.get())
            ? createIndex(root->pos(false), 0, root)
            : QModelIndex();
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if(parent.column() > 0)
    {
        return 0;
    }

    const auto root = getNode(parent);
    return root ? root->getChildren().count() : 0;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return columnCount_;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const auto node = getNode(index);
    return node->property(roles_[role]);
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!hasIndex(index.row(), index.column(), index.parent()) || role != Qt::EditRole || role != Qt::CheckStateRole)
    {
        return false;
    }

    const auto node = getNode(index);
    if(!node)
    {
        return false;
    }

    auto iter = roles_.begin();
    std::advance(iter, index.column());
    node->setProperty(iter.value(), value);
    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid() || index.column() >= flags_.count())
    {
        return Qt::NoItemFlags;
    }

    return flags_.at(index.column());
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    return roles_;
}

QModelIndex TreeModel::getIndexByNode_(TreeNode *node) const
{
    QVector<int> nodePositions;
    QModelIndex result;

    if(!node)
    {
        return result;
    }

    do
    {
        nodePositions.append(node->pos(false));
        node = node->getRoot();
    } while(node != nullptr);

    for(int i = nodePositions.size() - 2; i >= 0; --i)
    {
        result = index(nodePositions[i], 0, result);
    }

    return result;
}

bool TreeModel::insertNode(TreeNode *node, TreeNode *parent, int pos)
{
    return insertNode(node, getIndexByNode_(parent), pos);
}

bool TreeModel::insertNode(TreeNode *node, const QModelIndex &parent, int pos)
{
    auto parentNode = getNode(parent);
    const auto childrenCount = parentNode->getChildren().count();
    if(pos >= childrenCount)
    {
        return false;
    }

    if(pos < 0)
    {
        pos = childrenCount;
    }

    beginInsertRows(parent, pos, pos);
    const auto isOk = parentNode->insert(node, pos);
    endInsertRows();

    emit sigChildrenCountChanged(parent, childrenCount + 1, true);
    return isOk;
}

}
