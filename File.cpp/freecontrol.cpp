#include "freecontrol.h"
#include "ui_freecontrol.h"

FreeControl::FreeControl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FreeControl)
{
    ui->setupUi(this);
    font.setPixelSize(15);
    ui->lineEdit->setFont(font);
}

FreeControl::~FreeControl()
{
    delete ui;
}

void FreeControl::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    this->close();
}

void FreeControl::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("操作提示"),tr("请输入命令"),QMessageBox::Yes, NULL);
        return;
    }

    QString control = "$" + ui->lineEdit->text();
    emit sendMessage(control.toLatin1());
    ui->lineEdit->clear();

    QMessageBox::information(this,tr("操作提示"),tr("命令已发送！"),QMessageBox::Yes, NULL);
}
