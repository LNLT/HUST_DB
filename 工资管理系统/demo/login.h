#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QMainWindow>
namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_user_login_clicked();

    void on_user_add_clicked();

private:
    Ui::login *ui;
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL"); //数据库对象
    QString username;
    QString dbname;
};

#endif // LOGIN_H
