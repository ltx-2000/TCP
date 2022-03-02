#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpserver = new QTcpServer(this);
    tcpserver->listen(QHostAddress::Any,7574);
    setWindowTitle("服务器：7574");
    tcpsocket = new QTcpSocket();
    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(newConnect()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::newConnect()
{
    tcpsocket = tcpserver->nextPendingConnection();
    QString ip = tcpsocket->peerAddress().toString();
    qint16 port = tcpsocket->peerPort();
    QString info = QString("[%1:%2]:已连接").arg(ip).arg(port);
    //QString settext = ui->rec_edit->placeholderText()+info;
    ui->rec_edit->append(info);
    connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(readdata()));
    connect(tcpsocket,SIGNAL(disconnected()),this,SLOT(disConnected()));
}

void Widget::disConnected()
{
    QTcpSocket *obj = (QTcpSocket*)sender();//掉线对象
    qDebug()<<obj->peerAddress().toString();//打印出掉线对象的ip
    QString ip = obj->peerAddress().toString();
    qint16 port = obj->peerPort();
    QString info = QString("[%1:%2]:已掉线").arg(ip).arg(port);
    ui->rec_edit->append(info);
}

void Widget::readdata()
{
    QByteArray buffer;
    QTcpSocket* obj = (QTcpSocket*)sender();
    buffer = obj->readAll();
    QString ip = obj->peerAddress().toString();
    qint16 port = obj->peerPort();
    QString back = QString(buffer);
    QString info = QString("[%1:%2]:%3").arg(ip).arg(port).arg(back);
    ui->rec_edit->append(info);
    back = QString("服务器返回：%1").arg(back);
    obj->write(back.toUtf8());
    ui->send_edit->append(back);
}
