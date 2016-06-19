#include "useways.h"
#include "ui_useways.h"

useWays::useWays(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::useWays)
{
    ui->setupUi(this);
}

useWays::~useWays()
{
    delete ui;
}
