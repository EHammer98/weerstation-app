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

   //Check connection
   if (db.open()){
       qModel = new QSqlQueryModel();
       qModel->setQuery("SELECT count(ID) FROM tblsensordata");
       max = qModel->record(0).value("count(ID)").toInt();

       qModel->setQuery("SELECT intStationErrors FROM tblsensordata");
       int count = 0;
       for(int i = 0; i < max; i++){
           int temp = qModel->record(i).value("intStationErrors").toInt();                          //An error from stm32
           if(temp != 0){
              count++;
           }
       }
       if(count == 0){
           QMessageBox::information(this, "Succesfull", "Connection to database established");      //No errors
       }else{
           QMessageBox::information(this, "ERROR", "Connection to STM32 failed");                   //1 or more errors from stm32
           db.close();
           delete ui;
       }


   }else{
       QMessageBox::information(this, "ERROR", "Connection to database failed");                    //An error with connection to database
       delete ui;
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
    temp2 = temp2.addSecs(-60 * 60);                                        //Change time to wintertime instead of summertime
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
    temp2 = temp2.addSecs(-60 * 60);                                        //Change time to wintertime instead of summertime
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
    temp2 = temp2.addSecs(-60 * 60);                                        //Change time to wintertime instead of summertime
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

//Set chart in view to show it
void MainWindow::ShowChart()
{
    chart->resize(1000,600);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addItem(chart);

    ui->View->setScene(scene);
}

//Hide or show Temperatureline in chart
void MainWindow::on_TempBut_clicked(bool checked)
{
    if(checked == true){
        TempLine->hide();
    }else{
        TempLine->show();
    }
}

//Hide or show Pressureline in chart
void MainWindow::on_PresBut_clicked(bool checked)
{
    if(checked == true){
        PresLine->hide();
    }else{
        PresLine->show();
    }
}

//Hide or show Humidityline in chart
void MainWindow::on_HumBut_clicked(bool checked)
{
    if(checked == true){
        HumLine->hide();
    }else{
        HumLine->show();
    }
}

//Change Format from X-axis to date with time
void MainWindow::on_DayBut_clicked()
{
    Formatx = "dd/MM hh:mm";
    x->setFormat(Formatx);
}

//Change Format from X-axis to hours and minutes
void MainWindow::on_HourBut_clicked()
{
    Formatx = "hh:mm";
    x->setFormat(Formatx);
}

//Change Format from X-axis to weekday
void MainWindow::on_WeekBut_clicked()
{
    Formatx = "dddd";
    x->setFormat(Formatx);
}
