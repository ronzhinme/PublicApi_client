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
};

#endif // CATEGORYTREE_H
