#ifndef DB_INTERFACE
#define	DB_INTERFACE
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Database/sqlite3.h"

class IDataBase {

public:
	static sqlite3_stmt* pSqliteStmt;
	static const int SendRequestToDB(std::string sQuerry);
//------------------------------------------------------------------------------
//						USER
//------------------------------------------------------------------------------
	//return codes: SUCCESS 1 / INVALID_INPUT_DATA -1 / UNEXPECTED_ERROR -7
	static const int AddUser(const std::string &sLogin, 
							 const std::string &sPassword, int& iUserId);
	
	//return codes: SUCCESS 1 / NO_SUCH_USER -2 / UNEXPECTED_ERROR -7
	static const int GetUserId(const std::string &sLogin,
							   const std::string &sPassword, int& iUserId);
	
	//return codes: SUCCESS 1 / NO_SUCH_USER -2 / UNEXPECTED_ERROR -7
	static const int GetFriendList(const int iId, 
								   std::vector <std::string> &FriendList);
	
	//return codes: SUCCESS 1		  / NO_SUCH_USER -2 
	//				NO_SUCH_FRIEND -3 / UNEXPECTED_ERROR -7
	static const int AddFriend(const int iUserId, const int iFriendId);
	
	//return codes: SUCCESS 1		  / NO_SUCH_USER -2 
	//				NO_SUCH_FRIEND -3 / UNEXPECTED_ERROR -7
	static const int DeleteFriend(const int iUserId, const int iFriendId);
	
	//return codes: SUCCESS 1 / NO_SUCH_USER -2 / UNEXPECTED_ERROR -7
	static const int GetFriendRequestsList(const int iId,
										   std::vector<std::string> &vsFrReqList);
	
	//return codes: SUCCESS 1		  / NO_SUCH_USER -2 
	//				NO_SUCH_FRIEND -3 / UNEXPECTED_ERROR -7
	static const int AddFriendRequest(const int iUserId, const int iFrReqId);
	
	//return codes: SUCCESS 1		   / NO_SUCH_USER -2 
	//				NO_SUCH_REQUEST -6 / UNEXPECTED_ERROR -7
	static const int DeleteFriendRequest(const int iUserId, const int iFrReqId);
//------------------------------------------------------------------------------
//						CATEGORY
//------------------------------------------------------------------------------
	//return codes: SUCCESS 1		      / NO_SUCH_USER -2 
	//				INVALID_INPUT_DATA -1 / UNEXPECTED_ERROR -7
	static const int CreateCategory(const int iUserId,
									const std::string &sCategoryName, int& iCategoryId);

	//return codes: SUCCESS 1		    / NO_SUCH_USER -2 
	//				NO_SUCH_CATEGORY -4 / UNEXPECTED_ERROR -7
	static const int GetCategory(const int iCategoryId,
								 const int iUserId,
								 std::vector<std::string> &vsCategory);

	//return codes: SUCCESS 1		    / NO_SUCH_USER -2 
	//				NO_SUCH_CATEGORY -4 / UNEXPECTED_ERROR -7
	static const int DeleteCategory(const int iCategoryId, const int iUserId);

	//return codes: SUCCESS 1		    / NO_SUCH_USER -2 
	//				NO_SUCH_CATEGORY -4 / UNEXPECTED_ERROR -7
	//				INVALID_INPUT_DATA -1
	static const int ChangeCategoryName(const int iCategoryId,
										const int iUserId,
										const std::string &sCategoryName);
//------------------------------------------------------------------------------ 
//						NOTE
//------------------------------------------------------------------------------
	//return codes: SUCCESS 1		    / INVALID_INPUT_DATA -1
	//				NO_SUCH_CATEGORY -4 / UNEXPECTED_ERROR -7
	static const int AddNote(const int iCategoryId, const std::string &sKeyWords, int& iNoteId);

	//return codes: SUCCESS 1		    / NO_SUCH_USER -2 
	//				NO_SUCH_NOTE -5 / UNEXPECTED_ERROR -7
	static const int GetNote(const int iNoteId,
							 const int iUserId,
							 std::vector<std::string> &vsNote);

	//return codes: SUCCESS 1		/ NO_SUCH_USER -2 
	//				NO_SUCH_NOTE -5 / NO_SUCH_CATEGORY -4
	//				UNEXPECTED_ERROR -7
	static const int ChangeCategoryId(const int iNoteId, const int iCategoryId, const int iUserId);

	//return codes: SUCCESS 1		/ INVALID_INPUT_DATA -1
	//				NO_SUCH_NOTE -5 / UNEXPECTED_ERROR -7
	static const int SetHeader(const int iNoteId, const std::string &sHeader);

	//return codes: SUCCESS 1		/ INVALID_INPUT_DATA -1
	//				NO_SUCH_NOTE -5 / UNEXPECTED_ERROR -7
	static const int SetText(const int iNoteId, const std::string &sText);

	//return codes: SUCCESS 1		/ NO_SUCH_FRIEND -3
	//				NO_SUCH_NOTE -5 / UNEXPECTED_ERROR -7
	static const int AddFriendAccess(const int iNoteId, const int iFriendId);

	//return codes: SUCCESS 1		/ NO_SUCH_FRIEND -3
	//				NO_SUCH_NOTE -5 / ACCESS_DENIED 0
	//				UNEXPECTED_ERROR -7
	static const int CheckFriendAccess(const int iNoteId, const int iFriendId);

	//return codes: SUCCESS 1		/ NO_SUCH_FRIEND -3
	//				NO_SUCH_NOTE -5 / UNEXPECTED_ERROR -7
	static const int DeleteFriendAccess(const int iNoteId, const int iFriendId);
};

#endif
