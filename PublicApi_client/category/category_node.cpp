#include "category_node.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CategoryNode::CategoryNode(CategoryType type, QObject *parent)
    : DataModels::TreeNode(parent)
{
    connect(this, &DataModels::TreeNode::sigChildrenCountChanged, this, &CategoryNode::onChildrenCountChanged_);

    setName("");
    onChildrenCountChanged_();
    set(roles().value(Role::Type), type);
}

CategoryNode::CategoryNode(const QString &name, CategoryType type, QObject *parent)
    : DataModels::TreeNode(parent)
{
    connect(this, &DataModels::TreeNode::sigChildrenCountChanged, this, &CategoryNode::onChildrenCountChanged_);

    setName(name);
    onChildrenCountChanged_();
    set(roles().value(Role::Type), type);
}

const QHash<int, QByteArray> CategoryNode::roles()
{
    static const QHash<int, QByteArray> hash
    {
        {CategoryNode::Role::Name, "name"},
        {CategoryNode::Role::IsEmpty, "isEmpty"},
        {CategoryNode::Role::Icon, "icon"},
        {CategoryNode::Role::Type, "type"},
        {CategoryNode::Role::Api, "api"},
        {CategoryNode::Role::Description, "description"},
        {CategoryNode::Role::Auth, "auth"},
        {CategoryNode::Role::Https, "https"},
        {CategoryNode::Role::Cors, "cors"},
        {CategoryNode::Role::Link, "link"},
        {CategoryNode::Role::Category, "category"},
    };

    return hash;
}

QString CategoryNode::name() const
{
    return get(roles().value(Role::Name)).toString();
}

void CategoryNode::setName(const QString &val)
{
    set(roles().value(Role::Name), val);
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
        //emit sigFromJsonError(jErr.errorString());
        return;
    }

    if(jDoc.isNull() || !jDoc.isObject())
    {
        return;
    }

    const auto jObj = jDoc.object();
    const auto count = jObj.value("count").toInt(0);
    if(count == 0)
    {
        return;
    }

    const auto jNodes = jObj.value("entries");
    if(!jNodes.isArray())
    {
        return;
    }

    const auto jNodesArr = jNodes.toArray();
    for(const auto jNode: jNodesArr)
    {
        if(!jNode.isObject())
        {
            continue;
        }

        const auto jNodeObj = jNode.toObject();
        auto node = new CategoryNode(CategoryType::Entry, this);
        node->fromJsonEntry_(QJsonDocument(jNodeObj).toJson(QJsonDocument::JsonFormat::Compact));
        insert(node);
    }
}

void CategoryNode::fromJsonEntry_(const QByteArray &json)
{
    clear();
    QJsonParseError jErr;
    const auto jDoc = QJsonDocument::fromJson(json, &jErr);

    if(jErr.error != QJsonParseError::NoError)
    {
        //emit sigFromJsonError(jErr.errorString());
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
        setDescription_(jDescription.toString());
    }

    const auto jAuth = jObj.value("Auth");
    if(!jAuth.isNull() && jAuth.isString())
    {
        setAuth_(jAuth.toString());
    }

    const auto jHttps = jObj.value("HTTPS");
    if(!jHttps.isNull() && jHttps.isBool())
    {
        setHttps_(jHttps.toBool());
    }

    const auto jCors = jObj.value("Cors");
    if(!jCors.isNull() && jCors.isString())
    {
        setCors_(jCors.toString());
    }

    const auto jLink = jObj.value("Link");
    if(!jLink.isNull() && jLink.isString())
    {
        setLink_(jLink.toString());
    }

    const auto jCategory = jObj.value("Category");
    if(!jCategory.isNull() && jCategory.isString())
    {
        setCategory_(jCategory.toString());
    }
}

void CategoryNode::setApi_(const QString &val)
{
    set(roles().value(Role::Api), val);
}

void CategoryNode::setDescription_(const QString &val)
{
    set(roles().value(Role::Description), val);
}

void CategoryNode::setAuth_(const QString &val)
{
    set(roles().value(Role::Auth), val);
}

void CategoryNode::setHttps_(bool val)
{
    set(roles().value(Role::Https), val);
}

void CategoryNode::setCors_(const QString &val)
{
    set(roles().value(Role::Cors), val);
}

void CategoryNode::setLink_(const QString &val)
{
    set(roles().value(Role::Link), val);
}

void CategoryNode::setCategory_(const QString &val)
{
    set(roles().value(Role::Category), val);
}

void CategoryNode::onChildrenCountChanged_()
{
    set(roles().value(Role::IsEmpty), getChildren().isEmpty());
    set(roles().value(Role::Icon), getChildren().isEmpty()
        ? QUrl("qrc:/category/icons/file-earmark.svg")
        : QUrl("qrc:/category/icons/folder.svg"));
}
