#include "clientsocket.h"

#include <qbluetoothsocket.h>

ClientSocket::ClientSocket(QObject *parent)
: QObject(parent), socket(nullptr)
{
    CSCreate = 1;
}

ClientSocket::~ClientSocket()
{
    stopClient();
}

void ClientSocket::startClient(const QBluetoothServiceInfo &remoteService)
{
    if (socket)
        return;

    // Connect to service
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "Create socket";
    socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void ClientSocket::stopClient()
{
    CSCreate = 0;
    delete socket;
    socket = nullptr;
    qWarning("Socket client arreter");
}

void ClientSocket::readSocket()
{
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QByteArray line = socket->readLine();
        emit messageReceived(socket->peerName(), QString::fromUtf8(line.constData(), line.length()));

    }
}

void ClientSocket::connected()
{
    emit connected(socket->peerName());

}

