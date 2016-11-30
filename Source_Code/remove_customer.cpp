#include "remove_customer.h"
#include "ui_remove_customer.h"
#include <QMessageBox>
#include <QWidget>
#include <QDesktopWidget>
#include <iostream>


using namespace std;

remove_customer::remove_customer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remove_customer)
{
    QRect rec = QApplication::desktop()->screenGeometry();
    const int scrnHeight = rec.height(); // returns the height of the screen.
    const int scrnWidth = rec.width(); // returns the width of the screen.
    double boxWidth = scrnWidth * .40;
    double boxHeight = scrnHeight * .40;
    int innerFrameX = boxWidth*.85;
    int innerFrameY = boxHeight*.85;
    ui->setupUi(this);
    this->resize(boxWidth,boxHeight);
    ui->groupBox->resize(innerFrameX,innerFrameY);
    ui->groupBox->move(boxWidth/2-innerFrameX/2,boxHeight/2-innerFrameY/2);
}

remove_customer::~remove_customer()
{
    delete ui;
}

void remove_customer::on_view_customer_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel;
    QSqlQuery* qry = new QSqlQuery;
    qry->prepare("SELECT * FROM Customer");
    qry->exec();
    model->setQuery(*qry);
    ui->cus_view->setModel(model);
}

void remove_customer::on_rem_customer_clicked()
{
    QString customerID;
    customerID = ui->customerID->text();
    QSqlQuery qry;
    qry.prepare("DELETE FROM Customer WHERE CustomerID='"+customerID+"'");
    if(qry.exec()){
        QMessageBox::critical(this, tr("Delete"), tr("Deleted!"));
    }
    else {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}

void remove_customer::on_cus_view_clicked(const QModelIndex &index)
{
    QString cus_id = ui->cus_view->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Customer WHERE CustomerID='"+cus_id+"' OR FirstName='"+cus_id+"' OR LastName='"+cus_id+"'");

    if(qry.exec()){
        while(qry.next()){
            ui->customerID->setText(qry.value(0).toString());
            ui->customer_fn->setText(qry.value(1).toString());
            ui->customer_ln->setText(qry.value(2).toString());
        }
    }
}
