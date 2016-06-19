#include "signalcontrol.h"
#include "ui_signalcontrol.h"

extern QList<QByteArray> ReadIP;

SignalControl::SignalControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignalControl)
{
    ui->setupUi(this);
    font.setPixelSize(25);
    ui->lineEdit->setFont(font);
    //ui->lineEdit->installEventFilter(this);
}

SignalControl::~SignalControl()
{
    delete ui;
}

void SignalControl::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("操作提示"),tr("请输入学生IP！"),QMessageBox::Yes, NULL);
        return;
    }

    if(!ReadIP.contains(ui->lineEdit->text().toLatin1()))
    {
        QMessageBox::information(this,tr("操作提示"),tr("输入IP有误或该学生已离线！请到信息显示菜单查看详情！"),QMessageBox::Yes, NULL);
        return;
    }

    emit sendMessage(ui->lineEdit->text().toLatin1());
    ui->lineEdit->clear();
    this->close();
}

void SignalControl::on_pushButton_2_clicked()
{
    QByteArray close = "0";
    emit sendMessage(close);
    this->close();
}

