#ifndef FREECONTROL_H
#define FREECONTROL_H

#include <QDialog>
#include <QMessageBox>
#include <string>
#include <QFont>

namespace Ui {
class FreeControl;
}

class FreeControl : public QDialog
{
    Q_OBJECT

signals:
    void sendMessage(QByteArray msg);

public:
    explicit FreeControl(QWidget *parent = 0);
    ~FreeControl();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::FreeControl *ui;
    QFont font;
};

#endif // FREECONTROL_H
