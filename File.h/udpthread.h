#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QThread>
#include <QUdpSocket>
#include <QByteArray>
#include <QList>
#include <QTimer>
#include <QSettings>
#include <QMessageBox>
#include <QSettings>
#include <QTextCodec>
#include <QDebug>
#include <QElapsedTimer>
#include <QApplication>


class QUdpSocket;
class UdpThread : public QThread
{
    Q_OBJECT
public:
    explicit UdpThread(QObject *parent = 0);

signals:
    void sendMessage(QByteArray datagram);

    void LookforIP(QList<QByteArray> listip);       //备用，把收到的IP记录发送到主进程

private slots:
    void readMessage();

    void sendControl(QByteArray datagram);

    void ControlStates();

public:
    QUdpSocket *TeacherUdp;
    QByteArray FirstStates;
    QByteArray startip;
    QByteArray endip;
    QList<QByteArray> list;     //备用，记录所有主机IP
    QList<QString> listIP;
    QString TeamIp;
    int Port;
};

#endif // UDPTHREAD_H
