#ifndef STUDENTSTATUS_H
#define STUDENTSTATUS_H

#include <QDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QByteArray>
#include <QTimer>
#include <QSettings>
#include <QTextCodec>
#include <QFont>
#include <QList>
#include <QStringList>
#include <QDebug>

namespace Ui {
class StudentStatus;
}

class StudentStatus : public QDialog
{
    Q_OBJECT

public:
    explicit StudentStatus(QWidget *parent = 0);
    ~StudentStatus();

private slots:
    void timeOut();

private:
    Ui::StudentStatus *ui;
    QStandardItemModel *itme_model;
    QList<QString> list;
    QFont font;
    QFont fontview;
};

#endif // STUDENTSTATUS_H
