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
	static int AddUser(std::string sLogin, std::string sPassword);
	
	//return codes: (>0) - id; 
	//				( 0) - no such user; 
	//				(-1) - fault
	static int GetUserId(std::string sLogin, std::string sPassword);
	
	//return codes: ( 0) - no such user; 
	//				(-1) - unexpected error; 
    //				( 1) - Friends Ids;
	static int GetFriendList(int iId, std::vector <std::string> FriendList);
	
	//return codes: ( 1) - success;
	//				( 0) - no such user; 
	//				(-1) - no such friend;
	//				(-2) - unexpected error;
	static int AddFriend(int iUserId, int iFriendId);
	
	//return codes: ( 1) - success;
	//				( 0) - no such user; 
	//				(-1) - no such friend;
	//				(-2) - unexpected error;
	static int DeleteFriend(int iUserId, int iFriendId);
	
	//return codes: ( 1) - success;
	//				( 0) - no such user; 
	//				(-1) - unexpected error; 
	static int GetFriendRequestsList(int iId, 
									 std::vector<std::string> *vsFrReqList);
	
	//return codes: ("1" ) - success;
	//				("0" ) - no such user; 
	//				("-1") - no such friend;
	//				("-2") - unexpected error;
	static int AddFriendRequest(int iUserId, int iFrReqId);
	
	//return codes: ("1" ) - success;
	//				("0" ) - no such user; 
	//				("-1") - no such request;
	//				("-2") - unexpected error;
	static int DeleteFriendRequest(int iUserId, int iFrReqId);
//------------------------------------------------------------------------------
//						CATEGORY
//------------------------------------------------------------------------------
	//return codes: (>0) - category id;
	//				(0) - invalid User Id;
	//				(-1) - invalid Category Name;
	//				(-2) - unexpected error;
	static int CreateCategory(int iUserId, std::string sCategoryName);

	//return codes: (1) - success;
	//				(0) - invalid Category Id;
	//				(-1) - invalid User Id;
	//				(-2) - unexpected error;
	static int GetCategory(int iCategoryId, 
						   int iUserId, 
						   std::vector<std::string>* vsCategory);

	//return codes: (1) - success;
	//				(0) - invalid Category Id;
	//				(-1) - invalid User Id;
	//				(-2) - unexpected error;
	static int DeleteCategory(int iCategoryId, int iUserId);

	//return codes: (1) - success;
	//				(0) - invalid Category Id;
	//				(-1) - invalid User Id;
	//				(-2) - invalid Category Name;
	//				(-3) - unexpected error;
	static int ChangeCategoryName(int iCategoryId, 
								  int iUserId, 
								  std::string sCategoryName);
//------------------------------------------------------------------------------ 
//						NOTE
//------------------------------------------------------------------------------
	//return codes: (>0) - note id; 
	//				(0) - invalid Category Id;
	//				(-1) - invalid Key Words;
	//				(-2) - unexpected error;
	static int AddNote(int iCategoryId, std::string sKeyWords);

	//return codes: (1) - success;
	//				( 0) - invalid Note Id;
	//				(-1) - invalid User Id;
	//				(-2) - unexpected error;
	static int GetNote(int iNoteId, 
					   int iUserId, 
					   std::vector<std::string>* vsNote);

	//return codes: (1) - success;
	//				( 0) - invalid Note Id;
	//				(-1) - invalid Category Id;
	//				(-2) - invalid User Id;
	//				(-3) - unexpected error;
	static int ChangeCategoryId(int iNoteId, int iCategoryId, int iUserId);

	//return codes: (1) - success; 
	//				(0) - invalid Category Id;
	//				(-1) - invalid Header;
	//				(-2) - unexpected error;
	static int SetHeader(int iCategoryId, std::string sHeader);

	//return codes: (1) - success; 
	//				(0) - invalid Category Id;
	//				(-1) - invalid Text;
	//				(-2) - unexpected error;
	static int SetText(int iCategoryId, std::string sText);

	//return codes: ("1" ) - success;
	//				("0" ) - no such Note; 
	//				("-1") - no such friend;
	//				("-2") - unexpected error;
	static int AddFriendAccess(int iNoteId, int iFriendId);

	//return codes: ("1" ) - success;
	//				("0" ) - access denied; 
	//				("-1") - no such friend;
	//				("-2") - unexpected error;
	static int CheckFriendAccess(int iNoteId, int iFriendId);

	//return codes: ("1" ) - success;
	//				("0" ) - no such Note; 
	//				("-1") - no such friend;
	//				("-2") - unexpected error;
	static int DeleteFriendAccess(int iNoteId, int iFriendId);
};

#endif
