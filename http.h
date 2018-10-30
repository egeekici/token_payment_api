#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QDebug>
#include <QUrl>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include<QJsonArray>

class http : public QObject
{
    Q_OBJECT
public:
    explicit http(QObject *parent = nullptr);
    void do_qr_request(double,QString,QString);
    void payment(QJsonDocument);
signals:
    void qrdatareadyread(QByteArray);
    void paymentdatareadyread(QByteArray);
public slots:
    void reading_qr(QNetworkReply*);
    void reading_payment(QNetworkReply*);
private:
    QNetworkAccessManager *qnam_qr = new QNetworkAccessManager (this);
    QNetworkAccessManager *qnam_p=new QNetworkAccessManager(this);
    QByteArray id ;
    QByteArray secret;
    double amountt;
    QJsonDocument json_qr;

};

#endif // HTTP_H
