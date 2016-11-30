#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "emp_verification.h"
#include "addemployee.h"
#include "addcustomer.h"
#include "edit_inventory.h"
#include "dbmanager.h"
#include "edit_customer.h"
#include "edit_employee.h"
#include "remove_customer.h"
#include "remove_employee.h"
#include "view_inventory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DbManager* database = DbManager::Instance();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fts_clicked();

    void on_add_emp_clicked();

    void on_remove_emp_clicked();

    void on_view_emp_clicked();

    void on_edit_Inv_clicked();

    void on_check_in_clicked();

    void on_check_out_clicked();

    void on_add_Customer_clicked();

    void on_remove_Customer_clicked();

    void on_view_Customers_clicked();

    void on_view_Inv_clicked();

    void on_signInButton_clicked();

    void on_signOutButton_clicked();

    void on_Quit_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
