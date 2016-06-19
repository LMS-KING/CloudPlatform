#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QCloseEvent>
#include <QEvent>
#include "udpthread.h"
#include "freecontrol.h"
#include "signalcontrol.h"
#include "morecontrol.h"
#include "studentstatus.h"
#include "useways.h"
#include "prodouce.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:


private slots:

    void on_open_triggered();

    void on_delete_2_triggered();

    void on_freecontrol_triggered();

    void readMessagefree(QByteArray mag);   //接收自由命令窗口命令

    void readMessagesignal(QByteArray mag); //接收控制单台窗口IP

    void readMessagemore(QByteArray sip, QByteArray eip);  //接收控制多台窗口IP

    void readAllIP(QList<QByteArray> allip);

    void on_allclose_triggered();

    void on_signalcontrol_triggered();

    void on_morecontrol_triggered();

    void on_status_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_use_triggered();

    void on_action_3_triggered();

    void closeEvent(QCloseEvent *event);      //关闭事件重写

private:
    Ui::MainWindow *ui;
    UdpThread *udpThread;
    QString fileName;
    FreeControl *free;
    SignalControl *signal;
    MoreControl *more;
    StudentStatus *stustas;
    useWays *useway;
    prodouce *produces;
};

#endif // MAINWINDOW_H
