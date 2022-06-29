#include "IDataBase.h"
#include "DBErrors.h"
#include <string>

const int IDataBase::AddUser(const std::string &sLogin,
           const std::string &sPassword,
           int &iUserId)
{
	return std::stoi(sLogin);
}

const int IDataBase::GetUserId(const std::string &sLogin,
             const std::string &sPassword,
             int& iUserId)
{
	return std::stoi(sLogin);
}

const int IDataBase::GetFriendList(const int iId, 
								   std::vector <std::string> &FriendList)
{
	return iId;
}

const int IDataBase::AddFriend(const int iUserId, const int iFriendId)
{
	return iUserId;
}

const int IDataBase::DeleteFriend(const int iUserId, const int iFriendId)
{
	return iUserId;
}

const int IDataBase::GetFriendRequestsList(const int iId,
										   std::vector<std::string> &vsFrReqList)
{
	return iId;
}

const int IDataBase::AddFriendRequest(const int iUserId, const int iFrReqId)
{
	return iUserId;
}

const int IDataBase::DeleteFriendRequest(const int iUserId, const int iFrReqId)
{
	return iUserId;
}

const int IDataBase::CreateCategory(const int iUserId,
              const std::string &sCategoryName,
              int& iCategoryId)
{
	return iUserId;
}

const int IDataBase::GetCategory(const int iCategoryId,
								 const int iUserId,
								 std::vector<std::string> &vsCategory)
{
	return iCategoryId;
}

const int IDataBase::DeleteCategory(const int iCategoryId, const int iUserId)
{
	return iCategoryId;
}

const int IDataBase::ChangeCategoryName(const int    iCategoryId,
									    const int    iUserId,
										const std::string &sCategoryName)
{
	return iCategoryId;
}

const int IDataBase::AddNote(const int iCategoryId, const std::string &sKeyWords, int &iNoteId)
{
	return iCategoryId;
}

const int IDataBase::GetNote(const int iNoteId,
							 const int iUserId,
					    	 std::vector<std::string> &vsNote)
{
	return iNoteId;
}

const int IDataBase::ChangeCategoryId(const int iNoteId, 
									  const int iCategoryId, 
									  const int iUserId)
{
	return iNoteId;
}

const int IDataBase::SetHeader(const int iNoteId, const std::string &sHeader)
{
	return iNoteId;
}

const int IDataBase::SetText(const int iNoteId, const std::string &sText)
{
	return iNoteId;
}

const int IDataBase::AddFriendAccess(const int iNoteId, const int iFriendId)
{
	return iNoteId;
}

const int IDataBase::CheckFriendAccess(const int iNoteId, const int iFriendId)
{
	return iNoteId;
}

const int IDataBase::DeleteFriendAccess(const int iNoteId, const int iFriendId)
{
	return iNoteId;
}
