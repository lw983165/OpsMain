#include "MainWindow.hpp"
#include <QApplication>
#include <exception>
#include <QDebug>

int main(int argc, char *argv[])
{
    int status;

    try {
        QApplication a(argc, argv);
        MainWindow w;
        w.showMaximized();
        status = a.exec();
    } catch (std::exception &e) {
        qDebug() << e.what();
    }

    return status;
}
