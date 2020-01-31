#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent)
: QObject(parent), socket(0)
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
    qWarning("ConnectToService done");
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void ClientSocket::stopClient()
{
    delete socket;
    socket = 0;
}

void ClientSocket::readSocket()
{
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QByteArray line = socket->readLine();


            }
}

void ClientSocket::connected()
{
    //emit connected(socket->peerName());
}

