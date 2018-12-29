#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon((QIcon(":/img/img/icon_3.pbm")));
    MainWindow w;
    w.show();

    return a.exec();
}
