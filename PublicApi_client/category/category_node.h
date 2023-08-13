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
    Q_PROPERTY(QUrl icon READ icon CONSTANT)
public:
    CategoryNode(QObject *parent = nullptr);
    CategoryNode(const QString &name, QObject *parent = nullptr);

    enum Role
    {
        // roles by columns
        Name = Qt::UserRole + 1,
        Extra,
        // all other roles
        IsEmpty,
        Icon,
    };

    static const QHash<int, QByteArray> roles();
    QString name() const;
    void setName(const QString &val);
    bool isEmpty() const;
    QUrl icon() const;
private slots:
    void onChildrenCountChanged_();
signals:
    void sigNameChanged();
};

#endif // CATEGORYNODE_H
