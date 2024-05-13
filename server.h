#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets>
#include <QTcpServer>
#include <QTcpSocket>

//Serevr Class
class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);
    bool startServer(int port);
    bool stopServer();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
};
#endif // SERVER_H
