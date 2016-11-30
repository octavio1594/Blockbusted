#include "remove_employee.h"
#include "ui_remove_employee.h"
#include <QMessageBox>
#include <QWidget>
#include <QDesktopWidget>
#include <iostream>


using namespace std;

remove_employee::remove_employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remove_employee)
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

remove_employee::~remove_employee()
{
    delete ui;
}

void remove_employee::on_view_emp_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery();
    qry->prepare("SELECT * FROM Employee");
    qry->exec();
    model->setQuery(*qry);
    ui->emp_view->setModel(model);
    //qDebug() << (model->rowCounter());
}

void remove_employee::on_emp_view_clicked(const QModelIndex &index)
{
    QString emp_id = ui->emp_view->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Employee WHERE EmpID='"+emp_id+"' OR FirstName='"+emp_id+"' OR LastName='"+emp_id+"'");

    if(qry.exec()){
        while(qry.next()){
            ui->empId->setText(qry.value(0).toString());
            ui->emp_fn->setText(qry.value(1).toString());
            ui->emp_ln->setText(qry.value(2).toString());
        }
    }
}

void remove_employee::on_rem_emp_clicked()
{
    QString empId;
    empId = ui->empId->text();
    if(empId == "1000"){
        QMessageBox::critical(this, tr("ERROR"), tr("Insufficient privileges!\nCannot delete GM"));
    }
    else{
        QSqlQuery qry;
        qry.prepare("DELETE FROM Employee WHERE EmpID='"+empId+"'");
        if(qry.exec()){
            QMessageBox::critical(this, tr("Delete"), tr("Deleted!"));
        }
        else {
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }
    }

}
