#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <dbmanager.h>

namespace Ui {
class addCustomer;
}

class addCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit addCustomer(QWidget *parent = 0);
    ~addCustomer();

private slots:

    //Cancels out of sign in window
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::addCustomer *ui;
};

#endif // ADDCUSTOMER_H
