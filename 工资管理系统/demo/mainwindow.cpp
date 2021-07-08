#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
//    qDebug()<<QSqlDatabase::drivers();
//    db.close();
//    db.removeDatabase(dbname);
    ui->setupUi(this);
    subwindow=new SubWindow();
    connect(subwindow,SIGNAL(SendData_sub(int,QString,QString,QString,int,int)),this, SLOT(receiveData(int,QString,QString,QString,int,int)));
    QDateTime time=QDateTime::currentDateTime();
    QStringList list=time.date().toString("yyyy-MM-dd").split("-");
    QString year_str=list[0];
    QString month_str=list[1];
    ui->time_year->setText(year_str);
    ui->time_month->setText(month_str);
    year=year_str.toInt();
    month=month_str.toInt();
    //qDebug()<<year<<month;
    QSqlQuery query(db);
    QString sql=QString("select depart_id from person where id=%1").arg(this->person_id);
    query.exec(sql);
    query.next();
    depart_id=query.value("depart_id").toInt();
}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::error(bool success,QSqlQuery query){//收集报错
    if(!success){
        QMessageBox::warning(nullptr,"warning",query.lastError().text(),QMessageBox::Yes, QMessageBox::Yes);
        return 0;
    }
    return 1;
}

void MainWindow::receiveData(int id,QString name,QString gender,QString tele,int depart,int job){
    if(add_flage==1){
        add_person(id,name,gender,tele, depart, job);
        add_flage=0;
    }
    else if (up_flag==1) {
        up_person(id,name,gender,tele, depart, job);
        up_flag=0;
    }
}

void MainWindow::on_add_person_clicked()//添加人员，grant<2
{
    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    subwindow->show();
    add_flage=1;
}

