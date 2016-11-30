#include "edit_inventory.h"
#include "ui_edit_inventory.h"
#include <QMessageBox>
#include <QWidget>
#include <QDesktopWidget>
#include <iostream>
#include <QFont>

//Creates window
edit_inventory::edit_inventory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_inventory)
{
    QRect rec = QApplication::desktop()->screenGeometry();
    const int scrnHeight = rec.height(); // returns the height of the screen.
    const int scrnWidth = rec.width(); // returns the width of the screen.
    double boxWidth = scrnWidth * .50;
    double boxHeight = scrnHeight * .50;
    int innerFrameX = boxWidth*.90;
    int innerFrameY = boxHeight*.80;
    ui->setupUi(this);
    this->resize(boxWidth,boxHeight);
    ui->product_groupBox->resize(innerFrameX,innerFrameY);
}

//Destructor
edit_inventory::~edit_inventory()
{
    delete ui;
}

//Adds Product to the Database
//Also Creates a replica in Inventory Count portion to keep track of how many we have
void edit_inventory::on_add_product_clicked()
{
    //Set temp variables to entered text field values
    QString pid, name, genre, rating, price, quantity;
    pid = ui->pid_input->text();
    name = ui->pname_input->text();
    genre = ui->pgenre_input->text();
    rating = ui->prating_input->text();
    price = ui->pprice_input->text();
    quantity = ui->pquantity_input->text();

    //Insert item into Inventory
    QSqlQuery qry;
    qry.prepare("INSERT INTO Inventory (ProductName, Genre, Rating, Price, Quantity) VALUES (:name, :genre, :rating, :price, :quantity)");
    //qry.bindValue(":pid", pid); //don't need due to autoincriment
    qry.bindValue(":name", name);
    qry.bindValue(":genre", genre);
    qry.bindValue(":rating", rating);
    qry.bindValue(":price", price);
    qry.bindValue(":quantity", quantity);

    if(qry.exec())
    {   QMessageBox::critical(this, tr("Save"), tr("Saved")); }
    else
    {   QMessageBox::critical(this, tr("error::"), qry.lastError().text()); }

    // Query for inserting the new product to InventoryCount
    QSqlQuery qryCount;
    QString variance = "0";
    int count = quantity.toInt() + variance.toInt();
    pid = qry.lastInsertId().toString();
    qryCount.prepare("INSERT INTO InventoryCount (ProductID, ProductName, Quantity, Counted, Variance) VALUES (:pid, :name, :quantity, :count, :variance)");
    qryCount.bindValue(":pid", pid);
    qryCount.bindValue(":name", name);
    qryCount.bindValue(":quantity", quantity);
    qryCount.bindValue(":variance", variance);
    qryCount.bindValue(":count", count);

    if(qryCount.exec())
    {   QMessageBox::critical(this, tr("Save"), tr("InventoryCount Saved")); }
    else
    {   QMessageBox::critical(this, tr("error::"), qryCount.lastError().text()); }
}

//Edits inventory item based on provided Product ID number
//Product ID must exist for edits to be made
void edit_inventory::on_edit_product_clicked()
{
    QString pid, name, genre, rating, price, quantity;
    pid = ui->pid_input->text();
    name = ui->pname_input->text();
    genre = ui->pgenre_input->text();
    rating = ui->prating_input->text();
    price = ui->pprice_input->text();
    quantity = ui->pquantity_input->text();

    QSqlQuery qry;
    qry.prepare("UPDATE Inventory SET ProductID='"+pid+"', ProductName='"+name+"', Genre='"+genre+"', Rating='"+rating+"', Price='"+price+"', Quantity='"+quantity+"' WHERE ProductID='"+pid+"'");

    if(qry.exec())
    {    QMessageBox::critical(this, tr("Edit"), tr("Updated!")); }
    else
    {    QMessageBox::critical(this, tr("error::"), qry.lastError().text()); }

    // Query for editting the same product in InventoryCount
    QSqlQuery qryCount;
    QString variance = "0";
    int count = quantity.toInt() + variance.toInt();
    QString counted = QString::number(count);

    qryCount.prepare("UPDATE InventoryCount SET ProductID='"+pid+"', ProductName='"+name+"', Quantity='"+quantity+"', Counted='"+counted+"' WHERE ProductID='"+pid+"'");

    if(qryCount.exec())
    {   QMessageBox::critical(this, tr("Edit"), tr("InventoryCount Updated")); }
    else
    {   QMessageBox::critical(this, tr("error::"), qryCount.lastError().text()); }
}

//Loads inventory to view
void edit_inventory::on_load_inv_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery();
    qry->prepare("SELECT * FROM Inventory");
    qry->exec();
    model->setQuery(*qry);
    ui->inv_view->setModel(model);
    qDebug() << (model->rowCount());
}

//Loads Text fields with given selected Inventory item's data
//also highlights product id in grey
void edit_inventory::on_inv_view_clicked(const QModelIndex &index)
{
    QString val = ui->inv_view->model()->data(index).toString();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM Inventory WHERE ProductID='"+val+"' OR ProductName='"+val+"' OR Genre='"+val+"' OR Rating='"+val+"' OR Price='"+val+"' OR Quantity='"+val+"'");

    if(qry.exec())
    {
        while(qry.next())
        {
            ui->pid_input->setText(qry.value(0).toString());
            ui->pname_input->setText(qry.value(1).toString());
            ui->pgenre_input->setText(qry.value(2).toString());
            ui->prating_input->setText(qry.value(3).toString());
            ui->pprice_input->setText(qry.value(4).toString());
            ui->pquantity_input->setText(qry.value(5).toString());

            ui->pid_input->setReadOnly(true);
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Base, Qt::lightGray);
            palette->setColor(QPalette::Text, Qt::black);
            ui->pid_input->setPalette(*palette);

        }
    }
    else {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}

//Removes product from inventory list
void edit_inventory::on_remove_product_clicked()
{
    QString pid, name, genre, rating, price;
    pid = ui->pid_input->text();

    QSqlQuery qry;
    qry.prepare("DELETE FROM Inventory WHERE ProductID='"+pid+"'");

    if(qry.exec())
    {   QMessageBox::critical(this, tr("Delete"), tr("Deleted!")); }
    else
    {   QMessageBox::critical(this, tr("error::"), qry.lastError().text()); }

    // Query for deleting the selected product in InventoryCount
    QSqlQuery qryCount;
    qryCount.prepare("DELETE FROM InventoryCount WHERE ProductID='"+pid+"'");

    if(qryCount.exec())
    {   QMessageBox::critical(this, tr("Delete"), tr("InventoryCount Deleted")); }
    else
    {   QMessageBox::critical(this, tr("error::"), qryCount.lastError().text()); }
}

//Creates Inventory Count window
void edit_inventory::on_InventoryCount_clicked()
{
    inventory_count invCount;
    invCount.setModal(true);
    invCount.exec();
}
