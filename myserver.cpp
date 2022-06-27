#include "myserver.h"
#include "IDataBase.cpp"
#include "IDataBase.h"
#include "DBErrors.h"
#include <iostream>
#include <vector>
#include <string>

myserver::myserver(){}

myserver::~myserver(){}

void myserver::startServer(){
    if(this->listen(QHostAddress::Any,5555)){
        qDebug()<<"Listening";
    }
    else{
        qDebug()<<"Not listening";
    }
}

void myserver::incomingConnection(qintptr pisocketDescriptor){
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(pisocketDescriptor);

    connect(socket, SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug()<<pisocketDescriptor<<"Client connected";

    socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
    qDebug()<<"Send client connect status - YES";
}

void myserver::sockReady(){
}


void myserver::sockDisc(){
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
