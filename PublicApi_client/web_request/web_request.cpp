#include "web_request.h"

#include <QNetworkRequest>
#include <QNetworkReply>

WebRequest::WebRequest(QObject *parent)
    :QObject(parent)
    , manager_(new QNetworkAccessManager(this))
{
}

void WebRequest::requestGetJson(const QString &url, const QByteArray &data)
{
    if(!manager_)
    {
        return;
    }

    QNetworkRequest newRequest(url);
    newRequest.setRawHeader("Content-Type", "application/json; charset=utf-8");
    newRequest.setRawHeader("Accept", "application/json");

    QNetworkReply* reply = manager_->get(newRequest);
    connect(reply, &QNetworkReply::finished, this, [reply, newRequest, this]()
    {
        int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const auto &err = reply->error();
        if ((err != QNetworkReply::NoError) || (httpStatus == 0))
        {
            emit sigRequestError(err, httpStatus);
        }
        else
        {
            emit sigRequestCompleted(reply->readAll());
        }

        reply->abort();
        reply->deleteLater();
    });
}

