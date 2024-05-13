#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    server = new Server();
    movie = new QMovie(":/new/gif/Tower.gif");
    ui->LoadingLabel->setMovie(movie);
    movie->start();
    movie->stop();

    QRegExp regex("\\d{0,5}"); // 0 to 5 digits
    QRegExpValidator *validator = new QRegExpValidator(regex, this);
    ui->portLineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete server;
}


void MainWindow::on_startServerBtn_clicked()
{

    if(server->startServer(ui->portLineEdit->text().toInt())){
        ui->outputWindow->append(":: Server Started Successfully...");
        if(ui->portLineEdit->text().toInt()==0)
            ui->outputWindow->append(":: Port Number:  12345");
        else
            ui->outputWindow->append(":: Port Number:  "+ui->portLineEdit->text());
        ui->portLineEdit->setDisabled(true);
        movie->start();
    }else{
        ui->outputWindow->append(":: Unable to SetUp Server. TRY AGAIN...");
    }
}


void MainWindow::on_stopServerBtn_clicked()
{
    if(server->stopServer()){
        ui->outputWindow->append(":: Server Stopped");
        ui->portLineEdit->setDisabled(false);
        movie->stop();
    }else{
        ui->outputWindow->append(":: Server is not Running...");
    }
}
