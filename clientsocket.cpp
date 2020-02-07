#include "clientsocket.h"

#include <qbluetoothsocket.h>

ClientSocket::ClientSocket(QObject *parent)
: QObject(parent), socket(nullptr)
{
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
    qWarning("Create Socket");
    socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void ClientSocket::stopClient()
{
    delete socket;
    socket = nullptr;
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
    //emit connected(socket->peerName());
}

