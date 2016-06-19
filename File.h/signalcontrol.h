#ifndef SIGNALCONTROL_H
#define SIGNALCONTROL_H

#include <QDialog>
#include <QByteArray>
#include <QMessageBox>
#include <QEvent>
#include <QFont>

namespace Ui {
class SignalControl;
}

class SignalControl : public QDialog
{
    Q_OBJECT

public:
    explicit SignalControl(QWidget *parent = 0);
    ~SignalControl();

signals:
    void sendMessage(QByteArray msg);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

   // bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::SignalControl *ui;
    QFont font;
};

#endif // SIGNALCONTROL_H
