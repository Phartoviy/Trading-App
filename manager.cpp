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
    for (int i = 0;i<ui->tableWidget_2->rowCount();i++)
    {
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem("0"));
    }
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(balanceSlot()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(buySlot()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(saleSlot()));
}

Manager::~Manager()
{
    delete ui;
}

int Manager::findItem(QString title)
{
    for (int i = 0;i<ui->tableWidget_2->rowCount();i++)
    {
        if (title == ui->tableWidget_2->item(i,0)->text())
            return i;
    }
    return -1;

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
    currentTitle = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();
    currentPrice = ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text().toInt();
    currentDividend = ui->tableWidget->item(ui->tableWidget->currentRow(),2)->text().toInt();
    currentQuantity = ui->tableWidget->item(ui->tableWidget->currentRow(),3)->text().toInt();
    if (balance > currentPrice)
    {
        balance = balance - currentPrice;
        if (flagBalance)
            ui->pushButton->setText(QString::number(balance));
    }

    addActive();
}

void Manager::addActive()
{
    int row = findItem(currentTitle);
    qDebug() << row;

    if (row >= 0)
    {
        int quantity = ui->tableWidget_2->item(row,3)->text().toInt();
        ui->tableWidget_2->setItem(row,3,new QTableWidgetItem(QString::number(quantity+1)));

    }
    else
    {
        ui->tableWidget_2->setItem(currentRow,0,new QTableWidgetItem(currentTitle));
        ui->tableWidget_2->setItem(currentRow,1,new QTableWidgetItem(QString::number(currentPrice)));
        ui->tableWidget_2->setItem(currentRow,2,new QTableWidgetItem(QString::number(currentDividend)));
        ui->tableWidget_2->setItem(currentRow++,3,new QTableWidgetItem(QString::number(1)));

    }

}

void Manager::saleSlot()
{

}



void Manager::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous) //slot magazine
{
    qDebug() << "currentChange";
}


void Manager::on_tableWidget_2_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)// slot active
{

}

