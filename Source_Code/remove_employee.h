#ifndef REMOVE_EMPLOYEE_H
#define REMOVE_EMPLOYEE_H

#include <QDialog>
#include "mainwindow.h"
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class remove_employee;
}

class remove_employee : public QDialog
{
    Q_OBJECT

public:
    explicit remove_employee(QWidget *parent = 0);
    ~remove_employee();

private slots:
    void on_view_emp_clicked();

    void on_emp_view_clicked(const QModelIndex &index);

    void on_rem_emp_clicked();

private:
    Ui::remove_employee *ui;
};

#endif // REMOVE_EMPLOYEE_H
