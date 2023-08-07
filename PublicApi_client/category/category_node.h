#ifndef CATEGORYNODE_H
#define CATEGORYNODE_H

#include "../models/tree/tree_node.h"
#include "qqmlintegration.h"
#include <QVariantList>

class CategoryRoles final
{
public:
    enum Role
    {
        Undefined = -1,
        Name = Qt::UserRole + 1
    };

    static QVariantList roles();
};

class CategoryNode : public DataModels::TreeNode
{
    Q_GADGET
    QML_ELEMENT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    CategoryNode(QObject *parent = nullptr);
    CategoryNode(const QString &name, QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &val);
};

#endif // CATEGORYNODE_H
