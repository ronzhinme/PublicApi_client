#ifndef CATEGORYNODE_H
#define CATEGORYNODE_H

#include "../models/tree/tree_node.h"
#include "qqmlintegration.h"
#include <QVariantList>

class CategoryNode : public DataModels::TreeNode
{
    QML_ELEMENT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool isEmpty READ isEmpty CONSTANT)
public:
    CategoryNode(QObject *parent = nullptr);
    CategoryNode(const QString &name, QObject *parent = nullptr);

    enum Role
    {
        // roles by columns
        Name = Qt::UserRole + 1,
        // all other roles
        IsEmpty
    };

    static const QHash<int, QByteArray> roles();
    QString name() const;
    void setName(const QString &val);
    bool isEmpty() const;
private slots:
    void onChildrenCountChanged_();
signals:
    void sigNameChanged();
};

#endif // CATEGORYNODE_H
