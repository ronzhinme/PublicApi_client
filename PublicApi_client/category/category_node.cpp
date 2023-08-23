#include "category_node.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CategoryNode::CategoryNode(CategoryType type, QObject *parent)
    : DataModels::TreeNode(parent)
{
    connect(this, &DataModels::TreeNode::sigChildrenCountChanged, this, &CategoryNode::onChildrenCountChanged_);

    const QString emptyString;
    setName(emptyString);
    setAuth(emptyString);
    setCors(emptyString);
    setDescription(emptyString);
    setLink(emptyString);
    setHttps(false);

    onChildrenCountChanged_();
    set(roles().value(Role::Type), type);
}

CategoryNode::CategoryNode(const QString &name, CategoryType type, QObject *parent)
    : DataModels::TreeNode(parent)
{
    connect(this, &DataModels::TreeNode::sigChildrenCountChanged, this, &CategoryNode::onChildrenCountChanged_);

    setName(name);

    const QString emptyString;
    setAuth(emptyString);
    setCors(emptyString);
    setDescription(emptyString);
    setLink(emptyString);

    onChildrenCountChanged_();
    set(roles().value(Role::Type), type);
}

const QHash<int, QByteArray> CategoryNode::roles()
{
    static const QHash<int, QByteArray> hash
    {
        {CategoryNode::Role::Name, "nameRole"},
        {CategoryNode::Role::IsEmpty, "isEmptyRole"},
        {CategoryNode::Role::Icon, "iconRole"},
        {CategoryNode::Role::Type, "typeRole"},
        {CategoryNode::Role::Description, "descriptionRole"},
        {CategoryNode::Role::Auth, "authRole"},
        {CategoryNode::Role::Https, "httpsRole"},
        {CategoryNode::Role::Cors, "corsRole"},
        {CategoryNode::Role::Link, "linkRole"},
    };

    return hash;
}

QString CategoryNode::getName() const
{
    return get(roles().value(Role::Name)).toString();
}

QString CategoryNode::getDescription() const
{
    return get(roles().value(Role::Description)).toString();
}

void CategoryNode::setName(const QString &val)
{
    const auto propName = roles().value(Role::Name);
    set(propName, val);
    emit sigPropertyChanged(propName, val);
}

bool CategoryNode::isEmpty() const
{
    return get(roles().value(Role::IsEmpty)).toBool();
}

QUrl CategoryNode::icon() const
{
    return get(roles().value(Role::Icon)).toUrl();
}

CategoryNode::CategoryType CategoryNode::type() const
{
    return static_cast<CategoryNode::CategoryType>(get(roles().value(Role::Type)).toInt());
}

void CategoryNode::fromJson(const QByteArray &json)
{
    clear();
    QJsonParseError jErr;
    const auto jDoc = QJsonDocument::fromJson(json, &jErr);

    if(jErr.error != QJsonParseError::NoError)
    {
        return;
    }

    if(jDoc.isNull() || !jDoc.isObject())
    {
        return;
    }

    const auto jObj = jDoc.object();
    const auto jApi = jObj.value("API");
    if(!jApi.isNull() && jApi.isString())
    {
        setName(jApi.toString());
    }

    const auto jDescription = jObj.value("Description");
    if(!jDescription.isNull() && jDescription.isString())
    {
        setDescription(jDescription.toString());
    }

    const auto jAuth = jObj.value("Auth");
    if(!jAuth.isNull() && jAuth.isString())
    {
        setAuth(jAuth.toString());
    }

    const auto jHttps = jObj.value("HTTPS");
    if(!jHttps.isNull() && jHttps.isBool())
    {
        setHttps(jHttps.toBool());
    }

    const auto jCors = jObj.value("Cors");
    if(!jCors.isNull() && jCors.isString())
    {
        setCors(jCors.toString());
    }

    const auto jLink = jObj.value("Link");
    if(!jLink.isNull() && jLink.isString())
    {
        setLink(jLink.toString());
    }
}

void CategoryNode::setDescription(const QString &val)
{
    const auto propName = roles().value(Role::Description);
    set(propName, val);
    emit sigPropertyChanged(propName, val);
}

QString CategoryNode::getAuth() const
{
    return get(roles().value(Role::Auth)).toString();
}

void CategoryNode::setAuth(const QString &val)
{
    const auto propName = roles().value(Role::Auth);
    set(propName, val);
    emit sigPropertyChanged(propName, val);
}

bool CategoryNode::getHttps() const
{
    return get(roles().value(Role::Https)).toBool();
}

void CategoryNode::setHttps(bool val)
{
    const auto propName = roles().value(Role::Https);
    set(propName, val);
    emit sigPropertyChanged(propName, val);
}

QString CategoryNode::getCors() const
{
    return get(roles().value(Role::Cors)).toString();
}

void CategoryNode::setCors(const QString &val)
{
    const auto propName = roles().value(Role::Cors);
    set(propName, val);
    emit sigPropertyChanged(propName, val);
}

QString CategoryNode::getLink() const
{
    return get(roles().value(Role::Link)).toString();
}

void CategoryNode::setLink(const QString &val)
{
    const auto propName = roles().value(Role::Link);
    set(propName, val);
    emit sigPropertyChanged(propName, val);
}

void CategoryNode::onChildrenCountChanged_()
{
    const auto isEmpty = getChildren().isEmpty();
    const auto isGroup = get(roles().value(Role::Type)).toInt() == CategoryNode::CategoryType::Group;
    set(roles().value(Role::IsEmpty), isEmpty);
    set(roles().value(Role::Icon), isGroup
        ? (isEmpty ? QUrl("qrc:/category/icons/folder.svg") : QUrl("qrc:/category/icons/folder-fill.svg"))
        : QUrl("qrc:/category/icons/file-earmark.svg"));
}
