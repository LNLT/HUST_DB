#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QMainWindow>
#include "subwindow.h"
#include "QDateTime"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    SubWindow *subwindow;
    QSqlDatabase db; //数据库对象
    QString username;
    int year;
    int month;
    int grant;
    int person_id;
    int depart_id;

private slots:
    void receiveData(int id,QString name,QString gender,QString tele,int depart,int job);
    void on_add_person_clicked();
    void on_select_person_clicked();
    void on_up_person_clicked();
    void on_dele_person_clicked();
    void on_salary_clicked();
    void on_select_depart_clicked();
    void on_add_depart_clicked();
    void on_up_depart_clicked();
    void on_dele_depart_clicked();
    void on_salary_depart_clicked();
    void on_select_job_clicked();
    void on_add_job_clicked();
    void on_up_job_clicked();
    void on_dele_job_clicked();
    void on_attendance_select_clicked();
    void on_attendance_add_clicked();
    void on_attendance_up_clicked();
    void on_attendance_dele_clicked();
    void on_allowance_select_clicked();
    void on_allowance_add_clicked();
    void on_allowance_up_clicked();
    void on_allowance_dele_clicked();

    void on_salary_2_clicked();

private:
    Ui::MainWindow *ui;
    int up_flag=0;
    int add_flage=0;
    void add_person(int id,QString name,QString gender,QString tele,int depart,int job);
    void up_person(int id,QString name,QString gender,QString tele,int depart,int job);
    int error(bool success,QSqlQuery query);
    int select_depart_id();
    int select_job_id();
    int select_person_id(int id);
    int select_id(int flag_a);
};
#endif // MAINWINDOW_H
