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
    Q_PROPERTY(int type READ type CONSTANT)
public:
    enum CategoryType
    {
        Group = 0,
        Entry,
    };

    CategoryNode(CategoryType type = Group, QObject *parent = nullptr);
    CategoryNode(const QString &name, CategoryType type = Group, QObject *parent = nullptr);

    enum Role
    {
        // roles by columns
        Name = Qt::UserRole + 1,

        // all other roles
        IsEmpty,
        Icon,
        Type,
        Api,
        Description,
        Auth,
        Https,
        Cors,
        Link,
        Category,
    };

    static const QHash<int, QByteArray> roles();
    QString name() const;
    void setName(const QString &val);
    bool isEmpty() const;
    QUrl icon() const;
    CategoryType type() const;

    void fromJson(const QByteArray &json);
private:
    void fromJsonEntry_(const QByteArray &json);
    void setApi_(const QString& val);
    void setDescription_(const QString& val);
    void setAuth_(const QString& val);
    void setHttps_(bool val);
    void setCors_(const QString& val);
    void setLink_(const QString& val);
    void setCategory_(const QString& val);
private slots:
    void onChildrenCountChanged_();
signals:
    void sigNameChanged();
    void sigFromJsonError(const QString &error);
};

#endif // CATEGORYNODE_H
