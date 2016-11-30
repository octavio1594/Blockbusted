#include "dbmanager.h"
//Absolute path to database
//Needs to be changed for each user
QString databasepath = "C:/Users/Raymango/Desktop/FinalBB/Blockbusted-Final_Product/blockbusted_db.db";

//Constructor
//Sets up the database connection and opens it
DbManager::DbManager(){
    blockbusted_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    blockbusted_db->setDatabaseName(databasepath);
    if(blockbusted_db->open())
        qDebug() << "Database is open...";
    else
        qDebug() << "Database did not open...";
}

//Closes database connection
void DbManager::dataClose(){
    //qDebug() << blockbusted_db.connectionName();
    blockbusted_db->close();
    QString connection = blockbusted_db->connectionName();
    delete blockbusted_db;
    QSqlDatabase::removeDatabase(connection);
    qDebug() << "Database connection removed";
}

//begin singleton
DbManager* DbManager::_instance = 0;

DbManager* DbManager::Instance()
{
    if ( _instance == 0 )
        _instance = new DbManager();
 return _instance;
}

//end singleton
