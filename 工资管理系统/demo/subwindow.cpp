#include "subwindow.h"
#include "ui_subwindow.h"
#include "QDebug"
SubWindow::SubWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SubWindow)
{
    ui->setupUi(this);
    connect(ui->add_person,SIGNAL(clicked()),this, SLOT(on_add_person_clicked()));
}

SubWindow::~SubWindow()
{
    delete ui;
}

void SubWindow::on_add_person_clicked()
{
    QString name,gender,tele;
    int id,depart,job;
    name=ui->name->text().isEmpty()?nullptr:ui->name->text();
    gender=ui->gender->text().isEmpty()?nullptr:ui->gender->text();
    tele=ui->tele->text().isEmpty()?nullptr:ui->tele->text();
    id=ui->id->text().isEmpty()?-1:ui->id->text().toInt();
    depart=ui->depart->text().isEmpty()?-1:ui->depart->text().toInt();
    job=ui->level->text().isEmpty()?-1:ui->level->text().toInt();
    qDebug()<<id<<name<<gender<<tele<<depart<<job;
    emit SendData_sub(id,name,gender,tele,depart,job);
    this->close();
}
