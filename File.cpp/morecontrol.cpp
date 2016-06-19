#include "morecontrol.h"
#include "ui_morecontrol.h"

extern QList<QByteArray> ReadIP;

MoreControl::MoreControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoreControl)
{
    ui->setupUi(this);
    font.setPixelSize(25);
    ui->lineEdit->setFont(font);
    ui->lineEdit_2->setFont(font);
}

MoreControl::~MoreControl()
{
    delete ui;
}

void MoreControl::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::information(this,tr("操作提示"),tr("请输入IP"),QMessageBox::Yes, NULL);
        return;
    }

    if(!ReadIP.contains(ui->lineEdit->text().toLatin1()) || !ReadIP.contains(ui->lineEdit_2->text().toLatin1()))
    {
        if(!ReadIP.contains(ui->lineEdit->text().toLatin1()))
            QMessageBox::information(this,tr("操作提示"),tr("起始IP有误或该学生已离线！请到信息显示菜单查看详情！"),QMessageBox::Yes, NULL);
        else
             QMessageBox::information(this,tr("操作提示"),tr("终止IP有误或该学生已离线！请到信息显示菜单查看详情！"),QMessageBox::Yes, NULL);
        return;
    }

    emit sendMessage(ui->lineEdit->text().toLatin1(), ui->lineEdit_2->text().toLatin1());
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    this->close();
}

void MoreControl::on_pushButton_2_clicked()
{
    QByteArray close = "0";
    emit sendMessage(close, close);
    this->close();
}
