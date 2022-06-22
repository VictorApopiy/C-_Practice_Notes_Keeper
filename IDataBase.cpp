#include "IDataBase.h"
#include <string>

int IDataBase::AddUser(std::string sLogin, std::string sPassword) {
	int i = std::stoi(sLogin);
	return i;
}

int IDataBase::GetUserId(std::string sLogin, std::string sPassword)
{
	int i = stoi(sLogin);
	return i;
}

int IDataBase::GetFriendList(int iId, std::vector <std::string> FriendList)
{
	return iId;
}

int IDataBase::AddFriend(int iUserId, int iFriendId)
{
	return iUserId;
}

int IDataBase::DeleteFriend(int iUserId, int iFriendId)
{
	return iUserId;
}

int IDataBase::GetFriendRequestsList(int iId,
								     std::vector<std::string>* vsFrReqList)
{
	return iId;
}

int IDataBase::AddFriendRequest(int iUserId, int iFrReqId)
{
	return iUserId;
}

int IDataBase::DeleteFriendRequest(int iUserId, int iFrReqId)
{
	return iUserId;
}

int IDataBase::CreateCategory(int iUserId, std::string sCategoryName)
{
	return iUserId;
}

int IDataBase::GetCategory(int iCategoryId, 
						   int iUserId, 
						   std::vector<std::string>* vsCategory)
{
	return iCategoryId;
}

int IDataBase::DeleteCategory(int iCategoryId, int iUserId)
{
	return iCategoryId;
}

int IDataBase::ChangeCategoryName(int    iCategoryId,
								  int    iUserId, 
								  std::string sCategoryName)
{
	return iCategoryId;
}

int IDataBase::AddNote(int iCategoryId, std::string sKeyWords)
{
	return iCategoryId;
}

int IDataBase::GetNote(int iNoteId, 
					   int iUserId, 
					   std::vector<std::string>* vsNote)
{
	return iNoteId;
}

int IDataBase::ChangeCategoryId(int iNoteId, int iCategoryId, int iUserId)
{
	return iNoteId;
}

int IDataBase::SetHeader(int iCategoryId, std::string sHeader)
{
	return iCategoryId;
}

int IDataBase::SetText(int iCategoryId, std::string sText)
{
	return iCategoryId;
}

int IDataBase::AddFriendAccess(int iNoteId, int iFriendId)
{
	return iNoteId;
}

int IDataBase::CheckFriendAccess(int iNoteId, int iFriendId)
{
	return iNoteId;
}

int IDataBase::DeleteFriendAccess(int iNoteId, int iFriendId)
{
	return iNoteId;
}