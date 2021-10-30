#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.Setup();
    w.TemperatureLine();
    w.PressureLine();
    w.HumidityLine();
    w.ShowChart();
    w.resize(1250, 800);
    w.show();
    return a.exec();
}
