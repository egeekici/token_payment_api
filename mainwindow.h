#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "http.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void returnqrdata(QByteArray data1);
    void returnpaymentdata(QByteArray data2);
    void on_pushButton_clicked();

    private:
    Ui::MainWindow *ui;
    http data;
};

#endif // MAINWINDOW_H
