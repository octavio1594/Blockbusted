#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>

class DbManager
{
public:
    QSqlDatabase *blockbusted_db;
    void dataClose();
    bool dataOpen();

 //Singleton
     static DbManager* Instance();
    protected:
     DbManager();
    private:
     static DbManager* _instance;
 //End singleton

};

#endif // DBMANAGER_H
