#include "IDataBase.h"
#include "DBErrors.h"
#include <string>
static sqlite3_stmt* pSqliteStmt;

const int IDataBase::SendRequestToDB(std::string sQuerry) {
  sqlite3* pSqliteDatabase;
  sqlite3_open("NotesKeeper.db", &pSqliteDatabase);
  int iReturnCode = sqlite3_prepare_v2(pSqliteDatabase, sQuerry.c_str(), -1, &pSqliteStmt, 0);
  if (iReturnCode != SQLITE_OK) {
    return  iReturnCode;
  }
  else
  {
    return SUCCESS;
  }
}

const int IDataBase::AddUser(const std::string &sLogin,
                             const std::string &sPassword, int& iUserId)
{
    try {
        for (int i = 0; i < sLogin.size() || i < sPassword.size(); i++) {
            if (!(i > sLogin.size()))
                if (sLogin[i] == '\'')
                    return INVALID_INPUT_DATA;
            if (!(i > sPassword.size()))
                if (sPassword[i] == '\'')
                    return INVALID_INPUT_DATA;
        }

        std::string sQuerry = "INSERT INTO user(login, password) VALUES (\'" + sLogin + "\', \'" + sPassword + "\');";
        SendRequestToDB(sQuerry);
        sQuerry = "SELECT userId from user where login = \'" + sLogin + "\' and password = \'" + sPassword + "\';";
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iUserId = sqlite3_column_int(pSqliteStmt, 0);
        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::GetUserId(const std::string &sLogin,
                               const std::string &sPassword, int& iUserId)
{
    try {
        for (int i = 0; i < sLogin.size() || i < sPassword.size(); i++) {
            if (!(i > sLogin.size()))
                if (sLogin[i] == '\'')
                    return INVALID_INPUT_DATA;
            if (!(i > sPassword.size()))
                if (sPassword[i] == '\'')
                    return INVALID_INPUT_DATA;
        }
        std::string sQuerry = "SELECT userId from user where login = \'" + sLogin + "\' and password = \'" + sPassword + "\'";
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iUserId = sqlite3_column_int(pSqliteStmt, 0);
        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::GetFriendList(const int iUserId,
                                   std::vector <std::string> &FriendList)
{
    try {
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;

        sQuerry = "SELECT friendList from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        const unsigned char* pucFriendList = sqlite3_column_text(pSqliteStmt, 0);

        std::string sFriendList;
        sFriendList.append(reinterpret_cast<const char*>(pucFriendList));
        char* pcFriendList = new char[sFriendList.length() + 1];
        strcpy(pcFriendList, sFriendList.c_str());
        char* pcToFriendListVector;
        while (pcToFriendListVector != NULL)
        {
            pcToFriendListVector = strtok(pcFriendList, "|");
            FriendList.push_back(pcToFriendListVector);
        }

        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::AddFriend(const int iUserId, const int iFriendId)
{
    try {
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;
        sQuerry = "SELECT userId from user where userId = " + std::to_string(iFriendId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iFriendId)
            return NO_SUCH_FRIEND;

        sQuerry = "SELECT friendList from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        const unsigned char* pucFriendList = sqlite3_column_text(pSqliteStmt, 0);

        std::string sFriendList;
        sFriendList.append(reinterpret_cast<const char*>(pucFriendList));
        sFriendList += std::to_string(iFriendId) + '|';

        sQuerry = "UPDATE user SET friendList = \'" + sFriendList + "\' where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);

        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::DeleteFriend(const int iUserId, const int iFriendId)
{
    try {
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;
        sQuerry = "SELECT userId from user where userId = " + std::to_string(iFriendId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iFriendId)
            return NO_SUCH_FRIEND;

        sQuerry = "SELECT friendList from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        const unsigned char* pucFriendList = sqlite3_column_text(pSqliteStmt, 0);

        std::string sFriendList;
        sFriendList.append(reinterpret_cast<const char*>(pucFriendList));
        char* pcFriendList = new char[sFriendList.length() + 1];
        strcpy(pcFriendList, sFriendList.c_str());
        char* pcToFriendList;
        char* pcBuffer;
        std::string sFriendListToDB;
        while (pcToFriendList != NULL)
        {
            pcToFriendList = strtok(pcFriendList, "|");
            strcpy(pcBuffer, pcToFriendList);
            if (pcBuffer != std::to_string(iFriendId)) {
                sFriendListToDB += pcBuffer;
                sFriendListToDB[sizeof(sFriendListToDB) / sizeof(char) - 1] = '|';
            }
        }

        sQuerry = "UPDATE user SET friendList = \'" + sFriendListToDB + "\' where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);

        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::GetFriendRequestsList(const int iUserId,
                                           std::vector<std::string> &vsFrReqList)
{
    try {
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;

        sQuerry = "SELECT friendRequestList from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        const unsigned char* pucFriendList = sqlite3_column_text(pSqliteStmt, 0);

        std::string sFriendList;
        sFriendList.append(reinterpret_cast<const char*>(pucFriendList));
        char* pcFriendList = new char[sFriendList.length() + 1];
        strcpy(pcFriendList, sFriendList.c_str());
        char* pcToFriendListVector;
        while (pcToFriendListVector != NULL)
        {
            pcToFriendListVector = strtok(pcFriendList, "|");
            vsFrReqList.push_back(pcToFriendListVector);
        }

        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::AddFriendRequest(const int iUserId, const int iFrReqId)
{
    try {
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;
        sQuerry = "SELECT userId from user where userId = " + std::to_string(iFrReqId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iFrReqId)
            return NO_SUCH_REQUEST;

        sQuerry = "SELECT friendRequestList from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        const unsigned char* pucFriendRequestList = sqlite3_column_text(pSqliteStmt, 0);

        std::string sFriendList;
        sFriendList.append(reinterpret_cast<const char*>(pucFriendRequestList));
        sFriendList += std::to_string(iFrReqId) + '|';

        sQuerry = "UPDATE user SET friendRequestList = \'" + sFriendList + "\' where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);

        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::DeleteFriendRequest(const int iUserId, const int iFrReqId)
{
    try {
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;
        sQuerry = "SELECT userId from user where userId = " + std::to_string(iFrReqId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iFrReqId)
            return NO_SUCH_REQUEST;

        sQuerry = "SELECT friendRequestList from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        const unsigned char* pucFriendRequestList = sqlite3_column_text(pSqliteStmt, 0);

        std::string sFriendRequestList;
        sFriendRequestList.append(reinterpret_cast<const char*>(pucFriendRequestList));
        char* pcFriendRequestList = new char[sFriendRequestList.length() + 1];
        strcpy(pcFriendRequestList, sFriendRequestList.c_str());
        char* pcToFriendRequestList;
        char* pcBuffer;
        std::string sFriendRequestListToDB;
        while (pcToFriendRequestList != NULL)
        {
            pcToFriendRequestList = strtok(pcFriendRequestList, "|");
            strcpy(pcBuffer, pcToFriendRequestList);
            if (pcBuffer != std::to_string(iFrReqId)) {
                sFriendRequestListToDB += pcBuffer;
                sFriendRequestListToDB[sizeof(sFriendRequestListToDB) / sizeof(char) - 1] = '|';
            }
        }

        sQuerry = "UPDATE user SET friendRequestList = \'" + sFriendRequestListToDB + "\' where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);

        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::CreateCategory(const int iUserId,
                                    const std::string &sCategoryName, int& iCategoryId)
{
    try {
        for (int i = 0; i < sCategoryName.size(); i++) {
            if (sCategoryName[i] == '\'')
                    return INVALID_INPUT_DATA;
        }
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;

        sQuerry = "INSERT INTO category value (" + std::to_string(iUserId) + ", \'" + sCategoryName + "\')";
        SendRequestToDB(sQuerry);
        sQuerry = "SELECT categoryId from category where categoryName = \'" + sCategoryName + "\'";
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iCategoryId = sqlite3_column_int(pSqliteStmt, 0);
        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::GetCategory(const int iCategoryId,
                                 const int iUserId,
                                 std::vector<std::string> &vsCategory)
{
    try {
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;

        sQuerry = "SELECT categoryId from category where userId = " + std::to_string(iCategoryId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iCategoryId)
            return NO_SUCH_CATEGORY;

        sQuerry = "SELECT * from category where categoryId = " + std::to_string(iCategoryId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        if (sqlite3_column_int(pSqliteStmt, 1) == iUserId) {
            vsCategory.push_back(std::to_string(sqlite3_column_int(pSqliteStmt, 0)));
            vsCategory.push_back(std::to_string(sqlite3_column_int(pSqliteStmt, 1)));
            const unsigned char* pucBuffer = sqlite3_column_text(pSqliteStmt, 2);
            std::string sBuffer;
            sBuffer.append(reinterpret_cast<const char*>(pucBuffer));
            vsCategory.push_back(sBuffer);
            return SUCCESS;
        }
        else
            return NO_SUCH_CATEGORY;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::DeleteCategory(const int iCategoryId, const int iUserId)
{
    try {
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;

        sQuerry = "SELECT categoryId from category where userId = " + std::to_string(iCategoryId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iCategoryId)
            return NO_SUCH_CATEGORY;

        sQuerry = "DELETE FROM category where categoryId = " + std::to_string(iCategoryId);
        SendRequestToDB(sQuerry);
        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::ChangeCategoryName(const int    iCategoryId,
                                        const int    iUserId,
                                        const std::string &sCategoryName)
{
    try {
        for (int i = 0; i < sCategoryName.size(); i++) {
            if (sCategoryName[i] == '\'')
                return INVALID_INPUT_DATA;
        }
        std::string sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return NO_SUCH_USER;

        sQuerry = "SELECT categoryId from category where userId = " + std::to_string(iCategoryId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iCategoryId)
            return NO_SUCH_CATEGORY;

        sQuerry = "UPDATE category set categoryName = \'"+ sCategoryName +"\' where categoryId = " + std::to_string(iCategoryId);
        SendRequestToDB(sQuerry);
        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::AddNote(int iCategoryId, const std::string &sKeyWords, int& iNoteId)
{
    try {
        std::string sQuerry = "SELECT categoryId from category where userId = " + std::to_string(iCategoryId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iCategoryId)
            return NO_SUCH_CATEGORY;
        for (int i = 0; i < sKeyWords.size(); i++) {
            if (sKeyWords[i] == '\'')
                return INVALID_INPUT_DATA;
        }

        sQuerry = "INSERT INTO note(categoryId, keyWords) value ("+ std::to_string(iCategoryId) +", \'" + sKeyWords + "\')";
        SendRequestToDB(sQuerry);
        sQuerry = "SELECT noteId from note where keyWords = \'" + sKeyWords + "\'";
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iNoteId = sqlite3_column_int(pSqliteStmt, 0);
        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::GetNote(const int iNoteId,
                             const int iUserId,
                             std::vector<std::string> &vsNote)
{
    try {
        std::string sQuerry = "SELECT noteId from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iNoteId)
            return NO_SUCH_NOTE;
        sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iNoteId)
            return NO_SUCH_USER;
        sQuerry = "SELECT userId from category where categoryId = ";
        sQuerry       +=	  "(SELECT categoryId from note where noteId = " + std::to_string(iNoteId)+")";
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return UNEXPECTED_ERROR;

        sQuerry = "SELECT * from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        if (sqlite3_column_int(pSqliteStmt, 1) == iUserId){
            vsNote.push_back(std::to_string(sqlite3_column_int(pSqliteStmt, 0)));
            vsNote.push_back(std::to_string(sqlite3_column_int(pSqliteStmt, 1)));
            const unsigned char* pucBuffer = sqlite3_column_text(pSqliteStmt, 2);
            std::string sBuffer;
            sBuffer.append(reinterpret_cast<const char*>(pucBuffer));
            vsNote.push_back(sBuffer);
            sBuffer = "";
            pucBuffer = sqlite3_column_text(pSqliteStmt, 3);
            sBuffer.append(reinterpret_cast<const char*>(pucBuffer));
            vsNote.push_back(sBuffer);
            sBuffer = "";
            pucBuffer = sqlite3_column_text(pSqliteStmt, 4);
            sBuffer.append(reinterpret_cast<const char*>(pucBuffer));
            vsNote.push_back(sBuffer);
            sBuffer = "";
            pucBuffer = sqlite3_column_text(pSqliteStmt, 5);
            sBuffer.append(reinterpret_cast<const char*>(pucBuffer));
            vsNote.push_back(sBuffer);
            return SUCCESS;
        }
        else
            return NO_SUCH_CATEGORY;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::ChangeCategoryId(const int iNoteId,
                                      const int iCategoryId,
                                      const int iUserId)
{
    try {
        std::string sQuerry = "SELECT noteId from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iNoteId)
            return NO_SUCH_NOTE;
        sQuerry = "SELECT categoryId from category where userId = " + std::to_string(iCategoryId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iCategoryId)
            return NO_SUCH_CATEGORY;
        sQuerry = "SELECT userId from user where userId = " + std::to_string(iUserId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iNoteId)
            return NO_SUCH_USER;
        sQuerry = "SELECT userId from category where categoryId = ";
        sQuerry += "(SELECT categoryId from note where noteId = " + std::to_string(iNoteId) + ")";
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iUserId)
            return UNEXPECTED_ERROR;

        sQuerry = "UPDATE note SET categoryId = " + std::to_string(iCategoryId) + " where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);

    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::SetHeader(const int iNoteId, const std::string &sHeader)
{
    try {
        std::string sQuerry = "SELECT noteId from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iNoteId)
            return NO_SUCH_NOTE;

        sQuerry = "UPDATE note SET header = \'" + sHeader + "\' where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);

    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::SetText(const int iNoteId, const std::string &sText)
{
    try {
        std::string sQuerry = "SELECT noteId from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iNoteId)
            return NO_SUCH_NOTE;

        sQuerry = "UPDATE note SET text = \'" + sText + "\' where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);

    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::AddFriendAccess(const int iNoteId, const int iFriendId)
{
    try {
        std::string sQuerry = "SELECT noteId from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iNoteId)
            return NO_SUCH_NOTE;

        sQuerry = "SELECT userId from user where userId = " + std::to_string(iFriendId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iFriendId)
            return NO_SUCH_FRIEND;

        sQuerry = "SELECT friendAccessList from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        const unsigned char* pucFriendAccessList = sqlite3_column_text(pSqliteStmt, 0);

        std::string sFriendAccessList;
        sFriendAccessList.append(reinterpret_cast<const char*>(pucFriendAccessList));
        sFriendAccessList += std::to_string(iFriendId) + '|';

        sQuerry = "UPDATE note SET friendAccessList = \'" + sFriendAccessList + "\' where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::CheckFriendAccess(const int iNoteId, const int iFriendId)
{
    try {
        std::string sQuerry = "SELECT noteId from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iNoteId)
            return NO_SUCH_NOTE;
        sQuerry = "SELECT userId from user where userId = " + std::to_string(iFriendId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iFriendId)
            return NO_SUCH_FRIEND;

        sQuerry = "SELECT friendAccessList from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        const unsigned char* pucFriendAccessList = sqlite3_column_text(pSqliteStmt, 0);

        std::string sFriendAccessList;
        sFriendAccessList.append(reinterpret_cast<const char*>(pucFriendAccessList));
        char* pcFriendAccessList = new char[sFriendAccessList.length() + 1];
        strcpy(pcFriendAccessList, sFriendAccessList.c_str());
        char* pcToFriendAccessList;
        char* pcBuffer;
        std::string sFriendAccessListToDB;
        while (pcToFriendAccessList != NULL)
        {
            pcToFriendAccessList = strtok(pcFriendAccessList, "|");
            strcpy(pcBuffer, pcToFriendAccessList);
            if (!(strcmp(pcBuffer, std::to_string(iFriendId).c_str()))) {
                return SUCCESS;
            }
        }
        return ACCESS_DENIED;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}

const int IDataBase::DeleteFriendAccess(const int iNoteId, const int iFriendId)
{
    try {
        std::string sQuerry = "SELECT noteId from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        int iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iNoteId)
            return NO_SUCH_NOTE;
        sQuerry = "SELECT userId from user where userId = " + std::to_string(iFriendId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        iId = sqlite3_column_int(pSqliteStmt, 0);
        if (iId != iFriendId)
            return NO_SUCH_FRIEND;

        sQuerry = "SELECT friendAccessList from note where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);
        sqlite3_step(pSqliteStmt);
        const unsigned char* pucFriendAccessList = sqlite3_column_text(pSqliteStmt, 0);

        std::string sFriendAccessList;
        sFriendAccessList.append(reinterpret_cast<const char*>(pucFriendAccessList));
        char* pcFriendAccessList = new char[sFriendAccessList.length() + 1];
        strcpy(pcFriendAccessList, sFriendAccessList.c_str());
        char* pcToFriendAccessList;
        char* pcBuffer;
        std::string sFriendAccessListToDB;
        while (pcToFriendAccessList != NULL)
        {
            pcToFriendAccessList = strtok(pcFriendAccessList, "|");
            strcpy(pcBuffer, pcToFriendAccessList);
            if (pcBuffer != std::to_string(iFriendId)) {
                sFriendAccessListToDB += pcBuffer;
                sFriendAccessListToDB[sizeof(sFriendAccessListToDB) / sizeof(char) - 1] = '|';
            }
        }

        sQuerry = "UPDATE note SET friendAccessList = \'" + sFriendAccessListToDB + "\' where noteId = " + std::to_string(iNoteId);
        SendRequestToDB(sQuerry);

        return SUCCESS;
    }
    catch (...) {
        return UNEXPECTED_ERROR;
    }
}
