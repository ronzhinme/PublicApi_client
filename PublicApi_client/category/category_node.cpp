#include "category_node.h"
#include "../models/role_to_string.h"

QVariantList CategoryRoles::roles()
{
    static const auto roles = QVariantList{"name"};
    return roles;
}

static QString roleToString(CategoryRoles::Role role)
{
    static const auto undefined = "undefined";
    if(role == CategoryRoles::Role::Undefined)
    {
        return undefined;
    }

    return DataModels::RoleToString::toString(role - (Qt::UserRole + 1), CategoryRoles::roles(), undefined);
}

static CategoryRoles::Role stringToRole(const QString &name)
{
    const auto index = DataModels::RoleToString::toRoleIndex(name, CategoryRoles::roles(), CategoryRoles::Role::Undefined);
    return static_cast<CategoryRoles::Role>(index != CategoryRoles::Role::Undefined
                ? index + (Qt::UserRole + 1)
                : index);
}

CategoryNode::CategoryNode(QObject *parent)
    : DataModels::TreeNode(parent)
{
}

CategoryNode::CategoryNode(const QString &name, QObject *parent)
    : DataModels::TreeNode(parent)
{
    setName(name);
}

QString CategoryNode::name() const
{
    return property(roleToString(CategoryRoles::Name).toStdString().c_str()).toString();
}

void CategoryNode::setName(const QString &val)
{
    setProperty(roleToString(CategoryRoles::Name).toStdString().c_str(), val);
}
