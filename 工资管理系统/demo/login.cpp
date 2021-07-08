#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    dbname="ltt_system";
    QString passwd="123123";
    db.setHostName("127.0.0.1");
    db.setDatabaseName(dbname);
    db.setUserName("root");
    db.setPassword(passwd);
    if( !db.open() ){ //数据库打开失败
            QMessageBox::warning(nullptr,"warning",db.lastError().text(),QMessageBox::Yes, QMessageBox::Yes);
            return;
    }
    else {
        qDebug("connect database success!\n");
    }
    //  db.close();
    //  db.removeDatabase(dbname);
    //  qDebug("close database success!\n");
}

login::~login()
{
    delete ui;
}

void login::on_user_login_clicked()
{
    QSqlQuery query(db);
    QString sql=QString("select * from user where name='%1'").arg(ui->user_name->text());
    query.exec(sql);
    if(query.next()){
        if(!QString::compare(ui->user_pwd->text(),query.value("passwd").toString())){
            MainWindow *w=new MainWindow();
            this->close();
            w->show();
            w->db=this->db;
            w->username=ui->user_name->text();
            w->grant=query.value("grant_id").toInt();
            //查询该用户id
            QSqlQuery query_person(db);
            QString sql_person=QString("select * from person where name='%1'").arg(ui->user_name->text());
            query_person.exec(sql_person);
            if(query_person.next()){
                w->person_id=query_person.value("id").toInt();
            }
        }
        else {
            QMessageBox::warning(nullptr,"warning","密码不正确！",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    else {
        QMessageBox::warning(nullptr,"warning","没有该用户",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
}


void login::on_user_add_clicked()
{
    QSqlQuery query_person(db);
    QString sql_person=QString("select * from person where name='%1'").arg(ui->user_name->text());
    query_person.exec(sql_person);
    int grant=2;
    //如果是超级管理员
    if(!QString::compare(ui->user_name->text(),"root")){
        grant=0;
    }
    //如果公司有该员工
    if(query_person.next()){
        //如果是部门经理
        if(query_person.value("job_id").toInt()==0){
            grant=1;
        }
        //查询user表是否有该用户
        QSqlQuery query_user(db);
        QString sql_user=QString("select id from user where name='%1'").arg(ui->user_name->text());
        query_user.exec(sql_user);
        if(query_user.next()){
            QMessageBox::warning(nullptr,"warning","已有该用户！",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
        //查询user表的最大id
        QSqlQuery query_max(db);
        QString max_sql="SELECT max(id) as max FROM user";
        query_max.exec(max_sql);
        int max_id=0;
        if(query_max.next()){
            max_id=query_max.value("max").toInt()+1;
        }
        //添加user用户
        QSqlQuery query(db);
        QString sql=QString("insert into user values(%1,'%2',%3,%4)").arg(max_id).arg(ui->user_name->text()).arg(ui->user_pwd->text()).arg(grant);
        bool success=query.exec(sql);
        if(success){
            QMessageBox::warning(nullptr,"warning","注册成功！",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    else {
        QMessageBox::warning(nullptr,"warning","没有该员工！",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
}
