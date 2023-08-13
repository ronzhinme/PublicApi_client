#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QtQml/qqmlregistration.h>
#include "tree_node.h"

namespace DataModels
{

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeModel(QObject *parent = nullptr);
    ~TreeModel();

    void setFlags(QVector<Qt::ItemFlags> &&flags);
    void setRoleNames(const QHash<int, QByteArray> &roles);
    QStringList getHeaderNames() const;
    void setHeaderNames(const QStringList &val);
    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public:
    Q_INVOKABLE DataModels::TreeNode* getNode(const QModelIndex &index) const;

protected:
    QModelIndex getIndexByNode_(TreeNode *node) const;
    bool insertNode(TreeNode *node, TreeNode *parent, int pos = -1);
    bool insertNode(TreeNode *node, const QModelIndex &parent, int pos = -1);
    bool deleteNode(TreeNode *node, TreeNode *parent);

private:
    static constexpr int columnCount_{1};
    QScopedPointer<TreeNode> root_;
    QHash<int, QByteArray> roles_;
    QVector<Qt::ItemFlags> flags_;
    QStringList headerNames_;
signals:
    void sigChildrenCountChanged(const QModelIndex &index, int count, bool isAdd);
};

}
#endif // TREEMODEL_H
