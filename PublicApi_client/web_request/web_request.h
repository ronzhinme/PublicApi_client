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
    Q_INVOKABLE void requestGetJson(const QString &url, const QByteArray &data);
private:
    QScopedPointer<QNetworkAccessManager> manager_;
signals:
    void sigRequestError(QNetworkReply::NetworkError err, int httpCode);
    void sigRequestCompleted(const QByteArray &reply);
};

#endif // CATEGORYTREE_H
