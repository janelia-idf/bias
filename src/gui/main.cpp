#include <QApplication>
#include <QDialog>

#include "main_window.hpp"


int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec();
}
