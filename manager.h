
#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>

typedef int money;

QT_BEGIN_NAMESPACE
namespace Ui { class Manager; }
QT_END_NAMESPACE

class Manager : public QMainWindow

{
    Q_OBJECT

public:
    Manager(QWidget *parent = nullptr);
    ~Manager();
    int findItem(QString title);
private slots:
    void balanceSlot();
    void buySlot();
    void addActive();

private:
    Ui::Manager *ui;
    bool flagBalance = false;
    money balance = 1000;
    QString currentTitle;
    int currentDividend,currentQuantity;
    money currentPrice;
    int currentRow = 0;

};

#endif // MANAGER_H
