#include "studentstatus.h"
#include "ui_studentstatus.h"

extern QList<QByteArray> ReadIP;

StudentStatus::StudentStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentStatus)
{
    ui->setupUi(this);

    QSettings *pro = new QSettings("IP.ini",QSettings::IniFormat,0);
    QTextCodec *data = QTextCodec::codecForName("GBK");
    pro->setIniCodec(data);
    //设置字体
    font.setPixelSize(25);
    fontview.setPixelSize(15);
    ui->ip1->setFont(font);
    ui->ip2->setFont(font);
    ui->number->setFont(font);
    ui->tableView->setFont(fontview);

    //从IP.ini文件读出机房所有IP
    ui->ip1->setText(pro->value("IP/STARTIP").toString());
    ui->ip2->setText(pro->value("IP/ENDIP").toString());
    QString ip1 = pro->value("IP/STARTIP").toString();
    QString ip2 = pro->value("IP/ENDIP").toString();
    QStringList Qlist1 = ip1.split(".");
    int startip = Qlist1.at(3).toInt();      //起始IP末尾段
    QStringList Qlist2 = ip2.split(".");
    int endip = Qlist2.at(3).toInt();      //终止IP末尾段
    //法一
    int No1 = Qlist1.at(0).toInt();     //记录第一段，如10.64.54.100中的10
    int No2 = Qlist1.at(1).toInt();     //记录第二段64
    int No3 = Qlist1.at(2).toInt();     //记录第三段54
    QString ip = QString::number(No1) + "." + QString::number(No2) + "." +                   QString::number(No3) + ".";

    //法二
//    QString ips = ip1.left(9);

    for(int i = startip; i <= endip; i++)    //读取所有IP
    {
        //AllIP<<(ip + QString::number(i)).toLatin1();
        list.append(ip + QString::number(i));
    }
    delete pro;

    QTimer *time = new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(timeOut()));
    time->start(5000);

    itme_model = new QStandardItemModel();

    itme_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("学生IP")));
    itme_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("学生状态")));
    ui->tableView->setModel(itme_model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置列宽
    ui->tableView->setColumnWidth(0,240);       //IP列
    ui->tableView->setColumnWidth(1,165);       //状态列
    //表不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置列宽不可变动，即不能通过鼠标拖动增加列宽
    //ui->tableView->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    //ui->tableView->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);

    //IP降序排序
    itme_model->sort(0, Qt::AscendingOrder);
    //初始状态
    for(int i = 0; i < list.size(); i++)
    {
        QStandardItem *item = new QStandardItem(tr("%1").arg(list.at(i)));
        //设置状态项
        QStandardItem *itemstatus1 = new QStandardItem( QString("在线"));
        QStandardItem *itemstatus2 = new QStandardItem( QString("离线"));
        itme_model->setItem(i,0,item);
        if(ReadIP.contains(list.at(i).toLatin1()))
        {
            itme_model->setItem(i, 1, itemstatus1);
            //设置文本颜色
            itme_model->item(i, 1)->setForeground(QBrush(QColor(0, 255, 0)));
        }
        else
        {
            itme_model->setItem(i, 1, itemstatus2);
            //设置文本颜色
            itme_model->item(i, 1)->setForeground(QBrush(QColor(255, 0, 0)));
        }

        //设置字体
        itme_model->item(i, 0)->setFont(fontview);
        //设置文本居中
        itme_model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        //设置字体
        itme_model->item(i, 1)->setFont(fontview);
        //设置文本居中
        itme_model->item(i, 1)->setTextAlignment(Qt::AlignCenter);
    }
    //ui->number->setText(QString::number(ReadIP.size()));
}

StudentStatus::~StudentStatus()
{
    delete ui;
}

void StudentStatus::timeOut()       //每5s遍历IP，改变状态
{
    ui->number->setText(QString::number(ReadIP.size()));
    for(int i = 0; i < list.size(); i++)
    {
        QStandardItem *item = new QStandardItem(tr("%1").arg(list.at(i)));
        //设置状态项
        QStandardItem *itemstatus1 = new QStandardItem( QString("在线"));
        QStandardItem *itemstatus2 = new QStandardItem( QString("离线"));
        itme_model->setItem(i,0,item);
        if(ReadIP.contains(list.at(i).toLatin1()))
        {
            itme_model->setItem(i, 1, itemstatus1);
            //设置文本颜色
            itme_model->item(i, 1)->setForeground(QBrush(QColor(0, 255, 0)));
        }
        else
        {
            itme_model->setItem(i, 1, itemstatus2);
            //设置文本颜色
            itme_model->item(i, 1)->setForeground(QBrush(QColor(255, 0, 0)));
        }
        //设置字体
        itme_model->item(i, 0)->setFont(fontview);
        //设置文本居中
        itme_model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        //设置字体
        itme_model->item(i, 1)->setFont(fontview);
        //设置文本居中
        itme_model->item(i, 1)->setTextAlignment(Qt::AlignCenter);
    }
}
