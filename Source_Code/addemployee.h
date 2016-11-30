#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class addEmployee;
}

class addEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit addEmployee(QWidget *parent = 0);
    ~addEmployee();

private slots:

    //Cancels out of sign in window
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::addEmployee *ui;
};

#endif // ADDEMPLOYEE_H
