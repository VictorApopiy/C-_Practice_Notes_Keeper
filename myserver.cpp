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
    Data = socket->readAll();
    qDebug()<<"Data: "<<Data;
    std::vector <std::string> msg;

    nlohmann::json j;
    j = nlohmann::json::parse(QString(Data).toStdString());

    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            msg.push_back(it.value());
    }
    QJsonDocument document;
    QByteArray bytes;

        if(msg[0]=="AddUser"){
            int iUserId;
            int iRtCode = IDataBase::AddUser(msg[1], msg[2], iUserId);
            QJsonObject AddUser;
            switch(iRtCode){
            case SUCCESS:
                AddUser.insert("RequestType", "AddUser");
                AddUser.insert("SUCCESS", iUserId);
                document.setObject(AddUser);
                bytes = document.toJson( QJsonDocument::Indented );
                socket->write(bytes);
                socket->waitForBytesWritten(500);
                break;
            case INVALID_INPUT_DATA:
                res = "INVALID_INPUT_DATA";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="GetUserId"){
            int iUserId;
            int iRtCode = IDataBase::GetUserId(msg[1], msg[2], iUserId);
            QJsonObject GetUserId;
            switch(iRtCode){
            case SUCCESS:
                GetUserId.insert("RequestType", "GetUserId");
                GetUserId.insert("SUCCESS", iUserId);
                document.setObject(GetUserId);
                bytes = document.toJson( QJsonDocument::Indented );
                socket->write(bytes);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="GetFriendList"){
            int iId;
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
                socket->write(bytes);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }

        }
        else if(msg[0]=="AddFriend"){
            int iUserId;
            int iFriendId;
            iUserId = std::stoi(msg[1]);
            iFriendId = std::stoi(msg[2]);
            int iRtCode = IDataBase::AddFriend(iUserId, iFriendId);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_FRIEND:
                res = "NO_SUCH_FRIEND";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="DeleteFriend"){
            int iUserId;
            int iFriendId;
            iUserId = std::stoi(msg[1]);
            iFriendId = std::stoi(msg[2]);
            int iRtCode = IDataBase::DeleteFriend(iUserId, iFriendId);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_FRIEND:
                res = "NO_SUCH_FRIEND";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="GetFriendRequestsList"){
            int iId;
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
                socket->write(bytes);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="AddFriendRequest"){
            int iUserId;
            int iFrReqId;
            iUserId = std::stoi(msg[1]);
            iFrReqId = std::stoi(msg[2]);
            int iRtCode = IDataBase::AddFriendRequest(iUserId, iFrReqId);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_FRIEND:
                res = "NO_SUCH_FRIEND";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="DeleteFriendRequest"){
            int iUserId;
            int iFrReqId;
            iUserId = std::stoi(msg[1]);
            iFrReqId = std::stoi(msg[2]);
            int iRtCode = IDataBase::DeleteFriendRequest(iUserId, iFrReqId);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_REQUEST:
                res = "NO_SUCH_REQUEST";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="CreateCategory"){
            int iCategoryId;
            int iUserId;
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
                socket->write(bytes);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case INVALID_INPUT_DATA:
                res = "INVALID_INPUT_DATA";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="GetCategory"){
            int iCategoryId;
            int iUserId;
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
                socket->write(bytes);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_CATEGORY:
                res = "NO_SUCH_CATEGORY";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }

        }
        else if(msg[0]=="DeleteCategory"){
            int iCategoryId;
            int iUserId;
            iCategoryId = std::stoi(msg[1]);
            iUserId = std::stoi(msg[2]);
            int iRtCode = IDataBase::DeleteCategory(iCategoryId, iUserId);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_CATEGORY:
                res = "NO_SUCH_CATEGORY";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="ChangeCategoryName"){
            int iCategoryId;
            int iUserId;
            std::string sCategoryName;
            iCategoryId = std::stoi(msg[1]);
            iUserId = std::stoi(msg[2]);
            sCategoryName = msg[3];
            int iRtCode = IDataBase::ChangeCategoryName(iCategoryId, iUserId, sCategoryName);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_CATEGORY:
                res = "NO_SUCH_CATEGORY";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case INVALID_INPUT_DATA:
                res = "INVALID_INPUT_DATA";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="AddNote"){
            int iNoteId;
            int iCategoryId;
            std::string sKeyWords;
            iNoteId = std::stoi(msg[1]);
            iCategoryId = std::stoi(msg[2]);
            sKeyWords = msg[3];
            int iRtCode = IDataBase::AddNote(iCategoryId, sKeyWords, iNoteId);
            QJsonObject AddNote;
            switch(iRtCode){
            case SUCCESS:
                AddNote.insert("RequestType", "AddNote");
                AddNote.insert("SUCCESS", iCategoryId);
                document.setObject(AddNote);
                bytes = document.toJson( QJsonDocument::Indented );
                socket->write(bytes);
                socket->waitForBytesWritten(500);
                break;
            case INVALID_INPUT_DATA:
                res = "INVALID_INPUT_DATA";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_CATEGORY:
                res = "NO_SUCH_CATEGORY";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="GetNote"){
            int NoteId;
            int iUserId;
            std::vector<std::string> vsNote;
            int iRtCode = IDataBase::GetNote(NoteId, iUserId, vsNote);
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
                socket->write(bytes);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_NOTE:
                res = "NO_SUCH_NOTE";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }

        }
        else if(msg[0]=="ChangeCategoryId"){
            int iNoteId;
            int iCategoryId;
            int iUserId;
            iNoteId = std::stoi(msg[1]);
            iCategoryId = std::stoi(msg[2]);
            iUserId = std::stoi(msg[3]);
            int iRtCode = IDataBase::ChangeCategoryId(iNoteId, iCategoryId, iUserId);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_USER:
                res = "NO_SUCH_USER";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_NOTE:
                res = "NO_SUCH_NOTE";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_CATEGORY:
                res = "NO_SUCH_CATEGORY";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="SetHeader"){
            int iNoteId;
            std::string sHeader;
            iNoteId = std::stoi(msg[1]);
            sHeader = msg[2];
            int iRtCode = IDataBase::SetHeader(iNoteId, sHeader);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case INVALID_INPUT_DATA:
                res = "INVALID_INPUT_DATA";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_NOTE:
                res = "NO_SUCH_NOTE";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="SetText"){
            int iNoteId;
            std::string sText;
            iNoteId = std::stoi(msg[1]);
            sText = msg[2];
            int iRtCode = IDataBase::SetText(iNoteId, sText);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case INVALID_INPUT_DATA:
                res = "INVALID_INPUT_DATA";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_NOTE:
                res = "NO_SUCH_NOTE";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="AddFriendAccess"){
            int iNoteId;
            int iFriendId;
            iNoteId = std::stoi(msg[1]);
            iFriendId = std::stoi(msg[2]);
            int iRtCode = IDataBase::AddFriendAccess(iNoteId, iFriendId);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_FRIEND:
                res = "NO_SUCH_FRIEND";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_NOTE:
                res = "NO_SUCH_NOTE";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="CheckFriendAccess"){
            int iNoteId;
            int iFriendId;
            iNoteId = std::stoi(msg[1]);
            iFriendId = std::stoi(msg[2]);
            int iRtCode = IDataBase::CheckFriendAccess(iNoteId, iFriendId);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_FRIEND:
                res = "NO_SUCH_FRIEND";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_NOTE:
                res = "NO_SUCH_NOTE";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case ACCESS_DENIED:
                res = "ACCESS_DENIED";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else if(msg[0]=="DeleteFriendAccess"){
            int iNoteId;
            int iFriendId;
            iNoteId = std::stoi(msg[1]);
            iFriendId = std::stoi(msg[2]);
            int iRtCode = IDataBase::DeleteFriendAccess(iNoteId, iFriendId);
            switch(iRtCode){
            case SUCCESS:
                res = "SUCCESS";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_FRIEND:
                res = "NO_SUCH_FRIEND";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case NO_SUCH_NOTE:
                res = "NO_SUCH_NOTE";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            case UNEXPECTED_ERROR:
                res = "UNEXPECTED_ERROR";
                socket->write(res);
                socket->waitForBytesWritten(500);
                break;
            }
        }
        else{
            //Незрозуміла команда від клієнта
            res = "Unclear command";
            socket->write(res);
            socket->waitForBytesWritten(500);
         }

}

void myserver::sockDisc(){
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
