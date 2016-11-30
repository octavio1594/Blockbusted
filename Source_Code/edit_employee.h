#ifndef EDIT_EMPLOYEE_H
#define EDIT_EMPLOYEE_H

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QDebug>
#include <QtGui>
#include <mainwindow.h>

namespace Ui {
class edit_employee;
}

class edit_employee : public QDialog
{
    Q_OBJECT

public:
    explicit edit_employee(QWidget *parent = 0);
    ~edit_employee();

private:
    Ui::edit_employee *ui;
    QSqlTableModel *model;
};

#endif // EDIT_EMPLOYEE_H
