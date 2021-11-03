#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.Setup();
    w.TemperatureLine();
    w.PressureLine();
    w.HumidityLine();
    w.show();
    w.ShowChart();
    return a.exec();
}
