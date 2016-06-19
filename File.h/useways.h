#ifndef USEWAYS_H
#define USEWAYS_H

#include <QDialog>

namespace Ui {
class useWays;
}

class useWays : public QDialog
{
    Q_OBJECT

public:
    explicit useWays(QWidget *parent = 0);
    ~useWays();

private:
    Ui::useWays *ui;
};

#endif // USEWAYS_H
