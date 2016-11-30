#include "inventory_count.h"
#include "ui_inventory_count.h"
#include <QMessageBox>
#include <QWidget>
#include <QDesktopWidget>
#include <iostream>


inventory_count::inventory_count(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inventory_count)
{
    QRect rec = QApplication::desktop()->screenGeometry();
    const int scrnHeight = rec.height(); // returns the height of the screen.
    const int scrnWidth = rec.width(); // returns the width of the screen.
    double boxWidth = scrnWidth * .50;
    double boxHeight = scrnHeight * .50;
    int innerFrameX = boxWidth*.90;
    int innerFrameY = boxHeight*.75;
    ui->setupUi(this);
    this->resize(boxWidth,boxHeight);
    ui->invCount_groupBox->resize(innerFrameX,innerFrameY);

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT * FROM InventoryCount");
    query->exec();
    model->setQuery(*query);
    ui->inventoryCount->setModel(model);
    qDebug() << (model->rowCount());
    this->setFixedSize(boxWidth,boxHeight);
    ui->inventoryCount->resize(innerFrameX,innerFrameY);
    ui->exit->resize(innerFrameX*.20,innerFrameY*.12);
    ui->exit->move(boxWidth/2-innerFrameX*.10,boxHeight*.85);

}

inventory_count::~inventory_count()
{
    delete ui;
}

void inventory_count::on_inventoryCount_clicked(const QModelIndex &index)
{
    QString val = ui->inventoryCount->model()->data(index).toString();

    QSqlQuery qryCount;
    qryCount.prepare("SELECT * FROM InventoryCount WHERE ProductID='"+val+"' OR ProductName='"+val+"' OR Quantity='"+val+"' OR Counted='"+val+"' OR Variance='"+val+"'");

    if(qryCount.exec())
    {
        while(qryCount.next())
        {
            ui->id_input->setText(qryCount.value(0).toString());
            ui->name_input->setText(qryCount.value(1).toString());
            ui->quantity_input->setText(qryCount.value(2).toString());
            ui->count_input->setText(qryCount.value(3).toString());
            ui->variance_input->setText(qryCount.value(4).toString());

            ui->id_input->setReadOnly(true);
            ui->name_input->setReadOnly(true);
            ui->quantity_input->setReadOnly(true);
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Base, Qt::lightGray);
            palette->setColor(QPalette::Text, Qt::black);
            ui->id_input->setPalette(*palette);
            ui->name_input->setPalette(*palette);
            ui->quantity_input->setPalette(*palette);
        }
    }
    else {
        QMessageBox::critical(this, tr("error::"), qryCount.lastError().text());
    }
}

void inventory_count::on_edit_invCount_clicked()
{
    QString pid, name, quantity, counted, variance;
    pid = ui->id_input->text();
    name = ui->name_input->text();
    quantity = ui->quantity_input->text();
    counted = ui->count_input->text();
    int var = counted.toInt() - quantity.toInt();
    variance = QString::number(var);
    ui->variance_input->setText(variance);

    QSqlQuery qryCount;
    qryCount.prepare("UPDATE InventoryCount SET ProductID='"+pid+"', ProductName='"+name+"', Quantity='"+quantity+"', Counted='"+counted+"', Variance='"+variance+"' WHERE ProductID='"+pid+"'");

    if(counted.toInt() <= quantity.toInt()){
        if(qryCount.exec())
            QMessageBox::critical(this, tr("Edit"), tr("Updated!"));
        else
            QMessageBox::critical(this, tr("error::"), qryCount.lastError().text());
    } else {
        QMessageBox::critical(this, tr("error::"), tr("Failed! Not enough products existing..."));
    }

    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT * FROM InventoryCount");
    query->exec();
    model->setQuery(*query);
    ui->inventoryCount->setModel(model);

}
