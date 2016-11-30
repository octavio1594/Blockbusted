#include "addcustomer.h"
#include "ui_addcustomer.h"
#include <QWidget>
#include <QDesktopWidget>
#include <iostream>
#include <QFont>

using namespace std;


//creates window
addCustomer::addCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCustomer)
{
    QRect rec = QApplication::desktop()->screenGeometry();
    const int scrnHeight = rec.height(); // returns the height of the screen.
    const int scrnWidth = rec.width(); // returns the width of the screen.
    double boxWidth = scrnWidth * .35;
    double boxHeight = scrnHeight * .65;
    double fontSize = (boxWidth) * .02;
    int innerFrameX = boxWidth*.6;
    int innerFrameY = boxHeight*.6;
    ui->setupUi(this);
    this->setFixedSize(boxWidth,boxHeight);
    ui->frame->resize(boxWidth*.6,boxHeight*.6);
    ui->frame->move(boxWidth/2-innerFrameX/2,boxHeight/2-innerFrameY/2);
 //   QFont f("Arial", fontSize, QFont::Normal);
    ui->label->resize(innerFrameX*.3,innerFrameY*.2);// ui->label->setFont(f);
    ui->label->move(boxHeight/2-(innerFrameX*.3)/2,innerFrameY*.1);
//    ui->firstName->setFont(f); ui->lastName->setFont(f); ui->email->setFont(f); ui->city->setFont(f); ui->address->setFont(f); ui->phoneNumber->setFont(f); ui->state->setFont(f);
//    ui->zipCode->setFont(f);
//    ui->frame_2->resize(innerFrameX*.5,innerFrameY*.5);
//    ui->frame_2->move(boxHeight/2-(innerFrameX*.3)/2,innerFrameY*.7);


}

//destructor
addCustomer::~addCustomer()
{
    delete ui;
}

//Cancels out of sign in window
void addCustomer::on_cancelButton_clicked()
{
    QWidget::close();
}

//Add customer to the Database
void addCustomer::on_addButton_clicked()
{
    QString fName, lName, addr, cit, zCode, sta, pNum, emailA;

    //set variables to values in the given text boxes
    fName = ui->cusfirstName->text();
    lName = ui->cuslastName->text();
    addr = ui->cusaddress->text();
    cit = ui->cuscity->text();
    zCode = ui->cuszipCode->text();
    sta = ui->cusstate->text();
    pNum = ui->cusphoneNumber->text();
    emailA = ui->cusemail->text();

    //error check to make sure all boxes are filled in
    if ((fName==NULL)||(lName==NULL)||(addr==NULL)||(cit==NULL)||(zCode==NULL)||(sta==NULL)||(pNum==NULL)||(emailA==NULL))
    {
        ui->errorLabel->setText("Please fill all the requiered fields.");
        ui->errorLabel2->setText(NULL);
    }
    else
    {
        //insert given information into the database
        QSqlQuery query;
        query.prepare("INSERT INTO Customer (FirstName, LastName, Address, City, State, ZipCode, PhoneNumber, EmailAddress)"
                      "VALUES (:FirstName, :LastName, :Address, :City, :State, :ZipCode, :PhoneNumber, :EmailAddress)");
        query.bindValue(":FirstName", fName);
        query.bindValue(":LastName", lName);
        query.bindValue(":Address", addr);
        query.bindValue(":City", cit);
        query.bindValue(":State", sta);
        query.bindValue(":ZipCode", zCode);
        query.bindValue(":PhoneNumber", pNum);
        query.bindValue(":EmailAddress", emailA);

        //error message if something went wrong
        if(!query.exec())
        {
            qDebug() << "Add Person Error: "
                     << query.lastError();
        }
        
        //parameter reset and confirmation of success
        ui->errorLabel->setText("Customer was added to the database, click 'add'");
        ui->errorLabel2->setText("to add another customer or cancel to exit.");
        ui->cusfirstName->setText(NULL);
        ui->cuslastName->setText(NULL);
        ui->cusaddress->setText(NULL);
        ui->cuscity->setText(NULL);
        ui->cuszipCode->setText(NULL);
        ui->cusstate->setText(NULL);
        ui->cusphoneNumber->setText(NULL);
        ui->cusemail->setText(NULL);
    }
}
