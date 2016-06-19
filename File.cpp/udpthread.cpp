#include "udpthread.h"

extern QByteArray GMessage;
extern QByteArray StartIP;
extern QByteArray EndIP;

UdpThread::UdpThread(QObject *parent) :
    QThread(parent)
{
    FirstStates = GMessage;
    startip = StartIP;
    endip = EndIP;

    QSettings *pro = new QSettings("IP.ini",QSettings::IniFormat,0);
    QTextCodec *data = QTextCodec::codecForName("GBK");
    pro->setIniCodec(data);

    //及时判断教师端状态
    QTimer *time = new QTimer(0);
    connect(time,SIGNAL(timeout()),this,SLOT(ControlStates()));
    time->start(2000);

    TeacherUdp = new QUdpSocket(this);
    TeacherUdp->bind(pro->value("PORT/PORT").toInt(), QUdpSocket::ShareAddress);

    //关联信号和槽函数
    connect(TeacherUdp,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(this,SIGNAL(sendMessage(QByteArray)),this,SLOT(sendControl(QByteArray)));

    //教师机启动后发送两遍本地启动命令
        TeacherUdp->writeDatagram("##BDQD",6,QHostAddress::Broadcast,
                              pro->value("PORT/PORT").toInt());
        if(!TeacherUdp->waitForBytesWritten(2000))
            TeacherUdp->writeDatagram("##BDQD",6,QHostAddress::Broadcast,
                                  pro->value("PORT/PORT").toInt());
    delete pro;
}

void UdpThread::readMessage()      //接收数据(学生端IP)
{   
    while(TeacherUdp->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(TeacherUdp->pendingDatagramSize());
        TeacherUdp->readDatagram(datagram.data(),datagram.size());

//        qDebug()<<datagram;
//        qDebug()<<datagram;

        /*此处要判断数据是否为IP地址，如果是就加入list链表，否则退出函数*/
        if(datagram.at(0) - '0' != 1)       //接收本机发出的命令就退出
        {
            return;
        }
        else if(datagram.at(1) - '0' == 0)   //是IP上线，处理
        {
            if(!list.contains(datagram))     //如果该IP地址第一次传过来就加进IP地址链
                list.append(datagram);
            emit LookforIP(list);
        }
        else if(datagram.at(1) - '0' == 1)
        {
            datagram  = datagram.right(datagram.length() - 1);
            list.removeOne(datagram);
            emit LookforIP(list);
            return;
        }
        else
        {
            QMessageBox::information(0,tr("错误提示"),tr("网络错误!"),QMessageBox::Yes);
            return;
        }

        if(FirstStates == "#BDQD")  //如果是本地启动，不在广播
            return;
    }

    sleep(3);
    emit sendMessage(FirstStates);      //教师接收到数据(IP)，说明学生启动慢了，新状态重新广播
}

void UdpThread::sendControl(QByteArray datagram)       //发送指令
{
    QSettings *pro = new QSettings("IP.ini",QSettings::IniFormat,0);
    QTextCodec *data = QTextCodec::codecForName("GBK");
    pro->setIniCodec(data);

    if(startip == "0")      //全体控制,多播
    {
        if(datagram == "*SHUTDOWN")
        {
            list.clear();
            emit LookforIP(list);
        }

        TeacherUdp->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,
                              pro->value("PORT/PORT").toInt());
        if(!TeacherUdp->waitForBytesWritten(2000))
            TeacherUdp->writeDatagram(FirstStates.data(),FirstStates.size(),QHostAddress::Broadcast,
                                  pro->value("PORT/PORT").toInt());

        delete pro;
        return;
    }
    //控制单台或多台，单播
    if(endip == "0")  //控制单台
    {
        if(datagram == "*SHUTDOWN")
        {
            list.removeOne(startip);
            emit LookforIP(list);
        }

        TeacherUdp->writeDatagram(datagram.data(),datagram.size(),QHostAddress(QString(startip)),
                              pro->value("PORT/PORT").toInt());
        if(!TeacherUdp->waitForBytesWritten(2000))
            TeacherUdp->writeDatagram(FirstStates.data(),FirstStates.size(),QHostAddress(QString(startip)),
                                  pro->value("PORT/PORT").toInt());
    }
    else        //控制多台
    {
        QString ip1 = QString(startip);
        QString ip2 = QString(endip);
        QStringList Qlist1 = ip1.split(".");
        int start = Qlist1.at(3).toInt();      //起始IP末尾段
        QStringList Qlist2 = ip2.split(".");
        int end = Qlist2.at(3).toInt();      //终止IP末尾段
        //法一
        int No1 = Qlist1.at(0).toInt();     //记录第一段，如10.64.54.100中的10
        int No2 = Qlist1.at(1).toInt();     //记录第二段64
        int No3 = Qlist1.at(2).toInt();     //记录第三段54
        QString ip = QString::number(No1) + "." + QString::number(No2) + "." +                   QString::number(No3) + ".";

        //法二
        //QString ips = ip1.left(9);

        for(int i = start; i <= end; i++)    //读取所有IP
        {
            listIP.append(ip + QString::number(i));
        }

        for(int j = 0; j < listIP.size(); j++)
        {
            if(datagram == "*SHUTDOWN")
            {
                list.removeOne(listIP.at(j).toLatin1());
            }
            TeacherUdp->writeDatagram(datagram.data(),datagram.size(),QHostAddress(listIP.at(j)),
                                  pro->value("PORT/PORT").toInt());
        }
        emit LookforIP(list);
    }
    delete pro;
}

void UdpThread::ControlStates()         //判断教师端命令是否改变
{
    if(startip != StartIP || endip != EndIP)
    {
        startip = StartIP;
        endip = EndIP;
    }

    if(FirstStates == GMessage)
        return;
    FirstStates = GMessage;
    emit sendMessage(FirstStates);
}


