
#include "manager.h"
#include "./ui_manager.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QTableWidgetItem>

Manager::Manager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Manager)
{
    ui->setupUi(this);
    ui->pushButton->setFlat(true);
    ui->pushButton->setText("Balance*");

    ui->tableWidget->setRowCount(40);
    ui->tableWidget_2->setRowCount(40);
    ui->nameLabel->setText("Name: Pavel Dv.");


    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("trades.db");
    QString str = "SELECT * FROM securities";
    QString title;
    int price, dividend, quantity;
    if (dbase.open()){
        qDebug() << "Super openned!";
        QSqlQuery query;
        bool b = query.exec(str);
        QSqlRecord rec = query.record();
        int numberRow = 0;
        while(query.next())
        {
            title = query.value(rec.indexOf("title")).toString();
            price = query.value(rec.indexOf("price")).toInt();
            dividend = query.value(rec.indexOf("dividend")).toInt();
            quantity = query.value(rec.indexOf("quantity")).toInt();
            ui->tableWidget->setItem(numberRow,0,new QTableWidgetItem(title));
            ui->tableWidget->setItem(numberRow,1,new QTableWidgetItem(QString::number(price)));
            ui->tableWidget->setItem(numberRow,2,new QTableWidgetItem(QString::number(dividend)));
            ui->tableWidget->setItem(numberRow++,3,new QTableWidgetItem(QString::number(quantity)));
        }

    }
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(balanceSlot()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(buySlot()));
}

Manager::~Manager()
{
    delete ui;
}


void Manager::balanceSlot()
{
    (flagBalance)?flagBalance = false:flagBalance = true;
    if (flagBalance)
        ui->pushButton->setText(QString::number(balance));
    else
        ui->pushButton->setText("Balance*");
}

void Manager::buySlot()
{
    if (balance > ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text().toInt())
    {
        balance = balance - ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text().toInt();
        if (flagBalance)
            ui->pushButton->setText(QString::number(balance));
    }
}

