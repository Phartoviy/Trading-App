
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
private slots:
    void balanceSlot();
    void buySlot();
private:
    Ui::Manager *ui;
    bool flagBalance = false;
    money balance = 1000;
};

#endif // MANAGER_H
