#include "myserver.h"
#include "IDataBase.cpp"
#include "IDataBase.h"
#include "DBErrors.h"

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
    parseJson(Data);
}
void CMyServer::parseJson(QByteArray &Data){
    std::vector <std::string> msg;

    nlohmann::json j;
    j = nlohmann::json::parse(QString(Data).toStdString());

    for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            msg.push_back(it.value());
    }
    if(msg.at(0)=="AddUser"){
            AddUser(msg);
    }
    else if(msg.at(0)=="GetUserId"){
            GetUserId(msg);
    }
    else if(msg.at(0)=="GetFriendList"){
            GetFriendList(msg);
    }
    else if(msg.at(0)=="AddFriend"){
            AddFriend(msg);
    }
    else if(msg.at(0)=="DeleteFriend"){
            DeleteFriend(msg);
    }
    else if(msg.at(0)=="GetFriendRequestsList"){
            GetFriendRequestsList(msg);
    }
    else if(msg.at(0)=="AddFriendRequest"){
            AddFriendRequest(msg);
    }
    else if(msg.at(0)=="DeleteFriendRequest"){
            DeleteFriendRequest(msg);
    }
    else if(msg.at(0)=="CreateCategory"){
            CreateCategory(msg);
    }
    else if(msg.at(0)=="GetCategory"){
            GetCategory(msg);
    }
    else if(msg.at(0)=="DeleteCategory"){
            DeleteCategory(msg);
    }
    else if(msg.at(0)=="ChangeCategoryName"){
            ChangeCategoryName(msg);
    }
    else if(msg.at(0)=="AddNote"){
            AddNote(msg);
    }
    else if(msg.at(0)=="GetNote"){
            GetNote(msg);
    }
    else if(msg.at(0)=="ChangeCategoryId"){
            ChangeCategoryId(msg);
    }
    else if(msg.at(0)=="SetHeader"){
            SetHeader(msg);
    }
    else if(msg.at(0)=="SetText"){
            SetText(msg);
    }
    else if(msg.at(0)=="AddFriendAccess"){
            AddFriendAccess(msg);
    }
    else if(msg.at(0)=="CheckFriendAccess"){
            CheckFriendAccess(msg);
    }
    else if(msg.at(0)=="DeleteFriendAccess"){
            DeleteFriendAccess(msg);
    }
    else{
            socketWrite("Unclear command");
    }
}
void CMyServer::AddUser(const std::vector <std::string> &msg){
    int iRtCode = IDataBase::AddUser(msg.at(1), msg.at(2), iUserId);
    QJsonObject AddUser;
    switch(iRtCode){
    case SUCCESS:
        AddUser.insert("RequestType", "AddUser");
        AddUser.insert("SUCCESS", iUserId);
        document.setObject(AddUser);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        socketWrite("INVALID_INPUT_DATA");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::GetUserId(const std::vector <std::string> &msg){
    int iRtCode = IDataBase::GetUserId(msg.at(1), msg.at(2), iUserId);
    QJsonObject GetUserId;
    switch(iRtCode){
    case SUCCESS:
        GetUserId.insert("RequestType", "GetUserId");
        GetUserId.insert("SUCCESS", iUserId);
        document.setObject(GetUserId);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::GetFriendList(const std::vector <std::string> &msg){
    std::vector <std::string> FriendList;
    int iRtCode = IDataBase::GetFriendList(iId, FriendList);
    QJsonObject GetFriendList;
    std::string sList;

    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= FriendList.size(); i++){
             sList += FriendList[i] + '|';
        }
        GetFriendList.insert("RequestType", "GetFriendList");
        GetFriendList.insert("SUCCESS", sList.data());
        document.setObject(GetFriendList);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::AddFriend(const std::vector <std::string> &msg){
    iUserId = std::stoi(msg.at(1));
    iFriendId = std::stoi(msg.at(2));
    int iRtCode = IDataBase::AddFriend(iUserId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case NO_SUCH_FRIEND:
        socketWrite("NO_SUCH_FRIEND");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::DeleteFriend(const std::vector <std::string> &msg){
    iUserId = std::stoi(msg.at(1));
    iFriendId = std::stoi(msg.at(2));
    int iRtCode = IDataBase::DeleteFriend(iUserId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case NO_SUCH_FRIEND:
        socketWrite("NO_SUCH_FRIEND");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::GetFriendRequestsList(const std::vector <std::string> &msg){
    std::vector<std::string> vsFrReqList;
    int iRtCode = IDataBase::GetFriendRequestsList(iId, vsFrReqList);
    QJsonObject GetFriendRequestsList;
    std::string sRqList;
    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= vsFrReqList.size(); i++){
             sRqList += vsFrReqList[i] + '|';
        }
        GetFriendRequestsList.insert("RequestType", "GetFriendRequestsList");
        GetFriendRequestsList.insert("SUCCESS", sRqList.data());
        document.setObject(GetFriendRequestsList);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::AddFriendRequest(const std::vector <std::string> &msg){
    iUserId = std::stoi(msg.at(1));
    iFrReqId = std::stoi(msg.at(2));
    int iRtCode = IDataBase::AddFriendRequest(iUserId, iFrReqId);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case NO_SUCH_FRIEND:
        socketWrite("NO_SUCH_FRIEND");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::DeleteFriendRequest(const std::vector <std::string> &msg){
    iUserId = std::stoi(msg.at(1));
    iFrReqId = std::stoi(msg.at(2));
    int iRtCode = IDataBase::DeleteFriendRequest(iUserId, iFrReqId);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case NO_SUCH_REQUEST:
        socketWrite("NO_SUCH_REQUEST");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::CreateCategory(const std::vector <std::string> &msg){
    std::string sCategoryName;
    iCategoryId = std::stoi(msg.at(1));
    iUserId = std::stoi(msg.at(2));
    sCategoryName = msg.at(3);
    int iRtCode = IDataBase::CreateCategory(iUserId, sCategoryName, iCategoryId);
    QJsonObject CreateCategory;
    switch(iRtCode){
    case SUCCESS:
        CreateCategory.insert("RequestType", "CreateCategory");
        CreateCategory.insert("SUCCESS", iCategoryId);
        document.setObject(CreateCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case INVALID_INPUT_DATA:
        socketWrite("INVALID_INPUT_DATA");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::GetCategory(const std::vector <std::string> &msg){
    std::vector<std::string> vsCategory;
    int iRtCode = IDataBase::GetCategory(iCategoryId, iUserId, vsCategory);
    QJsonObject GetCategory;
    std::string sGCategory;
    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= vsCategory.size(); i++){
             sGCategory += vsCategory[i] + '|';
        }
        GetCategory.insert("RequestType", "GetCategory");
        GetCategory.insert("SUCCESS", sGCategory.data());
        document.setObject(GetCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case NO_SUCH_CATEGORY:
        socketWrite("NO_SUCH_CATEGORY");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::DeleteCategory(const std::vector <std::string> &msg){
    iCategoryId = std::stoi(msg.at(1));
    iUserId = std::stoi(msg.at(2));
    int iRtCode = IDataBase::DeleteCategory(iCategoryId, iUserId);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case NO_SUCH_CATEGORY:
        socketWrite("NO_SUCH_CATEGORY");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::ChangeCategoryName(const std::vector <std::string> &msg){
    std::string sCategoryName;
    iCategoryId = std::stoi(msg.at(1));
    iUserId = std::stoi(msg.at(2));
    sCategoryName = msg.at(3);
    int iRtCode = IDataBase::ChangeCategoryName(iCategoryId, iUserId, sCategoryName);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case NO_SUCH_CATEGORY:
        socketWrite("NO_SUCH_CATEGORY");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    case INVALID_INPUT_DATA:
        socketWrite("INVALID_INPUT_DATA");
        break;
    }
}
void CMyServer::AddNote(const std::vector <std::string> &msg){
    std::string sKeyWords;
    iNoteId = std::stoi(msg.at(1));
    iCategoryId = std::stoi(msg.at(2));
    sKeyWords = msg.at(3);
    int iRtCode = IDataBase::AddNote(iCategoryId, sKeyWords, iNoteId);
    QJsonObject AddNote;
    switch(iRtCode){
    case SUCCESS:
        AddNote.insert("RequestType", "AddNote");
        AddNote.insert("SUCCESS", iNoteId);
        document.setObject(AddNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        socketWrite("INVALID_INPUT_DATA");
        break;
    case NO_SUCH_CATEGORY:
        socketWrite("NO_SUCH_CATEGORY");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::GetNote(const std::vector <std::string> &msg){
    std::vector<std::string> vsNote;
    int iRtCode = IDataBase::GetNote(iNoteId, iUserId, vsNote);
    QJsonObject GetNote;
    std::string sGNote;
    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= vsNote.size(); i++){
             sGNote += vsNote[i] + '|';
        }
        GetNote.insert("RequestType", "GetNote");
        GetNote.insert("SUCCESS", sGNote.data());
        document.setObject(GetNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case NO_SUCH_NOTE:
        socketWrite("NO_SUCH_NOTE");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::ChangeCategoryId(const std::vector <std::string> &msg){
    iNoteId = std::stoi(msg.at(1));
    iCategoryId = std::stoi(msg.at(2));
    iUserId = std::stoi(msg.at(3));
    int iRtCode = IDataBase::ChangeCategoryId(iNoteId, iCategoryId, iUserId);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_USER:
        socketWrite("NO_SUCH_USER");
        break;
    case NO_SUCH_NOTE:
        socketWrite("NO_SUCH_NOTE");
        break;
    case NO_SUCH_CATEGORY:
        socketWrite("NO_SUCH_CATEGORY");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::SetHeader(const std::vector <std::string> &msg){
    std::string sHeader;
    iNoteId = std::stoi(msg.at(1));
    sHeader = msg.at(2);
    int iRtCode = IDataBase::SetHeader(iNoteId, sHeader);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case INVALID_INPUT_DATA:
        socketWrite("INVALID_INPUT_DATA");
        break;
    case NO_SUCH_NOTE:
        socketWrite("NO_SUCH_NOTE");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::SetText(const std::vector <std::string> &msg){
    std::string sText;
    iNoteId = std::stoi(msg.at(1));
    sText = msg.at(2);
    int iRtCode = IDataBase::SetText(iNoteId, sText);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case INVALID_INPUT_DATA:
        socketWrite("INVALID_INPUT_DATA");
        break;
    case NO_SUCH_NOTE:
        socketWrite("NO_SUCH_NOTE");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::AddFriendAccess(const std::vector <std::string> &msg){
    iNoteId = std::stoi(msg.at(1));
    iFriendId = std::stoi(msg.at(2));
    int iRtCode = IDataBase::AddFriendAccess(iNoteId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_FRIEND:
        socketWrite("NO_SUCH_FRIEND");
        break;
    case NO_SUCH_NOTE:
        socketWrite("NO_SUCH_NOTE");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::CheckFriendAccess(const std::vector <std::string> &msg){
    iNoteId = std::stoi(msg.at(1));
    iFriendId = std::stoi(msg.at(2));
    int iRtCode = IDataBase::CheckFriendAccess(iNoteId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_FRIEND:
        socketWrite("NO_SUCH_FRIEND");
        break;
    case NO_SUCH_NOTE:
        socketWrite("NO_SUCH_NOTE");
        break;
    case ACCESS_DENIED:
        socketWrite("ACCESS_DENIED");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::DeleteFriendAccess(const std::vector <std::string> &msg){
    iNoteId = std::stoi(msg.at(1));
    iFriendId = std::stoi(msg.at(2));
    int iRtCode = IDataBase::DeleteFriendAccess(iNoteId, iFriendId);
    switch(iRtCode){
    case SUCCESS:
        socketWrite("SUCCESS");
        break;
    case NO_SUCH_FRIEND:
        socketWrite("NO_SUCH_FRIEND");
        break;
    case NO_SUCH_NOTE:
        socketWrite("NO_SUCH_NOTE");
        break;
    case UNEXPECTED_ERROR:
        socketWrite("UNEXPECTED_ERROR");
        break;
    }
}
void CMyServer::socketWrite(const QByteArray &bytes){
    socket->write(bytes);
    socket->waitForBytesWritten(TIME);
}

void CMyServer::sockDisc(){
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
