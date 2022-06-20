#include "IDataBase.h"
#include <string>

int IDataBase::AddUser(string sLogin, string sPassword) {
	int i = stoi(sLogin);
	return i;
}

int IDataBase::GetUserId(string sLogin, string sPassword)
{
	int i = stoi(sLogin);
	return i;
}

string IDataBase::GetFriendList(int id)
{
	return to_string(id);
}

string IDataBase::AddFriend(int iUserId, int iFriendId)
{
	return to_string(iUserId);
}

string IDataBase::DeleteFriend(int iUserId, int iFriendId)
{
	return to_string(iUserId);
}

string IDataBase::GetFriendRequestsList(int id)
{
	return to_string(id);
}

string IDataBase::AddFriendRequest(int iUserId, int iFrReqId)
{
	return to_string(iUserId);
}

string IDataBase::DeleteFriendRequest(int iUserId, int iFrReqId)
{
	return to_string(iUserId);
}

int IDataBase::CreateCategory(int iUserId, string sCategoryName)
{
	return iUserId;
}

int IDataBase::DeleteCategory(int iCategoryId, int iUserId)
{
	return iCategoryId;
}

int IDataBase::ChangeCategoryName(int    iCategoryId, 
								  int    iUserId, 
								  string sCategoryName)
{
	return iCategoryId;
}

int IDataBase::AddNote(int iCategoryId, string sKeyWords)
{
	return iCategoryId;
}

int IDataBase::ChangeCategoryId(int iNoteId, int iCategoryId, int iUserId)
{
	return iNoteId;
}

int IDataBase::SetHeader(int iCategoryId, string sHeader)
{
	return iCategoryId;
}

int IDataBase::SetText(int iCategoryId, string sText)
{
	return iCategoryId;
}

int IDataBase::AddFriendAccess(int iNoteId, int iFriendId)
{
	return iNoteId;
}

int IDataBase::DeleteFriendAccess(int iNoteId, int iFriendId)
{
	return iNoteId;
}