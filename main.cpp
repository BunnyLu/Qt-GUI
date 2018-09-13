#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.setuplabel();  //initialize index and label array

    w.show();
 //   w.loadimage();
    return a.exec();
}
