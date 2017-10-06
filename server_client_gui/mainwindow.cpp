#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("srv_clnt");
    db.setUserName("client");
    db.setPassword("client");
    bool ok = db.open();

    qDebug() << "Database open? " << ok;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refreshButton_clicked()
{

    qDebug() << "SELECT * FROM client";

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.exec("SELECT * FROM client");

    while (query.next()) {
           QString ip = query.value(0).toString();
           QString text = query.value(1).toString();
           ui->textBrowser->append(ip+": "+text+"\n");
           qDebug() << ip << ": " << text << "\n";
       }
    QSqlDatabase::database().commit();
}

void MainWindow::on_sendButton_clicked()
{
    qDebug() << "INSERT INTO client(IP, MSG) VALUES('" << ui->ipTextEdit->toPlainText() << "', '" << ui->sendTextEdit->toPlainText() << "')";

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO client(IP, MSG) VALUES(':ip', ':msg')");
    query.bindValue(":ip", ui->ipTextEdit->toPlainText());
    query.bindValue(":msg", ui->sendTextEdit->toPlainText());
    query.exec();
    QSqlDatabase::database().commit();
}
