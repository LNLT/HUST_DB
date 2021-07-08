#include "mydb.h"
#define dbname "demo"

mydb::mydb()
{
    qDebug()<<QSqlDatabase::drivers();
    db = QSqlDatabase::addDatabase("QMYSQL"); //数据库对象
    db.setHostName("127.0.0.1");
    db.setDatabaseName("demo");
    db.setUserName("root");
    db.setPassword("123123");
}
void mydb::connectdb(){
    if( !db.open() ){ //数据库打开失败
            QMessageBox::warning(NULL,"错误",db.lastError().text(),QMessageBox::Yes, QMessageBox::Yes);
            return;
    }
}
void mydb::closedb(){
    db.close();
    db.removeDatabase(dbname);
}
