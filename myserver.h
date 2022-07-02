#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QByteArray>
#include <iostream>
#include <string>
#include <vector>
#include "3rdparty/json.hpp"

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

    void AddUser(const std::vector <std::string> &msg);
    void GetUserId(const std::vector <std::string> &msg);
    void GetFriendList();
    void AddFriend(const std::vector <std::string> &msg);
    void DeleteFriend(const std::vector <std::string> &msg);
    void GetFriendRequestsList();
    void AddFriendRequest(const std::vector <std::string> &msg);
    void DeleteFriendRequest(const std::vector <std::string> &msg);
    void CreateCategory(const std::vector <std::string> &msg);
    void GetCategory();
    void DeleteCategory(const std::vector <std::string> &msg);
    void ChangeCategoryName(const std::vector <std::string> &msg);
    void AddNote(const std::vector <std::string> &msg);
    void GetNote();
    void ChangeCategoryId(const std::vector <std::string> &msg);
    void SetHeader(const std::vector <std::string> &msg);
    void SetText(const std::vector <std::string> &msg);
    void AddFriendAccess(const std::vector <std::string> &msg);
    void CheckFriendAccess(const std::vector <std::string> &msg);
    void DeleteFriendAccess(const std::vector <std::string> &msg);
    void socketWrite(const QByteArray &bytes);
    void parseJson(QByteArray &Data);
public:
    CMyServer();
    ~CMyServer();

public slots:
    void startServer();
    void incomingConnection(qintptr pisocketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif // MYSERVER_H
