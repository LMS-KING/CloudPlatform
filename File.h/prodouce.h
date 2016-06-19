#ifndef PRODOUCE_H
#define PRODOUCE_H

#include <QDialog>

namespace Ui {
class prodouce;
}

class prodouce : public QDialog
{
    Q_OBJECT

public:
    explicit prodouce(QWidget *parent = 0);
    ~prodouce();

private slots:
    void on_pushButton_clicked();

private:
    Ui::prodouce *ui;
};

#endif // PRODOUCE_H
