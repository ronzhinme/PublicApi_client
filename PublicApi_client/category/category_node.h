#ifndef CATEGORYNODE_H
#define CATEGORYNODE_H

#include "../models/tree/tree_node.h"
#include "qqmlintegration.h"
#include <QVariantList>

class CategoryNode : public DataModels::TreeNode
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString description READ getDescription CONSTANT)
    Q_PROPERTY(QString auth READ getAuth CONSTANT)
    Q_PROPERTY(bool https READ getHttps CONSTANT)
    Q_PROPERTY(QString cors READ getCors CONSTANT)
    Q_PROPERTY(QString link READ getLink CONSTANT)
public:
    enum CategoryType
    {
        Group = 0,
        Entry,
    };
    enum Role
    {
        // roles by columns
        Name = Qt::UserRole + 1,

        // all other roles
        IsEmpty,
        Icon,
        Type,
        Description,
        Auth,
        Https,
        Cors,
        Link,
    };
    static const QHash<int, QByteArray> roles();

    CategoryNode(CategoryType type = Group, QObject *parent = nullptr);
    CategoryNode(const QString &name, CategoryType type = Group, QObject *parent = nullptr);

    QString getName() const;
    void setName(const QString &val);
    QString getDescription() const;
    void setDescription(const QString& val);
    QString getAuth() const;
    void setAuth(const QString& val);
    bool getHttps() const;
    void setHttps(bool val);
    QString getCors() const;
    void setCors(const QString& val);
    QString getLink() const;
    void setLink(const QString& val);

    bool isEmpty() const;
    QUrl icon() const;
    CategoryType type() const;

    void fromJson(const QByteArray &json);
private slots:
    void onChildrenCountChanged_();
signals:
    void sigPropertiesChanged();
};

#endif // CATEGORYNODE_H
