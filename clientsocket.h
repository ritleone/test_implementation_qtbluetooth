#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <qbluetoothserviceinfo.h>

#include <QBluetoothSocket>

#include <QtCore/QObject>

QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE

class ClientSocket : public QObject
{
public:
    explicit ClientSocket(QObject *parent = 0);
    ~ClientSocket();
    void startClient(const QBluetoothServiceInfo &remoteService);
    void stopClient();

signals:
    void connected(const QString &name);
    void disconnected();

private slots:
    void readSocket();
    void connected();

private:
    QBluetoothSocket *socket;
};

#endif // CLIENTSOCKET_H
