#include "clientform.h"
#include "ui_clientform.h"

clientForm::clientForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientForm)
{
    ui->setupUi(this);
    ui->ip_line->setText("128.0.0.1");
    ui->port_line->setText("7574");
    socket = new QTcpSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(Readdata()));
    connect(socket,SIGNAL(connected()),this,SLOT(Connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(Disconnected()));

}

clientForm::~clientForm()
{
    delete ui;
}

void clientForm::Readdata()
{
    QString msg = socket->readAll();
    qDebug()<<msg;
    ui->recEdit_2->append(msg);
}

void clientForm::Connected()
{
    ui->client_btn->setText("断开");

}

void clientForm::Disconnected()
{
    ui->client_btn->setText("连接");;
}

void clientForm::on_client_btn_clicked()
{
    if("连接"==ui->client_btn->text())
    {
        socket->connectToHost(ui->ip_line->text(),ui->port_line->text().toInt());
    }
    else
    {
        socket->disconnectFromHost();
    }
}

void clientForm::on_send_btn_clicked()
{
    QString msg = ui->sendEdit->toPlainText();
    socket->write(msg.toUtf8());
}
