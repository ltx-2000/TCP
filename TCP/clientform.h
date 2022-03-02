#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QWidget>
#include <QTcpSocket>
namespace Ui {
class clientForm;
}

class clientForm : public QWidget
{
    Q_OBJECT

public:
    explicit clientForm(QWidget *parent = 0);
    ~clientForm();

    QTcpSocket* socket;
private:
    Ui::clientForm *ui;

public slots:
    void Readdata();
    void Connected();

    void Disconnected();

    void on_client_btn_clicked();
    void on_send_btn_clicked();
};

#endif // CLIENTFORM_H
