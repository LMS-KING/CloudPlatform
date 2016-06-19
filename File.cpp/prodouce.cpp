#include "prodouce.h"
#include "ui_prodouce.h"

prodouce::prodouce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prodouce)
{
    ui->setupUi(this);
}

prodouce::~prodouce()
{
    delete ui;
}

void prodouce::on_pushButton_clicked()
{
    this->close();
}
