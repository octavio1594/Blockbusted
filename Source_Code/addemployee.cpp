#include "addemployee.h"
#include "ui_addemployee.h"
#include <QWidget>
#include <QDesktopWidget>
#include <iostream>
#include <QFont>

using namespace std;


//creates addEmployee window
addEmployee::addEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEmployee)
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

    ui->frame->move(boxWidth/2-innerFrameX/2,boxHeight/2-innerFrameY/2);//
//    QFont f("Arial", fontSize, QFont::Normal);
    ui->label->resize(innerFrameX*.3,innerFrameY*.2);
    //ui->label->setFont(f);
    ui->label->move(boxHeight/2-(innerFrameX*.3)/2,innerFrameY*.1);
//    ui->firstName->setFont(f); ui->lastName->setFont(f); ui->email->setFont(f); ui->city->setFont(f); ui->address->setFont(f); ui->phoneNumber->setFont(f); ui->state->setFont(f);
//    ui->zipCode->setFont(f);
//    ui->password->setFont(f);
 //   ui->frame_2->resize(innerFrameX*.5,innerFrameY*.5);
 //   ui->frame_2->move(boxHeight/2-(innerFrameX*.3)/2,innerFrameY*.7);
}

//destructor
addEmployee::~addEmployee()
{
    delete ui;
}

//Cancels out of sign in window
void addEmployee::on_cancelButton_clicked()
{
    QWidget::close();
}

//Adds Employee to the Database
void addEmployee::on_addButton_clicked()
{
    QString empID, fName, lName, addr, cit, zCode, sta, pNum, emailA, passWord;
    int manaOrEmp;

    //set variables to values in the given text boxes
    fName = ui->empFname->text();
    lName = ui->empLname->text();
    passWord = ui->empPass->text();
    addr = ui->empAddress->text();
    cit = ui->empCity->text();
    zCode = ui->empZip->text();
    sta = ui->empState->text();
    emailA = ui->empEmail->text();
    pNum = ui->empPhone->text();
    manaOrEmp = ui->empOrMana->isChecked();

    //Error check to make sure all fields are filled in
    if ((fName==NULL)||(lName==NULL)||(addr==NULL)||(cit==NULL)||(zCode==NULL)||
            (sta==NULL)||(pNum==NULL)||(emailA==NULL)||(passWord==NULL))
    {
        ui->errorLabel->setText("Please fill all the requiered fields.");
        ui->errorLabel2->setText(NULL);
    }
    else
    {

        //Insert Employee into database
        QSqlQuery query;
        query.prepare("INSERT INTO Employee (FirstName, LastName, Manager, Password, Address, City, State, ZipCode, EmailAddress, PhoneNumber)"
                      "VALUES (:FirstName, :LastName, :Manager, :Password, :Address, :City, :State, :ZipCode, :EmailAddress, :PhoneNumber)");
        query.bindValue("EmpID", empID);
        query.bindValue(":FirstName", fName);
        query.bindValue(":LastName", lName);
        query.bindValue(":Manager", manaOrEmp);
        query.bindValue(":Password", passWord);
        query.bindValue(":Address", addr);
        query.bindValue(":City", cit);
        query.bindValue(":State", sta);
        query.bindValue(":ZipCode", zCode);
        query.bindValue(":EmailAddress", emailA);
        query.bindValue(":PhoneNumber", pNum);

        if(!query.exec())
        {
            qDebug() << "Add Employee Error: "
                     << query.lastError();
        }

        //Confirmation of success and reset parameters
        ui->errorLabel->setText("Employee was added to the database, click 'add'");
        ui->errorLabel2->setText("to add another employee or cancel to exit.");
        ui->empFname->setText(NULL);
        ui->empLname->setText(NULL);
        ui->empPass->setText(NULL);
        ui->empAddress->setText(NULL);
        ui->empCity->setText(NULL);
        ui->empZip->setText(NULL);
        ui->empState->setText(NULL);
        ui->empPhone->setText(NULL);
        ui->empEmail->setText(NULL);
    }
}
