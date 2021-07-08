#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

class mydb
{
public:
   mydb();
   QSqlDatabase db;
   void connectdb();
   void closedb();
private:

};

#endif // DB_H
