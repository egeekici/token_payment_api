#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&data,SIGNAL(qrdatareadyread(QByteArray)),this,SLOT(returnqrdata(QByteArray)));
    connect(&data,SIGNAL(paymentdatareadyread(QByteArray)),this,SLOT(returnpaymentdata(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::returnqrdata(QByteArray data1)
{
    ui->textBrowser->setText(data1);
}

void MainWindow::returnpaymentdata(QByteArray data2)
{
    ui->textBrowser_2->setText(data2);
}

void MainWindow::on_pushButton_clicked()
{
    QString id = ui->lineEdit->text();
    QString secret = ui->lineEdit_2->text();
    double amount = ui->lineEdit_3->text().toDouble();
    data.do_qr_request(amount,id,secret);

}
