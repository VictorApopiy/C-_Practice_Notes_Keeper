#ifndef DB_INTERFACE
#define	DB_INTERFACE
#include <iostream>
#include <vector>

class IDataBase {
public:
//------------------------------------------------------------------------------
//						USER
//------------------------------------------------------------------------------
	//return codes: ( 1) - success; 
	//				( 0) - invalid login/password;
	//				(-1) - unexpected error
	static const int AddUser(const std::string &sLogin, 
							 const std::string &sPassword);
	
	//return codes: (>0) - id; 
	//				( 0) - no such user; 
	//				(-1) - fault
	static const int GetUserId(const std::string &sLogin, 
							   const std::string &sPassword);
	
	//return codes: ( 0) - no such user; 
	//				(-1) - unexpected error; 
    //				( 1) - Friends Ids;
	static const int GetFriendList(const int iId, 
								   std::vector <std::string> &FriendList);
	
	//return codes: ( 1) - success;
	//				( 0) - no such user; 
	//				(-1) - no such friend;
	//				(-2) - unexpected error;
	static const int AddFriend(const int iUserId, const int iFriendId);
	
	//return codes: ( 1) - success;
	//				( 0) - no such user; 
	//				(-1) - no such friend;
	//				(-2) - unexpected error;
	static const int DeleteFriend(const int iUserId, const int iFriendId);
	
	//return codes: ( 1) - success;
	//				( 0) - no such user; 
	//				(-1) - unexpected error; 
	static const int GetFriendRequestsList(const int iId,
										   std::vector<std::string> &vsFrReqList);
	
	//return codes: ( 1) - success;
	//				( 0) - no such user; 
	//				(-1) - no such friend;
	//				(-2) - unexpected error;
	static const int AddFriendRequest(const int iUserId, const int iFrReqId);
	
	//return codes: ( 1) - success;
	//				( 0) - no such user; 
	//				(-1) - no such request;
	//				(-2) - unexpected error;
	static const int DeleteFriendRequest(const int iUserId, const int iFrReqId);
//------------------------------------------------------------------------------
//						CATEGORY
//------------------------------------------------------------------------------
	//return codes: (>0) - category id;
	//				( 0) - invalid User Id;
	//				(-1) - invalid Category Name;
	//				(-2) - unexpected error;
	static const int CreateCategory(const int iUserId, 
									const std::string &sCategoryName);

	//return codes: ( 1) - success;
	//				( 0) - invalid Category Id;
	//				(-1) - invalid User Id;
	//				(-2) - unexpected error;
	static const int GetCategory(const int iCategoryId,
								 const int iUserId,
								 std::vector<std::string> &vsCategory);

	//return codes: ( 1) - success;
	//				( 0) - invalid Category Id;
	//				(-1) - invalid User Id;
	//				(-2) - unexpected error;
	static const int DeleteCategory(const int iCategoryId, const int iUserId);

	//return codes: ( 1) - success;
	//				( 0) - invalid Category Id;
	//				(-1) - invalid User Id;
	//				(-2) - invalid Category Name;
	//				(-3) - unexpected error;
	static const int ChangeCategoryName(const int iCategoryId,
										const int iUserId,
										const std::string &sCategoryName);
//------------------------------------------------------------------------------ 
//						NOTE
//------------------------------------------------------------------------------
	//return codes: (>0) - note id; 
	//				( 0) - invalid Category Id;
	//				(-1) - invalid Key Words;
	//				(-2) - unexpected error;
	static const int AddNote(const int iCategoryId, const std::string &sKeyWords);

	//return codes: ( 1) - success;
	//				( 0) - invalid Note Id;
	//				(-1) - invalid User Id;
	//				(-2) - unexpected error;
	static const int GetNote(const int iNoteId,
							 const int iUserId,
							 std::vector<std::string> &vsNote);

	//return codes: ( 1) - success;
	//				( 0) - invalid Note Id;
	//				(-1) - invalid Category Id;
	//				(-2) - invalid User Id;
	//				(-3) - unexpected error;
	static const int ChangeCategoryId(const int iNoteId, const int iCategoryId, const int iUserId);

	//return codes: ( 1) - success; 
	//				( 0) - invalid Category Id;
	//				(-1) - invalid Header;
	//				(-2) - unexpected error;
	static const int SetHeader(const int iCategoryId, const std::string &sHeader);

	//return codes: ( 1) - success; 
	//				( 0) - invalid Category Id;
	//				(-1) - invalid Text;
	//				(-2) - unexpected error;
	static const int SetText(const int iCategoryId, const std::string &sText);

	//return codes: ( 1) - success;
	//				( 0) - no such Note; 
	//				(-1) - no such friend;
	//				(-2) - unexpected error;
	static const int AddFriendAccess(const int iNoteId, const int iFriendId);

	//return codes: ( 1) - success;
	//				( 0) - access denied; 
	//				(-1) - no such friend;
	//				(-2) - unexpected error;
	static const int CheckFriendAccess(const int iNoteId, const int iFriendId);

	//return codes: ( 1) - success;
	//				( 0) - no such Note; 
	//				(-1) - no such friend;
	//				(-2) - unexpected error;
	static const int DeleteFriendAccess(const int iNoteId, const int iFriendId);
};

#endif
