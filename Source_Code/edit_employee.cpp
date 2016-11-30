#include "edit_employee.h"
#include "ui_edit_employee.h"
#include <QWidget>
#include <QDesktopWidget>
#include <iostream>



//Create Window and Automatically load Employee Table to view
//Excludes GM from being loaded and thus
//Prevents GM from being altered or removed
edit_employee::edit_employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_employee)
{
    QRect rec = QApplication::desktop()->screenGeometry();
    const int scrnHeight = rec.height(); // returns the height of the screen.
    const int scrnWidth = rec.width(); // returns the width of the screen.
    double boxWidth = scrnWidth * .50;
    double boxHeight = scrnHeight * .50;
    int innerFrameX = boxWidth*.98;
    int innerFrameY = boxHeight*.80;
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("Employee");
    model->setFilter("EmpID != 1000");
    model->select();
    ui->tableView->setModel(model);
    this->setFixedSize(boxWidth,boxHeight);
    ui->tableView->resize(innerFrameX,innerFrameY);
    ui->Exit->resize(innerFrameX*.20,innerFrameY*.15);
    ui->Exit->move(boxWidth/2-innerFrameX*.10,boxHeight*.85);
}

edit_employee::~edit_employee()
{
    delete ui;
}
