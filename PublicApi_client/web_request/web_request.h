#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include "qqmlintegration.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WebRequest : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    WebRequest(QObject *parent = nullptr);
    ~WebRequest() = default;
    Q_INVOKABLE void requestGetJson(const QString &url);
private:
    QScopedPointer<QNetworkAccessManager> manager_;
signals:
    void sigRequestError(const QString &url, QNetworkReply::NetworkError err, int httpCode);
    void sigRequestCompleted(const QString &url, const QByteArray &reply);
};

#endif // CATEGORYTREE_H
