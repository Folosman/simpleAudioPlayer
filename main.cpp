#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.setWindowIcon(QIcon("../SimpleAudioPlayer/Icons/Diablo"));
    w.resize(1280, 800);
    w.show();
    return a.exec();
}
