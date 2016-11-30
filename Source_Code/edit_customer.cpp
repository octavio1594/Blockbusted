#include "edit_customer.h"
#include "ui_edit_customer.h"
#include <QWidget>
#include <QDesktopWidget>
#include <iostream>


using namespace std;


//Create Window and Automatically load Customer Table to view
edit_customer::edit_customer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_customer)
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
    model->setTable("Customer");
    model->select();
    ui->tableView->setModel(model);
    this->setFixedSize(boxWidth,boxHeight);
    ui->tableView->resize(innerFrameX,innerFrameY);
    ui->Exit->resize(innerFrameX*.20,innerFrameY*.15);
    ui->Exit->move(boxWidth/2-innerFrameX*.10,boxHeight*.85);

}

edit_customer::~edit_customer()
{
    delete ui;
}
