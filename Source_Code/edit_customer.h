#ifndef EDIT_CUSTOMER_H
#define EDIT_CUSTOMER_H

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QDebug>
#include <QtGui>
#include <mainwindow.h>

namespace Ui {
class edit_customer;
}

class edit_customer : public QDialog
{
    Q_OBJECT

public:
    explicit edit_customer(QWidget *parent = 0);
    ~edit_customer();

private:
    Ui::edit_customer *ui;
    QSqlTableModel *model;
};

#endif // EDIT_CUSTOMER_H
