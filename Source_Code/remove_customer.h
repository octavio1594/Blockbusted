#ifndef REMOVE_CUSTOMER_H
#define REMOVE_CUSTOMER_H

#include <QDialog>
#include "mainwindow.h"
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class remove_customer;
}

class remove_customer : public QDialog
{
    Q_OBJECT

public:
    explicit remove_customer(QWidget *parent = 0);
    ~remove_customer();

private slots:

    void on_view_customer_clicked();

    void on_rem_customer_clicked();

    void on_cus_view_clicked(const QModelIndex &index);

private:
    Ui::remove_customer *ui;
};

#endif // REMOVE_CUSTOMER_H
