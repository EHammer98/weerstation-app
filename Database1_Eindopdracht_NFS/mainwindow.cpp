#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup connection with database
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("nfs");
    db.setUserName("root");
    db.setPassword("BkkOI.3a");

    //Show if connection is successful or failed
    if (db.open()){
        QMessageBox::information(this, "Database connection", "Connection successful!");

    }else{
        QMessageBox::information(this, "Database connection", "Connection failed");
    }

    //Show merken
    Model->setQuery("SELECT strMerk FROM tblMerk");
    ui->Merken->setModel(Model);
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

//Show Types with Logo and location
void MainWindow::on_Merken_clicked(const QModelIndex &index)
{
    //Get Types
    MerkModel->setQuery("SELECT * FROM tblmerk");
    IDMerk = MerkModel->record(index.row()).value("ID").toString();
    IDStad = MerkModel->record(index.row()).value("intStadID").toString();

    //Show Types
    MerkModel->setQuery("SELECT strType FROM tbltype WHERE intMerkID =" + IDMerk);
    ui->Types->setModel(MerkModel);

    //Get location of headquarters
    LocatieModel->setQuery("SELECT * FROM tblstad WHERE ID =" + IDStad);
    IDLand = LocatieModel->record(0).value("intLandID").toString();

    //Show location of headquarters
    LocatieModel->setQuery("SELECT strStad, strLand FROM tblstad INNER JOIN tblland ON tblstad.intLandID = tblland.ID WHERE tblland.ID =" + IDLand + " AND tblstad.ID =" + IDStad);
    ui->Hoofdkantoor->setModel(LocatieModel);

    //Get Logo
    ImageModel->setQuery("SELECT strLogo FROM tblmerk WHERE ID =" + IDMerk);
    QString strImage = ImageModel->record(0).value("strLogo").toString();

    //Show Logo
    QPixmap p;
    Image.load(strImage);
    ui->myLabel->setPixmap(p.fromImage(Image));

    //Empty Model view when a new merk is chosen
    TypeModel->setQuery("");
    ui->Modellen->setModel(TypeModel);
}

//Show Modellen with power
void MainWindow::on_Types_clicked(const QModelIndex &index)
{
    //Get Model
    TypeModel->setQuery("SELECT strMerk, tbltype.ID, strtype FROM tblmerk INNER JOIN tbltype ON tbltype.intMerkID = tblMerk.ID WHERE tblmerk.ID =" + IDMerk);
    IDType = TypeModel->record(index.row()).value("ID").toString();

    //Show Model with power in PK
    TypeModel->setQuery("SELECT strModel, CONCAT(intPK,' PK') FROM tbltypemodel LEFT JOIN tblmodel ON tbltypemodel.intModelID = tblmodel.ID Where intTypeID =" + IDType);
    ui->Modellen->setModel(TypeModel);

}

//Switch power between PK and kW
void MainWindow::on_VermogenButton_clicked(bool checked)
{
    //Switch power
    if(checked == false){
        TypeModel->setQuery("SELECT strModel, CONCAT(intPK,' PK') FROM tbltypemodel LEFT JOIN tblmodel ON tbltypemodel.intModelID = tblmodel.ID Where intTypeID =" + IDType);
    }else{
        TypeModel->setQuery("SELECT strModel, CONCAT(intkW,' kW') FROM tbltypemodel LEFT JOIN tblmodel ON tbltypemodel.intModelID = tblmodel.ID Where intTypeID =" + IDType);
    }

    //Show power
    ui->Modellen->setModel(TypeModel);
}
