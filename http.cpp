#include "http.h"

http::http(QObject *parent) : QObject(parent)
{
    connect(qnam_qr,SIGNAL(finished(QNetworkReply*)), this, SLOT(reading_qr(QNetworkReply*)));
    connect(qnam_p, SIGNAL(finished(QNetworkReply*)), this, SLOT(reading_payment(QNetworkReply*)));
}

void http::do_qr_request(double amount1,QString id1,QString secret1)
{
    QUrl url("https://sandbox-api.payosy.com/api/get_qr_sale");
    id=id1.toUtf8();
    secret=secret1.toUtf8();
    amountt=amount1*100;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setRawHeader("x-ibm-client-id",id);
    request.setRawHeader("x-ibm-client-secret",secret);

    QJsonObject json;
    json.insert("totalReceiptAmount",(amountt));


    qnam_qr->post(request,QJsonDocument(json).toJson());

}

void http::reading_qr(QNetworkReply *rep)
{
    QByteArray bts = rep->readAll();
    emit(qrdatareadyread(bts));
    json_qr= QJsonDocument::fromJson(bts) ;

    payment(json_qr);

}

void http::reading_payment(QNetworkReply *rep2)
{
    QByteArray bts2 = rep2->readAll();
    emit(paymentdatareadyread(bts2));

}

void http::payment(QJsonDocument jsonn){
 //   qDebug() << jsonn;//}
 //   qDebug() << jsonn.object().keys();
 //   qDebug() << jsonn.object().value("QRdata");
//"returnCode", "returnDesc"
 //   qDebug() << jsonn.object().value("returnCode");
 //   qDebug() << jsonn.object().value("returnDesc");

    QString qr_data=jsonn.object().value("QRdata").toString();
    if(qr_data==""){
        qr_data="00000000000000000000000000000000000000000000000000";
    }
    QStringRef asd(&qr_data, 10, 3);
    double curid =asd.toDouble();
    QStringRef asdf(&qr_data, 20, 3);
    double var_rate=asdf.toDouble();
    double return_code=jsonn.object().value("returnCode").toDouble();
    //double amount=100;
    QString return_Desc;
    if(jsonn.object().value("returnDesc").toString()=="OK"){
        return_Desc="success";}


//ııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııı
QJsonObject o1,o2,json3;
QJsonArray a1,a2;




o1={
    {"paymentType",3},
    {"amount",amountt},
    {"currencyID",curid},
    {"vatRate",var_rate}
};


a1.append(o1);
o2.insert("paymentProcessorID",67);
o2.insert("paymentActionList",a1);
a2.append(o2);
json3.insert("returnCode",return_code);
json3.insert("returnDesc",return_Desc);
json3.insert("receiptMsgCustomer","beko Campaign/n2018");
json3.insert("receiptMsgMerchant","beko Campaign Merchant/n2018");
json3.insert("paymentInfoList",a2);
json3.insert("QRdata",qr_data);

 //  ııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııııı

   QUrl url("https://sandbox-api.payosy.com/api/payment");

   QNetworkRequest request(url);
   request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
   request.setRawHeader("x-ibm-client-id",id);
   request.setRawHeader("x-ibm-client-secret",secret);




   qnam_p->post(request,QJsonDocument(json3).toJson());



}


