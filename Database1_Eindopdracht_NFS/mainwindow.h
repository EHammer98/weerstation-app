#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QTreeView>
#include <QObject>
#include <QLabel>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Merken_clicked(const QModelIndex &index);

    void on_Types_clicked(const QModelIndex &index);

    void on_VermogenButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");    // create batabase

    //Set SqlQueryModel for each view
    QSqlQueryModel *MerkModel = new QSqlQueryModel;
    QSqlQueryModel *TypeModel = new QSqlQueryModel;
    QSqlQueryModel *LocatieModel = new QSqlQueryModel;
    QSqlQueryModel *Model = new QSqlQueryModel;
    QSqlQueryModel *ImageModel = new QSqlQueryModel;

    //Create Image for Logo
    QImage Image;

    //Create a String for each ID
    QString IDMerk;
    QString IDType;
    QString IDStad;
    QString IDLand;
};
#endif // MAINWINDOW_H
