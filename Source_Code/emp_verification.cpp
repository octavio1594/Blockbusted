#include "emp_verification.h"
#include "ui_emp_verification.h"
#include <QWidget>
#include <QDesktopWidget>
#include <iostream>

using namespace std;

emp_verification::emp_verification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::emp_verification)
{   QRect rec = QApplication::desktop()->screenGeometry();
    const int scrnHeight = rec.height(); // returns the height of the screen.
    const int scrnWidth = rec.width(); // returns the width of the screen.
    double boxWidth = scrnWidth * .25;
    double boxHeight = scrnHeight * .25;
    int innerFrameX = boxWidth*.70;
    int innerFrameY = boxHeight*.70;
    ui->setupUi(this);
    this->resize(boxWidth,boxHeight);
    ui->groupBox->resize(innerFrameX,innerFrameY);
    ui->groupBox->move(boxWidth/2-innerFrameX/2,boxHeight/2-innerFrameY/2);
}

emp_verification::~emp_verification()
{
    qDebug() << "EMPLOYEE DONE";
    delete ui;
}

//Cancels out of sign in window
void emp_verification::on_cancelButton_clicked()
{
    QWidget::close();
}


//Requests verification when prompted
//User provides username (employee ID) and password
//If manager, signs in no problem
//If not a manager, returns saying "Insufficient privileges"
void emp_verification::on_signInButton_clicked()
{
    QString username, password;
    username = ui->lineEdit_Username->text();
    password = ui->lineEdit_Password->text();
    QSqlQuery qry;
    if(qry.exec("SELECT * FROM Employee WHERE EmpID = '"+ username +"' AND Password = '"+ password +"'"))
    {
        int count = 0;
        int employeeFlag = 0;

        while(qry.next())
        {
            count++;
            employeeFlag = qry.value(3).toInt();
            firstName = qry.value(1).toString();
            lastName = qry.value(2).toString();
            empID = qry.value(0).toString();
        }

        if(count == 1 && employeeFlag == 0)
        {
            employeeIsSignedIn = true;
            qDebug() << "Employee signed in";
            this->close();
        }

        else if(count == 1 && employeeFlag == 1)
        {
            assistantManagerIsSignedIn = true;
            qDebug() << "Assistant manager signed in";
            this->close();
        }

        else if(count == 1 && employeeFlag == 2)
        {
            generalManagerIsSignedIn = true;
            qDebug() << "General manager signed in";
            this->close();
        }

        else if(count < 1)
            ui->label->setText("Incorrect username or password");
    }
}
