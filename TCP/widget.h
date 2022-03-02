#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void newConnect();
    void disConnected();
    void readdata();

private:
    Ui::Widget *ui;
    QTcpSocket * tcpsocket;
    QTcpServer * tcpserver;



};

#endif // WIDGET_H
