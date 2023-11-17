#include "QtDMX.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDMX w;
    w.show();
    return a.exec();
}
