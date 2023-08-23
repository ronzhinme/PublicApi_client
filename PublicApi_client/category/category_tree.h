#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include "../models/tree/tree_model.h"

class CategoryTree : public DataModels::TreeModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    CategoryTree(QObject *parent = nullptr);
    ~CategoryTree() = default;

    Q_INVOKABLE void fromJson(const QByteArray &json);
    Q_INVOKABLE void entriesFromJson(const QString &url, const QByteArray &json);
signals:
    void sigFromJsonError(const QString &error);
};

#endif // CATEGORYTREE_H
