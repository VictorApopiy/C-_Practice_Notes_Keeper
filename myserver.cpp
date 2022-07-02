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
            GetFriendList();
    }
    else if(msg.at(0)=="AddFriend"){
            AddFriend(msg);
    }
    else if(msg.at(0)=="DeleteFriend"){
            DeleteFriend(msg);
    }
    else if(msg.at(0)=="GetFriendRequestsList"){
            GetFriendRequestsList();
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
            GetCategory();
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
            GetNote();
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
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size()== 3){
        iRtCode = IDataBase::AddUser(msg.at(1), msg.at(2), iUserId);
    }
    QJsonObject AddUser;
    switch(iRtCode){
    case SUCCESS:
        AddUser.insert("ResponseType", "SUCCESS");
        AddUser.insert("Data", iUserId);
        document.setObject(AddUser);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        AddUser.insert("ResponseType", "INVALID_INPUT_DATA");
        document.setObject(AddUser);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        AddUser.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(AddUser);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::GetUserId(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size()== 3){
        iRtCode = IDataBase::GetUserId(msg.at(1), msg.at(2), iUserId);
    }
    QJsonObject GetUserId;
    switch(iRtCode){
    case SUCCESS:
        GetUserId.insert("ResponseType", "SUCCESS");
        GetUserId.insert("Data", iUserId);
        document.setObject(GetUserId);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        GetUserId.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(GetUserId);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        GetUserId.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(GetUserId);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::GetFriendList(){
    std::vector <std::string> FriendList;
    int iRtCode = IDataBase::GetFriendList(iId, FriendList);
    QJsonObject GetFriendList;
    std::string sList;

    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= FriendList.size(); i++){
             sList += FriendList[i] + '|';
        }
        GetFriendList.insert("ResponseType", "SUCCESS");
        GetFriendList.insert("Data", sList.data());
        document.setObject(GetFriendList);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        GetFriendList.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(GetFriendList);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        GetFriendList.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(GetFriendList);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::AddFriend(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iUserId = std::stoi(msg.at(1));
        iFriendId = std::stoi(msg.at(2));
        iRtCode = IDataBase::AddFriend(iUserId, iFriendId);
    }
    QJsonObject AddFriend;
    switch(iRtCode){
    case SUCCESS:
        AddFriend.insert("ResponseType", "SUCCESS");
        document.setObject(AddFriend);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        AddFriend.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(AddFriend);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        AddFriend.insert("ResponseType", "NO_SUCH_FRIEND");
        document.setObject(AddFriend);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        AddFriend.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(AddFriend);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::DeleteFriend(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iUserId = std::stoi(msg.at(1));
        iFriendId = std::stoi(msg.at(2));
        iRtCode = IDataBase::DeleteFriend(iUserId, iFriendId);
    }
    QJsonObject DeleteFriend;
    switch(iRtCode){
    case SUCCESS:
        DeleteFriend.insert("ResponseType", "SUCCESS");
        document.setObject(DeleteFriend);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        DeleteFriend.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(DeleteFriend);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        DeleteFriend.insert("ResponseType", "NO_SUCH_FRIEND");
        document.setObject(DeleteFriend);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        DeleteFriend.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(DeleteFriend);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::GetFriendRequestsList(){
    std::vector<std::string> vsFrReqList;
    int iRtCode = IDataBase::GetFriendRequestsList(iId, vsFrReqList);
    QJsonObject GetFriendRequestsList;
    std::string sRqList;
    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= vsFrReqList.size(); i++){
             sRqList += vsFrReqList[i] + '|';
        }
        GetFriendRequestsList.insert("ResponseType", "SUCCESS");
        GetFriendRequestsList.insert("Data", sRqList.data());
        document.setObject(GetFriendRequestsList);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        GetFriendRequestsList.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(GetFriendRequestsList);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        GetFriendRequestsList.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(GetFriendRequestsList);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::AddFriendRequest(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iUserId = std::stoi(msg.at(1));
        iFrReqId = std::stoi(msg.at(2));
        iRtCode = IDataBase::AddFriendRequest(iUserId, iFrReqId);
    }
    QJsonObject AddFriendRequest;
    switch(iRtCode){
    case SUCCESS:
        AddFriendRequest.insert("ResponseType", "SUCCESS");
        document.setObject(AddFriendRequest);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        AddFriendRequest.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(AddFriendRequest);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        AddFriendRequest.insert("ResponseType", "NO_SUCH_FRIEND");
        document.setObject(AddFriendRequest);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        AddFriendRequest.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(AddFriendRequest);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::DeleteFriendRequest(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iUserId = std::stoi(msg.at(1));
        iFrReqId = std::stoi(msg.at(2));
        iRtCode = IDataBase::DeleteFriendRequest(iUserId, iFrReqId);
    }
    QJsonObject DeleteFriendRequest;
    switch(iRtCode){
    case SUCCESS:
        DeleteFriendRequest.insert("ResponseType", "SUCCESS");
        document.setObject(DeleteFriendRequest);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        DeleteFriendRequest.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(DeleteFriendRequest);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_REQUEST:
        DeleteFriendRequest.insert("ResponseType", "NO_SUCH_REQUEST");
        document.setObject(DeleteFriendRequest);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        DeleteFriendRequest.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(DeleteFriendRequest);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::CreateCategory(const std::vector <std::string> &msg){
    std::string sCategoryName;
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 4){
        iCategoryId = std::stoi(msg.at(1));
        iUserId = std::stoi(msg.at(2));
        sCategoryName = msg.at(3);
        iRtCode = IDataBase::CreateCategory(iUserId, sCategoryName, iCategoryId);
    }
    QJsonObject CreateCategory;
    switch(iRtCode){
    case SUCCESS:
        CreateCategory.insert("ResponseType", "SUCCESS");
        CreateCategory.insert("Data", iCategoryId);
        document.setObject(CreateCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        CreateCategory.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(CreateCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        CreateCategory.insert("ResponseType", "INVALID_INPUT_DATA");
        document.setObject(CreateCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        CreateCategory.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(CreateCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::GetCategory(){
    std::vector<std::string> vsCategory;
    int iRtCode = IDataBase::GetCategory(iCategoryId, iUserId, vsCategory);
    QJsonObject GetCategory;
    std::string sGCategory;
    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= vsCategory.size(); i++){
             sGCategory += vsCategory[i] + '|';
        }
        GetCategory.insert("ResponseType", "SUCCESS");
        GetCategory.insert("Data", sGCategory.data());
        document.setObject(GetCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        GetCategory.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(GetCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        GetCategory.insert("ResponseType", "NO_SUCH_CATEGORY");
        document.setObject(GetCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        GetCategory.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(GetCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::DeleteCategory(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iCategoryId = std::stoi(msg.at(1));
        iUserId = std::stoi(msg.at(2));
        iRtCode = IDataBase::DeleteCategory(iCategoryId, iUserId);
    }
    QJsonObject DeleteCategory;
    switch(iRtCode){
    case SUCCESS:
        DeleteCategory.insert("ResponseType", "SUCCESS");
        document.setObject(DeleteCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        DeleteCategory.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(DeleteCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        DeleteCategory.insert("ResponseType", "NO_SUCH_CATEGORY");
        document.setObject(DeleteCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        DeleteCategory.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(DeleteCategory);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::ChangeCategoryName(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 4){
        std::string sCategoryName;
        iCategoryId = std::stoi(msg.at(1));
        iUserId = std::stoi(msg.at(2));
        sCategoryName = msg.at(3);
        iRtCode = IDataBase::ChangeCategoryName(iCategoryId, iUserId, sCategoryName);
    }
    QJsonObject ChangeCategoryName;
    switch(iRtCode){
    case SUCCESS:
        ChangeCategoryName.insert("ResponseType", "SUCCESS");
        document.setObject(ChangeCategoryName);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        ChangeCategoryName.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(ChangeCategoryName);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        ChangeCategoryName.insert("ResponseType", "NO_SUCH_CATEGORY");
        document.setObject(ChangeCategoryName);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        ChangeCategoryName.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(ChangeCategoryName);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        ChangeCategoryName.insert("ResponseType", "INVALID_INPUT_DATA");
        document.setObject(ChangeCategoryName);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::AddNote(const std::vector <std::string> &msg){
    std::string sKeyWords;
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 4){
        iNoteId = std::stoi(msg.at(1));
        iCategoryId = std::stoi(msg.at(2));
        sKeyWords = msg.at(3);
        iRtCode = IDataBase::AddNote(iCategoryId, sKeyWords, iNoteId);
    }
    QJsonObject AddNote;
    switch(iRtCode){
    case SUCCESS:
        AddNote.insert("ResponseType", "SUCCESS");
        AddNote.insert("Data", iNoteId);
        document.setObject(AddNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        AddNote.insert("ResponseType", "INVALID_INPUT_DATA");
        document.setObject(AddNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        AddNote.insert("ResponseType", "NO_SUCH_CATEGORY");
        document.setObject(AddNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        AddNote.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(AddNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::GetNote(){
    std::vector<std::string> vsNote;
    int iRtCode = IDataBase::GetNote(iNoteId, iUserId, vsNote);
    QJsonObject GetNote;
    std::string sGNote;
    switch(iRtCode){
    case SUCCESS:
        for(int i = 0; i <= vsNote.size(); i++){
             sGNote += vsNote[i] + '|';
        }
        GetNote.insert("ResponseType", "SUCCESS");
        GetNote.insert("Data", sGNote.data());
        document.setObject(GetNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        GetNote.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(GetNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        GetNote.insert("ResponseType", "NO_SUCH_NOTE");
        document.setObject(GetNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        GetNote.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(GetNote);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::ChangeCategoryId(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 4){
        iNoteId = std::stoi(msg.at(1));
        iCategoryId = std::stoi(msg.at(2));
        iUserId = std::stoi(msg.at(3));
        iRtCode = IDataBase::ChangeCategoryId(iNoteId, iCategoryId, iUserId);
    }
    QJsonObject ChangeCategoryId;
    switch(iRtCode){
    case SUCCESS:
        ChangeCategoryId.insert("ResponseType", "SUCCESS");
        document.setObject(ChangeCategoryId);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_USER:
        ChangeCategoryId.insert("ResponseType", "NO_SUCH_USER");
        document.setObject(ChangeCategoryId);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        ChangeCategoryId.insert("ResponseType", "NO_SUCH_NOTE");
        document.setObject(ChangeCategoryId);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_CATEGORY:
        ChangeCategoryId.insert("ResponseType", "NO_SUCH_CATEGORY");
        document.setObject(ChangeCategoryId);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        ChangeCategoryId.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(ChangeCategoryId);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::SetHeader(const std::vector <std::string> &msg){
    std::string sHeader;
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iNoteId = std::stoi(msg.at(1));
        sHeader = msg.at(2);
        iRtCode = IDataBase::SetHeader(iNoteId, sHeader);
    }
    QJsonObject SetHeader;
    switch(iRtCode){
    case SUCCESS:
        SetHeader.insert("ResponseType", "SUCCESS");
        document.setObject(SetHeader);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        SetHeader.insert("ResponseType", "INVALID_INPUT_DATA");
        document.setObject(SetHeader);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        SetHeader.insert("ResponseType", "NO_SUCH_NOTE");
        document.setObject(SetHeader);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        SetHeader.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(SetHeader);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::SetText(const std::vector <std::string> &msg){
    std::string sText;
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iNoteId = std::stoi(msg.at(1));
        sText = msg.at(2);
        iRtCode = IDataBase::SetText(iNoteId, sText);
    }
    QJsonObject SetText;
    switch(iRtCode){
    case SUCCESS:
        SetText.insert("ResponseType", "SUCCESS");
        document.setObject(SetText);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case INVALID_INPUT_DATA:
        SetText.insert("ResponseType", "INVALID_INPUT_DATA");
        document.setObject(SetText);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        SetText.insert("ResponseType", "NO_SUCH_NOTE");
        document.setObject(SetText);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        SetText.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(SetText);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::AddFriendAccess(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iNoteId = std::stoi(msg.at(1));
        iFriendId = std::stoi(msg.at(2));
        iRtCode = IDataBase::AddFriendAccess(iNoteId, iFriendId);
    }
    QJsonObject AddFriendAccess;
    switch(iRtCode){
    case SUCCESS:
        AddFriendAccess.insert("ResponseType", "SUCCESS");
        document.setObject(AddFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        AddFriendAccess.insert("ResponseType", "NO_SUCH_FRIEND");
        document.setObject(AddFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        AddFriendAccess.insert("ResponseType", "NO_SUCH_NOTE");
        document.setObject(AddFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        AddFriendAccess.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(AddFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::CheckFriendAccess(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iNoteId = std::stoi(msg.at(1));
        iFriendId = std::stoi(msg.at(2));
        iRtCode = IDataBase::CheckFriendAccess(iNoteId, iFriendId);
    }
    QJsonObject CheckFriendAccess;
    switch(iRtCode){
    case SUCCESS:
        CheckFriendAccess.insert("ResponseType", "SUCCESS");
        document.setObject(CheckFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        CheckFriendAccess.insert("ResponseType", "NO_SUCH_FRIEND");
        document.setObject(CheckFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        CheckFriendAccess.insert("ResponseType", "NO_SUCH_NOTE");
        document.setObject(CheckFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case ACCESS_DENIED:
        CheckFriendAccess.insert("ResponseType", "ACCESS_DENIED");
        document.setObject(CheckFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        CheckFriendAccess.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(CheckFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    }
}
void CMyServer::DeleteFriendAccess(const std::vector <std::string> &msg){
    int iRtCode = INVALID_INPUT_DATA;
    if(msg.size() == 3){
        iNoteId = std::stoi(msg.at(1));
        iFriendId = std::stoi(msg.at(2));
        iRtCode = IDataBase::DeleteFriendAccess(iNoteId, iFriendId);
    }
    QJsonObject DeleteFriendAccess;
    switch(iRtCode){
    case SUCCESS:
        DeleteFriendAccess.insert("ResponseType", "SUCCESS");
        document.setObject(DeleteFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_FRIEND:
        DeleteFriendAccess.insert("ResponseType", "NO_SUCH_FRIEND");
        document.setObject(DeleteFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case NO_SUCH_NOTE:
        DeleteFriendAccess.insert("ResponseType", "NO_SUCH_NOTE");
        document.setObject(DeleteFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
        break;
    case UNEXPECTED_ERROR:
        DeleteFriendAccess.insert("ResponseType", "UNEXPECTED_ERROR");
        document.setObject(DeleteFriendAccess);
        bytes = document.toJson( QJsonDocument::Indented );
        socketWrite(bytes);
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
