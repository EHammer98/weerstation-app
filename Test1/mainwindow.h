#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtSql>                // for sql commands
#include <QSqlDatabase>
#include <QtCharts>
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QString>
#include <QtDebug>              // debugging purposes
#include <QTableView>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCore/QDateTime>
#include <QtCharts/QDateTimeAxis>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCharts/QValueAxis>
#include <QResizeEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

        void Setup();
        void TemperatureLine();
        void PressureLine();
        void HumidityLine();
        void ShowChart();

protected:
        void resizeEvent(QResizeEvent *e);

private slots:
        void on_TempBut_clicked(bool checked);

        void on_PresBut_clicked(bool checked);

        void on_HumBut_clicked(bool checked);

        void on_DayBut_clicked();

        void on_HourBut_clicked();

        void on_WeekBut_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");      //Create batabase
    QSqlQueryModel *qModel;                                     //The QSqlQueryModel class provides a read-only data model for SQL result sets

    QChart *chart = new QChart();                               //Create chart
    QDateTimeAxis *x = new QDateTimeAxis;                       //Create x axis

    //Create lines
    QLineSeries *TempLine = new QLineSeries;
    QLineSeries *PresLine = new QLineSeries;
    QLineSeries *HumLine = new QLineSeries;

    QGraphicsScene *scene = new QGraphicsScene;                 //Create GraphicsScene for chart

    QString Formatx;                                            //Create string for changing format X axis
    int max;                                                    //Create integer for setting the amount rows of data
};


#endif // MAINWINDOW_H
