#include "server.h"

Server::Server(QObject* parent):QTcpServer(parent)
{

}

void Server::onReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket)
        return;

    QByteArray requestData = clientSocket->readAll();
    qDebug() << "Received data:" << requestData;

    // Process the received data

    // Example: Echo back the received data
    clientSocket->write(requestData);
}


void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientSocket = new QTcpSocket(this);
    if (!clientSocket->setSocketDescriptor(socketDescriptor))
    {
        // Handle error
        delete clientSocket;
        return;
    }

    // Connect signals/slots for clientSocket if needed

    qDebug() << "New connection established.";

    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

bool Server::startServer(int port) {
     qDebug()<<port;
     if(port==0)
        port =1234;

       if (!listen(QHostAddress::Any, port)) {
           qDebug() << "Server could not start!";
           return false;
       }
       qDebug() << "Server listening on port" << serverPort();
       return true;
   }

bool Server::stopServer() {
    if (isListening()) {
        close();
        qDebug() << "Server stopped";
        return true;
    }
    return false;
}

