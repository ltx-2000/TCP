#include "widget.h"
#include "clientform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    clientForm client;
    client.show();

    return a.exec();
}
