#include <QApplication>

#include <mainwindow.h>
#include <analogclock.h>

#include <SerialPortWidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //AnalogClock clock;
    //clock.show();

    //SerialPortWidget port;
    //port.show();

    return a.exec();
}
