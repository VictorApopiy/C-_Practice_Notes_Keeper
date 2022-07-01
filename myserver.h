#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QByteArray>
#include <QtCore>
#include <iostream>
#include <QIODevice>
#include <string>
#include <vector>
#include <memory.h>
#include <QRegularExpression>
#include <QStringConverter>
#include "lib/json.hpp"

#define PORT 5555
#define TIME 5000

class CMyServer: public QTcpServer{
    Q_OBJECT
private:
    int iUserId = -1;
    int iNoteId = -1;
    int iFriendId = -1;
    int iCategoryId = -1;
    int iFrReqId = -1;
    int iId = -1;
    QTcpSocket* socket;
    QByteArray Data;
    QByteArray res;
    QJsonDocument document;
    QByteArray bytes;
public:
    CMyServer();
    ~CMyServer();

public slots:
    void startServer();
    void incomingConnection(qintptr pisocketDescriptor);
    void sockReady();
    void sockDisc();
    void m_AddUser(std::vector <std::string> &msg);
    void m_GetUserId(std::vector <std::string> &msg);
    void m_GetFriendList(std::vector <std::string> &msg);
    void m_AddFriend(std::vector <std::string> &msg);
    void m_DeleteFriend(std::vector <std::string> &msg);
    void m_GetFriendRequestsList(std::vector <std::string> &msg);
    void m_AddFriendRequest(std::vector <std::string> &msg);
    void m_DeleteFriendRequest(std::vector <std::string> &msg);
    void m_CreateCategory(std::vector <std::string> &msg);
    void m_GetCategory(std::vector <std::string> &msg);
    void m_DeleteCategory(std::vector <std::string> &msg);
    void m_ChangeCategoryName(std::vector <std::string> &msg);
    void m_AddNote(std::vector <std::string> &msg);
    void m_GetNote(std::vector <std::string> &msg);
    void m_ChangeCategoryId(std::vector <std::string> &msg);
    void m_SetHeader(std::vector <std::string> &msg);
    void m_SetText(std::vector <std::string> &msg);
    void m_AddFriendAccess(std::vector <std::string> &msg);
    void m_CheckFriendAccess(std::vector <std::string> &msg);
    void m_DeleteFriendAccess(std::vector <std::string> &msg);
    void m_socketWrite(QByteArray &bytes);
};

#endif // MYSERVER_H
