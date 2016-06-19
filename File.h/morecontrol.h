#ifndef MORECONTROL_H
#define MORECONTROL_H

#include <QDialog>
#include <QByteArray>
#include <QMessageBox>
#include <QFont>

namespace Ui {
class MoreControl;
}

class MoreControl : public QDialog
{
    Q_OBJECT

public:
    explicit MoreControl(QWidget *parent = 0);
    ~MoreControl();

signals:
    void sendMessage(QByteArray msg, QByteArray msgs);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MoreControl *ui;
    QFont font;
};

#endif // MORECONTROL_H
