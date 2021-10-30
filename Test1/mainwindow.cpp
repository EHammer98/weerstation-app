#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //setup database connection

    ui->setupUi(this);
    db.setHostName("databases.aii.avans.nl");
    db.setPort(3306);
    db.setDatabaseName("bpeters4_db2");
    db.setUserName("bpeters4");
    db.setPassword("Ab12345");

   if (db.open()){
       QMessageBox::information(this, "Succesfull", "Connection to database established");

   }else{
       QMessageBox::information(this, "ERROR", "Connection to database failed");
   }
}

MainWindow::~MainWindow()
{
  db.close();
  delete ui;
}

//Create Chart
void MainWindow::Setup()
{
     qModel = new QSqlQueryModel();
     qModel->setQuery("SELECT count(ID) FROM tblsensordata");
     max = qModel->record(0).value("count(ID)").toInt();

    chart->legend()->hide();
    chart->setTitle("WeatherStation Group E");
    chart->title();

    x->setTickCount(10);
    Formatx = "hh:mm dd-MM";
    x->setFormat(Formatx);
    chart->addAxis(x, Qt::AlignBottom);
    x->setTitleText("Time");
    x->setLabelsAngle(90);
}

//Create series for temperature for chart
void MainWindow::TemperatureLine()
{   //retreive data from db and store in db-model
    qModel = new QSqlQueryModel();
    qModel->setQuery("SELECT intTemp, dtDateTime FROM tblsensordata");

    //create line from data
    for(int i = 0; i<max ; i++ ){
    int temp = qModel->record(i).value("intTemp").toInt();
    QDateTime temp2;
    temp2 = qModel->record(i).value("dtDateTime").toDateTime();
    TempLine->append(temp2.toMSecsSinceEpoch(), temp);
    }
    chart->addSeries(TempLine);

    //create y-axis and connect to line
    QValueAxis *y = new QValueAxis;
    y->setLinePenColor(TempLine->pen().color());
    chart->addAxis(y, Qt::AlignLeft);
    TempLine->attachAxis(x);
    TempLine->attachAxis(y);
    y->setTitleText("Temperature (Degrees Celcius)");
    y->setTitleBrush(TempLine->pen().color());

}

    //Create series for pressure for chart
void MainWindow::PressureLine()
{   //retreive data from db and store in db-model
    qModel = new QSqlQueryModel();
    qModel->setQuery("SELECT intPress, dtDateTime FROM tblsensordata");

    //create line from data
    for(int i = 0; i<max ; i++ ){
    int temp = qModel->record(i).value("intPress").toInt();
    QDateTime temp2;
    temp2 = qModel->record(i).value("dtDateTime").toDateTime();
    PresLine->append(temp2.toMSecsSinceEpoch(), temp);
    }
    chart->addSeries(PresLine);

    //create y-axis and connect to line
    QValueAxis *y = new QValueAxis;
    y->setLinePenColor(PresLine->pen().color());
    chart->addAxis(y, Qt::AlignRight);
    PresLine->attachAxis(x);
    PresLine->attachAxis(y);
    y->setTitleText("Pressure (Pa)");
    y->setTitleBrush(PresLine->pen().color());
}

//Create series for humidity for chart
void MainWindow::HumidityLine()
{
    //retreive data from db and store in db-model
    qModel = new QSqlQueryModel();
    qModel->setQuery("SELECT intHum, dtDateTime FROM tblsensordata");

    //create line from data
    for(int i = 0; i<max ; i++ ){
    int temp = qModel->record(i).value("intHum").toInt();
    QDateTime temp2;
    temp2 = qModel->record(i).value("dtDateTime").toDateTime();
    HumLine->append(temp2.toMSecsSinceEpoch(), temp);
    }
    chart->addSeries(HumLine);

    //create y-axis and connect to line
    QValueAxis *y = new QValueAxis;
    y->setLinePenColor(HumLine->pen().color());
    chart->addAxis(y, Qt::AlignLeft);
    HumLine->attachAxis(x);
    HumLine->attachAxis(y);
    y->setTitleText("Humidity (relative %)");
    y->setTitleBrush(HumLine->pen().color());
}

void MainWindow::ShowChart()
{
    chart->resize(1000,600);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addItem(chart);

    ui->TestView->setScene(scene);
}

void MainWindow::on_TempBut_clicked(bool checked)
{
    if(checked == true){
        TempLine->hide();
    }else{
        TempLine->show();
    }
}

void MainWindow::on_PresBut_clicked(bool checked)
{
    if(checked == true){
        PresLine->hide();
    }else{
        PresLine->show();
    }
}

void MainWindow::on_HumBut_clicked(bool checked)
{
    if(checked == true){
        HumLine->hide();
    }else{
        HumLine->show();
    }
}

void MainWindow::on_DayBut_clicked()
{
    Formatx = "dd/MM hh:mm";
    x->setFormat(Formatx);
}

void MainWindow::on_HourBut_clicked()
{
    Formatx = "hh:mm";
    x->setFormat(Formatx);
}

void MainWindow::on_WeekBut_clicked()
{
    Formatx = "dddd";
    x->setFormat(Formatx);
}
