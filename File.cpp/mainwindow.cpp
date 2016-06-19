#include "mainwindow.h"
#include "ui_mainwindow.h"

QByteArray GMessage;
QByteArray StartIP;
QByteArray EndIP;
QList<QByteArray> ReadIP;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GMessage = "#BDQD";
    StartIP = "0";
    EndIP = "0";

    setObjectName("mainWindow");
    setStyleSheet("#mainWindow{border-image:url(:/new/zhuomian.jpg)}");
    ui->pushButton->setStyleSheet("QPushButton{color:red;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    ui->pushButton_2->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px}");
    ui->pushButton_3->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:2px 4px}");

    udpThread = new UdpThread;
    udpThread->start();
    free = new FreeControl(this);
    signal = new SignalControl(this);
    more = new MoreControl(this);
    stustas = new StudentStatus(this);
    useway = new useWays(this);
    produces = new prodouce(this);

    connect(free,SIGNAL(sendMessage(QByteArray)),this,SLOT(readMessagefree(QByteArray )));
    connect(signal,SIGNAL(sendMessage(QByteArray)),this,SLOT(readMessagesignal(QByteArray)));
    connect(more,SIGNAL(sendMessage(QByteArray,QByteArray)),this,SLOT(readMessagemore(QByteArray,QByteArray)));
    connect(udpThread,SIGNAL(LookforIP(QList<QByteArray>)),this,SLOT(readAllIP(QList<QByteArray>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_triggered()        //打开应用
{
    fileName = QFileDialog::getOpenFileName(this,tr("文件选择"),"D:");
    if(fileName == NULL)
        return;
    QString filename = "@" + fileName;
    GMessage = filename.toLocal8Bit();
    qDebug()<<GMessage;
}

void MainWindow::on_delete_2_triggered()        //删除文件
{
    fileName = QFileDialog::getOpenFileName(this,tr("文件选择"),"D:");
    if(fileName == NULL)
        return;
    QMessageBox tip(QMessageBox::Warning,tr("删除文件"),tr("是否确认删除\n%1").arg(fileName),QMessageBox::Yes | QMessageBox::No, NULL);
    if (tip.exec() == QMessageBox::No)
    {
        return;
    }
    QString filename = "&" + fileName;
    GMessage = filename.toLocal8Bit();
}

void MainWindow::on_freecontrol_triggered()     //自由命令菜单
{
    free->setWindowTitle(tr("自由命令"));
    free->setModal(true);
    free->show();
}

void MainWindow::readMessagesignal(QByteArray mag)      //接收控制单台主机的IP
{
    StartIP = mag;
}

void MainWindow::readMessagemore(QByteArray sip, QByteArray eip)    //接收控制多台主机的IP
{
    StartIP = sip;
    EndIP = eip;
}

void MainWindow::readAllIP(QList<QByteArray> allip)
{
    ReadIP = allip;
}

void MainWindow::readMessagefree(QByteArray mag)     //接收自由命令
{
    GMessage = mag;
}

void MainWindow::on_allclose_triggered()        //全体关机命令
{
    QMessageBox tip(QMessageBox::Warning,tr("关机命令"),tr("是否确认全体关机"),QMessageBox::Yes | QMessageBox::No, NULL);
    if (tip.exec() == QMessageBox::No)
        return;
    GMessage = QString("*").toLatin1() + QString("SHUTDOWN").toLatin1();
}

void MainWindow::on_signalcontrol_triggered()       //控制单台主机菜单
{
    signal->setWindowTitle(tr("控制单台主机"));
    signal->setModal(true);
    signal->show();
}

void MainWindow::on_morecontrol_triggered()
{
    more->setWindowTitle(tr("控制多台主机"));
    more->setModal(true);
    more->show();
}

void MainWindow::on_status_triggered()      //显示学生状态
{
    stustas->setWindowTitle(tr("学生状态"));
    stustas->setModal(true);
    stustas->show();
}

void MainWindow::on_pushButton_clicked()     //本地启动
{
    if(GMessage == "#BDQD")
        return;
    QMessageBox tip(QMessageBox::Warning,tr("切换操作"),tr("是否确认切换到\n本机启动"),QMessageBox::Yes | QMessageBox::No, NULL);
    if (tip.exec() == QMessageBox::No)
    {
        return;
    }
    ui->pushButton->setStyleSheet("QPushButton{color:red;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    ui->pushButton_2->setStyleSheet("QPushButton{color:black;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    ui->pushButton_3->setStyleSheet("QPushButton{color:black;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    GMessage = "#BDQD";
}

void MainWindow::on_pushButton_2_clicked()    //云桌面（自由）
{
    if(GMessage == "#YUNA")
        return;
    QMessageBox tip(QMessageBox::Warning,tr("切换操作"),tr("是否确认切换到\n自由云桌面"),QMessageBox::Yes | QMessageBox::No, NULL);
    if (tip.exec() == QMessageBox::No)
    {
        return;
    }
    ui->pushButton->setStyleSheet("QPushButton{color:black;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    ui->pushButton_2->setStyleSheet("QPushButton{color:red;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    ui->pushButton_3->setStyleSheet("QPushButton{color:black;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    GMessage = "#YUNA";
}

void MainWindow::on_pushButton_3_clicked()     //云桌面（受限）
{
    if(GMessage == "#YUNB")
        return;
    QMessageBox tip(QMessageBox::Warning,tr("切换操作"),tr("是否确认切换到\n受控云桌面"),QMessageBox::Yes | QMessageBox::No, NULL);
    if (tip.exec() == QMessageBox::No)
    {
        return;
    }
    ui->pushButton->setStyleSheet("QPushButton{color:black;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    ui->pushButton_2->setStyleSheet("QPushButton{color:black;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    ui->pushButton_3->setStyleSheet("QPushButton{color:red;border:2px groove gray;border-radius:10px;padding:2px 4px}");
    GMessage = "#YUNB";
}

void MainWindow::on_use_triggered()     //使用方法
{
    useway->setWindowTitle(tr("使用说明"));
    useway->setModal(true);
    useway->show();
}

void MainWindow::on_action_3_triggered()      //关于产品
{
    produces->setWindowTitle(tr("关于产品"));
    produces->setModal(true);
    produces->show();
}

void MainWindow::closeEvent(QCloseEvent *event)       //关闭事件重写
{
    QMessageBox tip(QMessageBox::Warning,tr("退出操作"),tr("再次登陆时所有学生将进入本地启动\n是否确认退出"),QMessageBox::Yes | QMessageBox::No, NULL);
    if (tip.exec() == QMessageBox::No)
    {
        event->ignore();
        return;
    }
}