void MainWindow::add_person(int id,QString name,QString gender,QString tele,int depart,int job)//添加人员
{
    if (grant==1) {
        if(depart_id!=depart){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    if(select_person_id(id)==1){
        QMessageBox::warning(nullptr,"warning","已有该员工！",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QSqlQuery query(db);
    QString sql=QString("insert into person values (%1,'%2','%3','%4',%5,%6,1)").arg(id).arg(name).arg(gender).arg(tele).arg(depart).arg(job);
    bool success=query.exec(sql);
    if(error(success,query)){
        on_select_person_clicked();
    }
}

void MainWindow::on_up_person_clicked()//修改员工信息,grant<2
{
    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    subwindow->show();
    up_flag=1;
}

void MainWindow::up_person(int id,QString name,QString gender,QString tele,int depart,int job)//修改员工信息,先显示再修改,grant<2
{
    if (grant==1) {
        QSqlQuery query(db);
        QString sql=QString("select depart_id from person where id=%1").arg(id);
        query.exec(sql);
        query.next();
        if(query.value("depart_id").toInt()!=depart_id){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    if(select_person_id(id)==0){
        QMessageBox::warning(nullptr,"warning","该员工不存在！",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QSqlQuery query(db);
    bool success;
    if(name!=nullptr){
        QString sql=QString("update person set name='%2' where id=%1").arg(id).arg(name);
        success=query.exec(sql);
        error(success,query);
    }
    if(gender!=nullptr){
        QString sql=QString("update person set gender='%2' where id=%1 and status=1").arg(id).arg(gender);
        success=query.exec(sql);
        error(success,query);
    }
    if(tele!=nullptr){
        QString sql=QString("update person set telephone='%2' where id=%1 and status=1").arg(id).arg(tele);
        success=query.exec(sql);
        qDebug()<<sql<<success;
        error(success,query);
    }
    if(depart!=-1){
        QString sql=QString("update person set depart_id=%2 where id=%1 and status=1").arg(id).arg(depart);
        success=query.exec(sql);
        error(success,query);
    }
    if(job!=-1){
        QString sql=QString("update person set job_id=%2 where id=%1 and status=1").arg(id).arg(job);
        success=query.exec(sql);
        error(success,query);
    }
    on_select_person_clicked();
}

void MainWindow::on_select_person_clicked()//查询所有员工
{
    QSqlQuery query(db);
    QString sql="select person.id,person.name,gender,telephone,department.name,job.name,status from person,department,job where person.depart_id=department.id and person.job_id=job.id order by person.id";
    //qDebug()<<grant<<this->username;
    if(grant==2){//只能查询自己的信息
        sql=QString("select person.id,person.name,gender,telephone,department.name,job.name,status from person,department,job where person.depart_id=department.id and person.job_id=job.id and person.name='%1' order by person.id ").arg(this->username);
    }
    bool success=query.exec(sql);
    error(success,query);
    ui->listWidget->clear();
    ui->listWidget->addItem("id\tname\tgender\ttelephone\tdepart\tjob\tstatus");
    while(query.next()){
        if(query.value("person.id").toString()==nullptr){
            QMessageBox::warning(nullptr,"warning","没有该员工！",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
        ui->listWidget->addItem(query.value("person.id").toString() +'\t'+query.value("person.name").toString()+'\t'+query.value("gender").toString()
                                +'\t'+query.value("telephone").toString()+'\t'+query.value("department.name").toString()+'\t'+query.value("job.name").toString()+'\t'+query.value("status").toString());
    }
}

void MainWindow::on_dele_person_clicked()//删除员工，修改员工status，grant<2
{
    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else if (grant==1) {
        QSqlQuery query(db);
        QString sql=QString("select depart_id from person where id=%1").arg(ui->dele_id->text().toInt());
        query.exec(sql);
        query.next();
        if(query.value("depart_id").toInt()!=depart_id){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    if(select_person_id(ui->dele_id->text().toInt())==0){
        QMessageBox::warning(nullptr,"warning","该员工不存在！",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if(db.transaction()){//启动事务操作
        QSqlQuery query(db);
        QString sql=QString("update person set status=0 where id=%1").arg(ui->dele_id->text().toInt());
        QString dele_user=QString("delete from user where name=(select name from person where id=%1)").arg(ui->dele_id->text().toInt());
        query.exec(sql);
        query.exec(dele_user);
        if(!db.commit()){//执行事务
            qDebug() << db.lastError();
            if(!db.rollback()){//回滚
                qDebug()<<db.lastError();
            }
        }
        on_select_person_clicked();//调用查询显示修改结果
    }
    ui->dele_id->clear();

}

void MainWindow::on_salary_clicked()//查询工资
{
    if(grant==0){
        //查询salary表中最大id号
        QSqlQuery query_max(db);
        QString max_sql="SELECT max(id) as max FROM salary";
        query_max.exec(max_sql);
        int max_id=0;
        if(query_max.next()){
            max_id=query_max.value("max").toInt()+1;
        }
        QSqlQuery query(db);
        QString sql="SELECT attendance.person_id as id,attendance.year as year,attendance.month as month,IFNULL((IFNULL(sum_overtime,0)+(25-absence_time))*based_salary,0) as salary_per ";
        QString sql2="FROM attendance left outer join (SELECT person_id,year,month,sum(IFNULL(overtime*overtime_type,0)) as sum_overtime FROM allowance GROUP BY person_id,year,month) as sum_all on(attendance.person_id=sum_all.person_id AND attendance.year=sum_all.year AND attendance.month=sum_all.month),(SELECT person.id as id,based_salary FROM job,person WHERE job.id=person.job_id) as salary2 WHERE salary2.id=attendance.person_id";
        bool success=query.exec(sql+sql2);
        error(success,query);
        while(query.next()){
            //查询工资
            QSqlQuery query_sele_salary(db);
            QString sele_salary=QString("select count(*) as num from salary where person_id=%1 and year=%2 and month=%3").arg(query.value("id").toInt()).arg(query.value("year").toInt()).arg(query.value("month").toInt());
            success=query_sele_salary.exec(sele_salary);
            error(success,query_sele_salary);
            if(query_sele_salary.next()){
                //qDebug()<<query_sele_salary.value("num").toInt()<<query.value("year").toInt()<<year<<query.value("month").toInt()<<month;
                if(query_sele_salary.value("num").toInt()!=0&&query.value("year").toInt()<=year&&query.value("month").toInt()<month)
                    //如果已经有记录且要写入的记录不是当前月，则不再写入
                    continue;
                //是当前年月，则覆盖记录
                if(query.value("year").toInt()==year&&query.value("month").toInt()==month){
                    QSqlQuery query_salary(db);
                    QString dele_salary=QString("delete from salary where person_id=%1 and year=%2 and month=%3").arg(query.value("id").toInt()).arg(query.value("year").toInt()).arg(query.value("month").toInt());
                    query_max.exec(max_sql);
                    if(query_max.next()){
                        max_id=query_max.value("max").toInt()+1;
                    }
                    success=query_salary.exec(dele_salary);
                    error(success,query_salary);
                }
            }
           //将数据写入salary表
            QSqlQuery query_salary(db);
            QString in_salary=QString("insert into salary values (%1,%2,%3,%4,%5)").arg(max_id).arg(query.value("id").toInt()).arg(query.value("year").toInt()).arg(query.value("month").toInt()).arg(query.value("salary_per").toInt());
            success=query_salary.exec(in_salary);
            error(success,query_salary);
            max_id++;
        }

    }


    //根据权限，查询工资表
    QSqlQuery query_salary(db);
    QString sql_salary;
    ui->listWidget->clear();
    ui->listWidget->addItem("name\tyear\tmonth\tsalary");
    if(grant==2){
        sql_salary=QString("select * from salary,person where person.id=salary.person_id and person.name='%1'").arg(this->username);
    }
    else if (grant==1 && ui->dele_id->text().toInt()==this->person_id) {
        sql_salary=QString("select * from salary,person where person.id=salary.person_id and person.name='%1'").arg(this->username);
    }
    else if (grant==0 && ui->dele_id->text().toInt()!=0) {
        sql_salary=QString("select * from salary,person where person.id=salary.person_id and person.id=%1").arg(ui->dele_id->text().toInt());
    }
    else if(grant==0){
        sql_salary="select * from salary,person where person.id=salary.person_id";
    }
    else{
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //qDebug()<<grant<<this->person_id<<sql_salary<<this->username;
    query_salary.exec(sql_salary);
    while(query_salary.next()){
        ui->listWidget->addItem(query_salary.value("name").toString() +'\t'+query_salary.value("year").toString()+'\t'+query_salary.value("month").toString()
                                +'\t'+query_salary.value("salary").toString());
    }
    ui->dele_id->clear();
}

void MainWindow::on_salary_2_clicked()//计算年终奖
{
    if(ui->dele_id->text()!=nullptr){
        //该员工是否存在
        if(select_person_id(ui->dele_id->text().toInt())==0){
            QMessageBox::warning(nullptr,"warning","该员工不存在！",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    QSqlQuery query_year(db);
    QString sql_year;
    //权限
    if(grant==2){
       sql_year=QString("call year_salary(%1)").arg(this->person_id);
    }
    else if (grant==1){
        QSqlQuery query(db);
        QString sql=QString("select depart_id from person where id=%1").arg(ui->dele_id->text().toInt());
        query.exec(sql);
        query.next();
        if(query.value("depart_id").toInt()!=depart_id){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
        sql_year=QString("call year_salary(%1)").arg(ui->dele_id->text().toInt());
    }
    else if (grant==0 && ui->dele_id->text()!=nullptr) {
        sql_year=QString("call year_salary(%1)").arg(ui->dele_id->text().toInt());
    }
    else{
        sql_year=QString("call year_salary(%1)").arg(0);
    }
    qDebug()<<grant<<ui->dele_id->text().toInt()<<sql_year;
    bool success=query_year.exec(sql_year);//调用存储过程
    error(success,query_year);
    ui->listWidget->clear();
    ui->listWidget->addItem("id\tyear\t年终奖");
    while(query_year.next()){
        ui->listWidget->addItem(query_year.value("person_id").toString() +'\t'+query_year.value("year").toString()+'\t'
                                +query_year.value("salary").toString());
    }
    ui->dele_id->clear();
}

int MainWindow::select_person_id(int id){//查询员工id。1：存在；0：不存在
    QSqlQuery query(db);
    QString sele=QString("select id from person where id=%1").arg(id);
    query.exec(sele);
    if(query.next()){
        return 1;
    }
    else{
        return 0;
    }
}

void MainWindow::on_select_depart_clicked()//查询部门
{
    QSqlQuery query(db);
    QString sql="select * from department";
    query.exec(sql);
    ui->listWidget_depart->clear();
    ui->listWidget_depart->addItem("id\tname\tnumber");
    while(query.next()){
        QSqlQuery query_count(db);
        QString sql_count=QString("select count(*) as num from person where depart_id=%1").arg(query.value("id").toInt());
        query_count.exec(sql_count);
        query_count.next();
        ui->listWidget_depart->addItem(query.value("id").toString()+"\t"+query.value("name").toString()+"\t"+query_count.value("num").toString());
    }
}

void MainWindow::on_add_depart_clicked()//添加部门,grant=0
{
    if(grant!=0){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //查询部门表是否有该id
    if(select_depart_id()==1){
        QMessageBox::warning(nullptr,"warning","id 已存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QSqlQuery query(db);
    if(ui->depart_id->text()==nullptr||ui->depart_name->text()==nullptr){
        QMessageBox::warning(nullptr,"warning","please input id or name!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //添加部门id，name
    QString sql=QString("insert into department values(%1,'%2')").arg(ui->depart_id->text().toInt()).arg(ui->depart_name->text());
    bool success=query.exec(sql);
    if(error(success,query)){
        on_select_depart_clicked();
    }
    ui->depart_id->clear();
    ui->depart_name->clear();
}

void MainWindow::on_up_depart_clicked()//修改部门,grant=0
{
    if(grant!=0){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //查询部门表是否有该id
    if(select_depart_id()==0){
        QMessageBox::warning(nullptr,"warning","id 不存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //修改部门name
    QSqlQuery query(db);
    if(ui->depart_name->text()!=nullptr){
        QString sql=QString("update department set name='%2' where id=%1").arg(ui->depart_id->text().toInt()).arg(ui->depart_name->text());
        bool success=query.exec(sql);
        if(error(success,query)){
            on_select_depart_clicked();//成功后显示结果
        }
    }
    ui->depart_id->clear();
    ui->depart_name->clear();
}

void MainWindow::on_dele_depart_clicked()//删除部门,grant=0
{
    if(grant!=0){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //查询部门表是否有该id
    if(select_depart_id()==0){
        QMessageBox::warning(nullptr,"warning","id 不存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //删除id
    QSqlQuery query(db);
    QString sql=QString("delete from department where id=%1").arg(ui->depart_id->text().toInt());
    bool success=query.exec(sql);
    if(error(success,query)){
        on_select_depart_clicked();
    }
    ui->depart_id->clear();
}

void MainWindow::on_salary_depart_clicked()//查询部门工资,grant<2
{
    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else if (grant==1) {
        if(this->depart_id!=ui->depart_id->text().toInt()){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    //查询部门表是否有该id
    if(select_depart_id()==0){
        QMessageBox::warning(nullptr,"warning","id 不存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //查询id工资
    QSqlQuery query(db);
    QString sql=QString("select person.name,year,month,salary,department.name from salary,person,department where person.depart_id=%1 and person.id=salary.person_id and person.depart_id=department.id").arg(ui->depart_id->text().toInt());
    bool success=query.exec(sql);
    if(!error(success,query)){
        return;
    }
    ui->listWidget_depart->clear();
    ui->listWidget_depart->addItem("name\tyear\tmonth\tsalary\tdepart_name");
    while(query.next()){
        ui->listWidget_depart->addItem(query.value("person.name").toString()+"\t"+query.value("year").toString()
                                       +"\t"+query.value("month").toString()+"\t"+query.value("salary").toString()+"\t"+query.value("department.name").toString());
    }
}

int MainWindow::select_depart_id(){//查询部门表是否有该id,1有,0无
    QSqlQuery query(db);
    if(ui->depart_id->text()==nullptr){
        QMessageBox::warning(nullptr,"warning","please input id!",QMessageBox::Yes, QMessageBox::Yes);
        return -1;
    }

    QString sql_select=QString("select id from department where id=%1").arg(ui->depart_id->text().toInt());
    bool success=query.exec(sql_select);
    error(success,query);
    if(query.next()){
        return 1;
    }
    else{
        return 0;
    }
}

void MainWindow::on_select_job_clicked()//查询工种
{
    QSqlQuery query(db);
    QString sql=QString("select * from job");
    bool success=query.exec(sql);
    error(success,query);
    ui->listWidget_job->clear();
    ui->listWidget_job->addItem("id\tname\tlevel\tbased_salary");
    while(query.next()){
        ui->listWidget_job->addItem(query.value("id").toString()+"\t"+query.value("name").toString()+"\t"+query.value("level").toString()
                                    +"\t"+query.value("based_salary").toString());
    }
}

void MainWindow::on_add_job_clicked()//添加工种,grant=0
{
    if(grant!=0){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //查询是否有该工种
    if(select_job_id()==1){
        QMessageBox::warning(nullptr,"warning","id 已存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //添加工种
    QSqlQuery query(db);
    QString sql=QString("insert into job values (%1,'%2',%3,%4)").arg(ui->job_id->text().toInt()).arg(ui->job_name->text()).arg(ui->job_level->text().toInt()).arg(ui->job_salary->text().toInt());
    bool success=query.exec(sql);
    if(error(success,query)){
        on_select_job_clicked();
    }
    ui->job_id->clear();
    ui->job_name->clear();
    ui->job_level->clear();
    ui->job_salary->clear();
}

void MainWindow::on_up_job_clicked()//修改工种信息,grant=0
{
    if(grant!=0){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //查询是否有该工种
    if(select_job_id()==0){
        QMessageBox::warning(nullptr,"warning","id 不存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //修改工种信息
    QSqlQuery query(db);
    bool success;
    if(ui->job_name->text()!=nullptr){
        QString sql=QString("update job set name='%2' where id=%1").arg(ui->job_id->text().toInt()).arg(ui->job_name->text());
        success=query.exec(sql);
        error(success,query);
    }
    if(ui->job_level->text()!=nullptr){
        QString sql=QString("update job set level=%2 where id=%1").arg(ui->job_id->text().toInt()).arg(ui->job_level->text().toInt());
        success=query.exec(sql);
        error(success,query);
    }
    if(ui->job_salary->text()!=nullptr){
        QString sql=QString("update job set based_salary=%2 where id=%1").arg(ui->job_id->text().toInt()).arg(ui->job_salary->text().toInt());
        success=query.exec(sql);
        error(success,query);
    }
    on_select_job_clicked();
    ui->job_id->clear();
    ui->job_name->clear();
    ui->job_level->clear();
    ui->job_salary->clear();
}

void MainWindow::on_dele_job_clicked()//删除工种,grant=0
{
    if(grant!=0){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //查询是否有该工种
    if(select_job_id()==0){
        QMessageBox::warning(nullptr,"warning","id 不存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //删除工种
    QSqlQuery query(db);
    QString sql=QString("delete from job where id=%1").arg(ui->job_id->text().toInt());
    bool success=query.exec(sql);
    if(error(success,query)){
        on_select_job_clicked();
    }
    ui->job_id->clear();
}

int MainWindow::select_job_id(){//查询工种表是否有该id,1有,0无
    QSqlQuery query(db);
    if(ui->job_id->text()==nullptr){
        QMessageBox::warning(nullptr,"warning","please input id!",QMessageBox::Yes, QMessageBox::Yes);
        return -1;
    }

    QString sql_select=QString("select id from job where id=%1").arg(ui->job_id->text().toInt());
    bool success=query.exec(sql_select);
    error(success,query);
    if(query.next()){
        return 1;
    }
    else{
        return 0;
    }
}

void MainWindow::on_attendance_select_clicked()//查询考勤记录,可查个人的，也可查所有的
{
    QSqlQuery query(db);
    QString sql;
    if(ui->person_id->text()==nullptr){//未输入person_id
        sql="select * from attendance,person where person.id=attendance.person_id";
    }
    else {//输入person_id
        sql=QString("select * from attendance,person where person.id=attendance.person_id and person_id=%1").arg(ui->person_id->text().toInt());
    }
    if(grant==2){
        sql=QString("select * from attendance,person where person.id=attendance.person_id and person_id=%1").arg(this->person_id);
    }
    bool success=query.exec(sql);
    error(success,query);
    ui->listWidget_allatt->clear();
    ui->listWidget_allatt->addItem("id\tname\t\tyear\tmonth\t缺勤天数");
    while(query.next()){
        ui->listWidget_allatt->addItem(query.value("attendance.id").toString()+"\t"+query.value("name").toString()+"\t\t"+query.value("year").toString()
                                    +"\t"+query.value("month").toString()+"\t"+query.value("absence_time").toString());
    }

}

void MainWindow::on_attendance_add_clicked()//添加考勤记录,grant<2
{
    if(select_id(0)<0){
            return;
    }
    else if(select_id(0)==1){
        QMessageBox::warning(nullptr,"warning","该记录已存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else if (grant==1) {
        QSqlQuery query(db);
        QString sql=QString("select depart_id from person where id=%1").arg(ui->person_id->text().toInt());
        query.exec(sql);
        query.next();
        if(query.value("depart_id").toInt()!=depart_id){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    //查询最大id号
    QSqlQuery query_max(db);
    QString max_sql="SELECT max(id) as max FROM attendance";
    query_max.exec(max_sql);
    int max_id=0;
    if(query_max.next()){
        max_id=query_max.value("max").toInt()+1;
    }
    //添加
    QSqlQuery query(db);
    QString sql=QString("insert into attendance values(%1,%2,%3,%4,%5)").arg(max_id).arg(ui->person_id->text().toInt()).arg(ui->year->text().toInt()).arg(ui->month->text().toInt()).arg(ui->attendance_day->text().toInt());
    bool success=query.exec(sql);
    if(error(success,query)){
        on_attendance_select_clicked();
    }
    ui->person_id->clear();
    ui->year->clear();
    ui->month->clear();
}

void MainWindow::on_attendance_up_clicked()//修改考勤记录,grant<2
{
    if(select_id(0)<0){
            return;
    }
    else if(select_id(0)==0){
        QMessageBox::warning(nullptr,"warning","该记录不存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else if (grant==1) {
        QSqlQuery query(db);
        QString sql=QString("select depart_id from person where id=%1").arg(ui->person_id->text().toInt());
        query.exec(sql);
        query.next();
        if(query.value("depart_id").toInt()!=depart_id){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }

    //修改
    QSqlQuery query(db);
    bool success;
    if(ui->attendance_day->text()!=nullptr){
        QString sql=QString("update attendance set absence_time=%4 where person_id=%1 and year=%2 and month=%3").arg(ui->person_id->text().toInt()).arg(ui->year->text().toInt()).arg(ui->month->text().toInt()).arg(ui->attendance_day->text().toInt());
        success=query.exec(sql);
        error(success,query);
    }
    on_attendance_select_clicked();
    ui->person_id->clear();
    ui->year->clear();
    ui->month->clear();
    ui->attendance_day->clear();
}

void MainWindow::on_attendance_dele_clicked()//删除考勤记录,grant<2
{
    if(select_id(0)<0){
            return;
    }
    else if(select_id(0)==0){
        QMessageBox::warning(nullptr,"warning","该记录不存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else if (grant==1) {
        QSqlQuery query(db);
        QString sql=QString("select depart_id from person where id=%1").arg(ui->person_id->text().toInt());
        query.exec(sql);
        query.next();
        if(query.value("depart_id").toInt()!=depart_id){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }

    //删除
    QSqlQuery query(db);
    QString sql=QString("delete from attendance where person_id=%1 and year=%2 and month=%3").arg(ui->person_id->text().toInt()).arg(ui->year->text().toInt()).arg(ui->month->text().toInt());
    bool success=query.exec(sql);
    if(error(success,query)){
        on_attendance_select_clicked();
    }
    ui->person_id->clear();
    ui->year->clear();
    ui->month->clear();
}

int MainWindow::select_id(int flag_a){//falg_a=0:查询考勤表是否有该记录,1有,0无。falg_a=1:查询津贴表是否有该记录,1有,0无。
    QSqlQuery query(db);
    if(ui->person_id->text()==nullptr){
        QMessageBox::warning(nullptr,"warning","please input person_id!",QMessageBox::Yes, QMessageBox::Yes);
        return -1;
    }
    if(ui->year->text()==nullptr){
        QMessageBox::warning(nullptr,"warning","please input year!",QMessageBox::Yes, QMessageBox::Yes);
        return -2;
    }
    if(ui->month->text()==nullptr){
        QMessageBox::warning(nullptr,"warning","please input month!",QMessageBox::Yes, QMessageBox::Yes);
        return -3;
    }
    QString sql_select;
    if(flag_a==0){
        sql_select=QString("select id from attendance where person_id=%1 and year=%2 and month=%3").arg(ui->person_id->text().toInt()).arg(ui->year->text().toInt()).arg(ui->month->text().toInt());
    }
    else {
        sql_select=QString("select id from allowance where person_id=%1 and year=%2 and month=%3").arg(ui->person_id->text().toInt()).arg(ui->year->text().toInt()).arg(ui->month->text().toInt());
    }
    bool success=query.exec(sql_select);
    error(success,query);
    if(query.next()){
        return 1;
    }
    else{
        return 0;
    }
}

void MainWindow::on_allowance_select_clicked()//查询加班记录
{
    QSqlQuery query(db);
    QString sql;
    if(ui->person_id->text()==nullptr){//未输入person_id
        sql="select * from allowance,person where person.id=allowance.person_id";
    }
    else {//输入person_id
        sql=QString("select * from allowance,person where person.id=allowance.person_id and person_id=%1").arg(ui->person_id->text().toInt());
    }
    if(grant==2){
        sql=QString("select * from allowance,person where person.id=allowance.person_id and person_id=%1").arg(this->person_id);
    }
    bool success=query.exec(sql);
    error(success,query);
    ui->listWidget_allatt->clear();
    ui->listWidget_allatt->addItem("id\tname\t\tyear\tmonth\t加班天数\t加班类型");
    while(query.next()){
        ui->listWidget_allatt->addItem(query.value("allowance.id").toString()+"\t"+query.value("name").toString()+"\t\t"+query.value("year").toString()
                                    +"\t"+query.value("month").toString()+"\t"+query.value("overtime").toString()+"\t"+query.value("overtime_type").toString());
    }
}

void MainWindow::on_allowance_add_clicked()//添加加班记录,grant<2
{
    if(select_id(1)<0){
        return;
    }
    else if(select_id(1)==1){
        QMessageBox::warning(nullptr,"warning","该记录已存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //权限
    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else if (grant==1) {
        QSqlQuery query(db);
        QString sql=QString("select depart_id from person where id=%1").arg(ui->person_id->text().toInt());
        query.exec(sql);
        query.next();
        if(query.value("depart_id").toInt()!=depart_id){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    //查询最大id号
    QSqlQuery query_max(db);
    QString max_sql="SELECT max(id) as max FROM allowance";
    query_max.exec(max_sql);
    int max_id=0;
    if(query_max.next()){
        max_id=query_max.value("max").toInt()+1;
    }
    //添加
    QSqlQuery query(db);
    QString sql=QString("insert into allowance values(%1,%2,%3,%4,%5,%6)").arg(max_id).arg(ui->person_id->text().toInt()).arg(ui->year->text().toInt()).arg(ui->month->text().toInt()).arg(ui->allowance_day->text().toInt()).arg(ui->allowance_type->text().toInt());
    bool success=query.exec(sql);
    if(error(success,query)){
        on_allowance_select_clicked();
    }
    ui->person_id->clear();
    ui->year->clear();
    ui->month->clear();
}

void MainWindow::on_allowance_up_clicked()//修改加班记录,grant<2
{
    if(select_id(1)<0){
            return;
    }
    else if(select_id(1)==0){
        QMessageBox::warning(nullptr,"warning","该记录不存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //权限
    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else if (grant==1) {
        QSqlQuery query(db);
        QString sql=QString("select depart_id from person where id=%1").arg(ui->person_id->text().toInt());
        query.exec(sql);
        query.next();
        if(query.value("depart_id").toInt()!=depart_id){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    //修改
    QSqlQuery query(db);
    bool success;
    if(ui->allowance_day->text()!=nullptr){
        QString sql=QString("update allowance set overtime=%4 where person_id=%1 and year=%2 and month=%3").arg(ui->person_id->text().toInt()).arg(ui->year->text().toInt()).arg(ui->month->text().toInt()).arg(ui->allowance_day->text().toInt());
        success=query.exec(sql);
        error(success,query);
    }
    if(ui->allowance_type->text()!=nullptr){
        QString sql=QString("update allowance set overtime_type=%4 where person_id=%1 and year=%2 and month=%3").arg(ui->person_id->text().toInt()).arg(ui->year->text().toInt()).arg(ui->month->text().toInt()).arg(ui->allowance_type->text().toInt());
        success=query.exec(sql);
        error(success,query);
    }
    on_allowance_select_clicked();
    ui->person_id->clear();
    ui->year->clear();
    ui->month->clear();
    ui->allowance_day->clear();
    ui->allowance_type->clear();
}

void MainWindow::on_allowance_dele_clicked()//删除加班记录,grant<2
{
    if(select_id(1)<0){
            return;
    }
    else if(select_id(1)==0){
        QMessageBox::warning(nullptr,"warning","该记录不存在!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    //权限
    if(grant==2){
        QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    else if (grant==1) {
        QSqlQuery query(db);
        QString sql=QString("select depart_id from person where id=%1").arg(ui->person_id->text().toInt());
        query.exec(sql);
        query.next();
        if(query.value("depart_id").toInt()!=depart_id){
            QMessageBox::warning(nullptr,"warning","没有访问权限!",QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    //删除
    QSqlQuery query(db);
    QString sql=QString("delete from allowance where person_id=%1 and year=%2 and month=%3").arg(ui->person_id->text().toInt()).arg(ui->year->text().toInt()).arg(ui->month->text().toInt());
    bool success=query.exec(sql);
    if(error(success,query)){
        on_allowance_select_clicked();
    }
    ui->person_id->clear();
    ui->year->clear();
    ui->month->clear();
}
