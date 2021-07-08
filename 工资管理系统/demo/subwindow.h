#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QMainWindow>

namespace Ui {
class SubWindow;
}

class SubWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubWindow(QWidget *parent = nullptr);
    ~SubWindow();

private slots:
    void on_add_person_clicked();
signals:
    void SendData_sub(int id,QString name,QString gender,QString tele,int depart,int job);
private:
    Ui::SubWindow *ui;
};

#endif // SUBWINDOW_H
