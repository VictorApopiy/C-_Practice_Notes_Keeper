#include "myserver.h"
#include "IDataBase.cpp"
#include "IDataBase.h"
#include "DBErrors.h"
#include <iostream>
#include <vector>
#include <string>

CMyServer::CMyServer(){}

CMyServer::~CMyServer(){}

void CMyServer::startServer(){
    if(listen(QHostAddress::Any,PORT)){
        qDebug()<<"Listening for connection";
    }
    else{
        qDebug()<<"Not listening for connection";
    }
}

void CMyServer::incomingConnection(qintptr pisocketDescriptor){
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(pisocketDescriptor);

    connect(socket, SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug()<<pisocketDescriptor<<"Client connected";

    socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
    qDebug()<<"Send client connect status - YES";
}

void CMyServer::sockReady(){
    Data = socket->readAll();
    qDebug()<<"Data: "<<Data;
    std::vector <std::string> msg;

    nlohmann::json j;
    j = nlohmann::json::parse(QString(Data).toStdString());

    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            msg.push_back(it.value());
    }

        if(msg.at(0)=="AddUser"){
            CMyServer::m_AddUser(msg);
        }
        else if(msg.at(0)=="GetUserId"){
            CMyServer::m_GetUserId(msg);
        }
        else if(msg.at(0)=="GetFriendList"){
            CMyServer::m_GetFriendList(msg);
        }
        else if(msg.at(0)=="AddFriend"){
            CMyServer::m_AddFriend(msg);
        }
        else if(msg.at(0)=="DeleteFriend"){
            CMyServer::m_DeleteFriend(msg);
        }
        else if(msg.at(0)=="GetFriendRequestsList"){
            CMyServer::m_GetFriendRequestsList(msg);
        }
        else if(msg.at(0)=="AddFriendRequest"){
            CMyServer::m_AddFriendRequest(msg);
        }
        else if(msg.at(0)=="DeleteFriendRequest"){
            CMyServer::m_DeleteFriendRequest(msg);
        }
        else if(msg.at(0)=="CreateCategory"){
            CMyServer::m_CreateCategory(msg);
        }
        else if(msg.at(0)=="GetCategory"){
            CMyServer::m_GetCategory(msg);
        }
        else if(msg.at(0)=="DeleteCategory"){
            CMyServer::m_DeleteCategory(msg);
        }
        else if(msg.at(0)=="ChangeCategoryName"){
            CMyServer::m_ChangeCategoryName(msg);
        }
        else if(msg.at(0)=="AddNote"){
            CMyServer::m_AddNote(msg);
        }
        else if(msg.at(0)=="GetNote"){
            CMyServer::m_GetNote(msg);
        }
        else if(msg.at(0)=="ChangeCategoryId"){
            CMyServer::m_ChangeCategoryId(msg);
        }
        else if(msg.at(0)=="SetHeader"){
            CMyServer::m_SetHeader(msg);
        }
        else if(msg.at(0)=="SetText"){
            CMyServer::m_SetText(msg);
        }
        else if(msg.at(0)=="AddFriendAccess"){
            CMyServer::m_AddFriendAccess(msg);
        }
        else if(msg.at(0)=="CheckFriendAccess"){
            CMyServer::m_CheckFriendAccess(msg);
        }
        else if(msg.at(0)=="DeleteFriendAccess"){
            CMyServer::m_DeleteFriendAccess(msg);
        }
        else{
            bytes = "Unclear command";
            CMyServer::m_socketWrite(bytes);
         }
}
void CMyServer::m_AddUser(std::vector <std::string> &msg){
    int iRtCode = IDataBase::AddUser(msg[1], msg[2], iUserId);
    QJsonObject AddUser;
    switch(iRtCode){
    case SUCCESS:
        AddUser.insert("RequestType", "AddUser");
        AddUser.insert("SUCCESS", iUserId);
        document.setObject(AddUser);
        bytes = document.toJson( QJsonDocument::Indented );
        CMyServer::m_socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        bytes = "INVALID_INPUT_DATA";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_GetUserId(std::vector <std::string> &msg){
    int iRtCode = IDataBase::GetUserId(msg[1], msg[2], iUserId);
    QJsonObject GetUserId;
    switch(iRtCode){
    case SUCCESS:
        GetUserId.insert("RequestType", "GetUserId");
        GetUserId.insert("SUCCESS", iUserId);
        document.setObject(GetUserId);
        bytes = document.toJson( QJsonDocument::Indented );
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_GetFriendList(std::vector <std::string> &msg){
    std::vector <std::string> FriendList;
    int iRtCode = IDataBase::GetFriendList(iId, FriendList);
    QJsonObject GetFriendList;
    std::string rList = "";

    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= FriendList.size(); i++){
             rList += FriendList[i] + '|';
        }
        GetFriendList.insert("RequestType", "GetFriendList");
        GetFriendList.insert("SUCCESS", rList.data());
        document.setObject(GetFriendList);
        bytes = document.toJson( QJsonDocument::Indented );
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_AddFriend(std::vector <std::string> &msg){
    iUserId = std::stoi(msg[1]);
    iFriendId = std::stoi(msg[2]);
    int iRtCode = IDataBase::AddFriend(iUserId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        bytes = "NO_SUCH_FRIEND";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_DeleteFriend(std::vector <std::string> &msg){
    iUserId = std::stoi(msg[1]);
    iFriendId = std::stoi(msg[2]);
    int iRtCode = IDataBase::DeleteFriend(iUserId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        bytes = "NO_SUCH_FRIEND";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_GetFriendRequestsList(std::vector <std::string> &msg){
    std::vector<std::string> vsFrReqList;
    int iRtCode = IDataBase::GetFriendRequestsList(iId, vsFrReqList);
    QJsonObject GetFriendRequestsList;
    std::string rqList = "";
    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= vsFrReqList.size(); i++){
             rqList += vsFrReqList[i] + '|';
        }
        GetFriendRequestsList.insert("RequestType", "GetFriendRequestsList");
        GetFriendRequestsList.insert("SUCCESS", rqList.data());
        document.setObject(GetFriendRequestsList);
        bytes = document.toJson( QJsonDocument::Indented );
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_AddFriendRequest(std::vector <std::string> &msg){
    iUserId = std::stoi(msg[1]);
    iFrReqId = std::stoi(msg[2]);
    int iRtCode = IDataBase::AddFriendRequest(iUserId, iFrReqId);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        bytes = "NO_SUCH_FRIEND";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_DeleteFriendRequest(std::vector <std::string> &msg){
    iUserId = std::stoi(msg[1]);
    iFrReqId = std::stoi(msg[2]);
    int iRtCode = IDataBase::DeleteFriendRequest(iUserId, iFrReqId);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_REQUEST:
        bytes = "NO_SUCH_REQUEST";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_CreateCategory(std::vector <std::string> &msg){
    std::string sCategoryName;
    iCategoryId = std::stoi(msg[1]);
    iUserId = std::stoi(msg[2]);
    sCategoryName = msg[3];
    int iRtCode = IDataBase::CreateCategory(iUserId, sCategoryName, iCategoryId);
    QJsonObject CreateCategory;
    switch(iRtCode){
    case SUCCESS:
        CreateCategory.insert("RequestType", "CreateCategory");
        CreateCategory.insert("SUCCESS", iCategoryId);
        document.setObject(CreateCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        bytes = "INVALID_INPUT_DATA";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_GetCategory(std::vector <std::string> &msg){
    std::vector<std::string> vsCategory;
    int iRtCode = IDataBase::GetCategory(iCategoryId, iUserId, vsCategory);
    QJsonObject GetCategory;
    std::string gCategory = "";
    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= vsCategory.size(); i++){
             gCategory += vsCategory[i] + '|';
        }
        GetCategory.insert("RequestType", "GetCategory");
        GetCategory.insert("SUCCESS", gCategory.data());
        document.setObject(GetCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        bytes = "NO_SUCH_CATEGORY";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_DeleteCategory(std::vector <std::string> &msg){
    iCategoryId = std::stoi(msg[1]);
    iUserId = std::stoi(msg[2]);
    int iRtCode = IDataBase::DeleteCategory(iCategoryId, iUserId);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        bytes = "NO_SUCH_CATEGORY";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_ChangeCategoryName(std::vector <std::string> &msg){
    std::string sCategoryName;
    iCategoryId = std::stoi(msg[1]);
    iUserId = std::stoi(msg[2]);
    sCategoryName = msg[3];
    int iRtCode = IDataBase::ChangeCategoryName(iCategoryId, iUserId, sCategoryName);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        bytes = "NO_SUCH_CATEGORY";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        bytes = "INVALID_INPUT_DATA";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_AddNote(std::vector <std::string> &msg){
    std::string sKeyWords;
    iNoteId = std::stoi(msg[1]);
    iCategoryId = std::stoi(msg[2]);
    sKeyWords = msg[3];
    int iRtCode = IDataBase::AddNote(iCategoryId, sKeyWords, iNoteId);
    QJsonObject AddNote;
    switch(iRtCode){
    case SUCCESS:
        AddNote.insert("RequestType", "AddNote");
        AddNote.insert("SUCCESS", iNoteId);
        document.setObject(AddNote);
        bytes = document.toJson( QJsonDocument::Indented );
        CMyServer::m_socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        bytes = "INVALID_INPUT_DATA";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        bytes = "NO_SUCH_CATEGORY";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_GetNote(std::vector <std::string> &msg){
    std::vector<std::string> vsNote;
    int iRtCode = IDataBase::GetNote(iNoteId, iUserId, vsNote);
    QJsonObject GetNote;
    std::string gNote = "";
    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= vsNote.size(); i++){
             gNote += vsNote[i] + '|';
        }
        GetNote.insert("RequestType", "GetNote");
        GetNote.insert("SUCCESS", gNote.data());
        document.setObject(GetNote);
        bytes = document.toJson( QJsonDocument::Indented );
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        bytes = "NO_SUCH_NOTE";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_ChangeCategoryId(std::vector <std::string> &msg){
    iNoteId = std::stoi(msg[1]);
    iCategoryId = std::stoi(msg[2]);
    iUserId = std::stoi(msg[3]);
    int iRtCode = IDataBase::ChangeCategoryId(iNoteId, iCategoryId, iUserId);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        bytes = "NO_SUCH_USER";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        bytes = "NO_SUCH_NOTE";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        bytes = "NO_SUCH_CATEGORY";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_SetHeader(std::vector <std::string> &msg){
    std::string sHeader;
    iNoteId = std::stoi(msg[1]);
    sHeader = msg[2];
    int iRtCode = IDataBase::SetHeader(iNoteId, sHeader);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        bytes = "INVALID_INPUT_DATA";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        bytes = "NO_SUCH_NOTE";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_SetText(std::vector <std::string> &msg){
    std::string sText;
    iNoteId = std::stoi(msg[1]);
    sText = msg[2];
    int iRtCode = IDataBase::SetText(iNoteId, sText);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        bytes = "INVALID_INPUT_DATA";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        bytes = "NO_SUCH_NOTE";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_AddFriendAccess(std::vector <std::string> &msg){
    iNoteId = std::stoi(msg[1]);
    iFriendId = std::stoi(msg[2]);
    int iRtCode = IDataBase::AddFriendAccess(iNoteId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        bytes = "NO_SUCH_FRIEND";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        bytes = "NO_SUCH_NOTE";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_CheckFriendAccess(std::vector <std::string> &msg){
    iNoteId = std::stoi(msg[1]);
    iFriendId = std::stoi(msg[2]);
    int iRtCode = IDataBase::CheckFriendAccess(iNoteId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        bytes = "NO_SUCH_FRIEND";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        bytes = "NO_SUCH_NOTE";
        CMyServer::m_socketWrite(bytes);
        break;
    case ACCESS_DENIED:
        bytes = "ACCESS_DENIED";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_DeleteFriendAccess(std::vector <std::string> &msg){
    iNoteId = std::stoi(msg[1]);
    iFriendId = std::stoi(msg[2]);
    int iRtCode = IDataBase::DeleteFriendAccess(iNoteId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        bytes = "SUCCESS";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        bytes = "NO_SUCH_FRIEND";
        CMyServer::m_socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        bytes = "NO_SUCH_NOTE";
        CMyServer::m_socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        bytes = "UNEXPECTED_ERROR";
        CMyServer::m_socketWrite(bytes);
        break;
    }
}
void CMyServer::m_socketWrite(QByteArray &bytes){
    socket->write(bytes);
    socket->waitForBytesWritten(TIME);
}

void CMyServer::sockDisc(){
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
