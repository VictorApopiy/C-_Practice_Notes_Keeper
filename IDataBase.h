#ifndef DB_INTERFACE
#define	DB_INTERFACE
#include <iostream>

using namespace std;

class IDataBase {
public:
//------------------------------------------------------------------------------
//						USER
//------------------------------------------------------------------------------
	//return codes: ( 1) - success; 
	//				( 0) - invalid login/password;
	//				(-1) - unexpected error
	int AddUser(string sLogin, string sPassword);
	
	//return codes: (>0) - id; 
	//				( 0) - no such user; 
	//				(-1) - fault
	int GetUserId(string sLogin, string sPassword);
	
	//return codes: (" 0") - no such user; 
	//				("-1") - unexpected error; 
    //				(*other str*) - Friends Ids;
	string GetFriendList(int id);
	
	//return codes: ("1" ) - success;
	//				("0" ) - no such user; 
	//				("-1") - no such friend;
	//				("-2") - unexpected error;
	string AddFriend(int iUserId, int iFriendId);
	
	//return codes: ("1" ) - success;
	//				("0" ) - no such user; 
	//				("-1") - no such friend;
	//				("-2") - unexpected error;
	string DeleteFriend(int iUserId, int iFriendId);
	
	//return codes: (" 0") - no such user; 
	//				("-1") - unexpected error; 
	//				(*other str*) - Friends Ids;
	string GetFriendRequestsList(int id);
	
	//return codes: ("1" ) - success;
	//				("0" ) - no such user; 
	//				("-1") - no such friend;
	//				("-2") - unexpected error;
	string AddFriendRequest(int iUserId, int iFrReqId);
	
	//return codes: ("1" ) - success;
	//				("0" ) - no such user; 
	//				("-1") - no such request;
	//				("-2") - unexpected error;
	string DeleteFriendRequest(int iUserId, int iFrReqId);
//------------------------------------------------------------------------------
//						CATEGORY
//------------------------------------------------------------------------------
	//return codes: (>0) - category id;
	//				(0) - invalid User Id;
	//				(-1) - invalid Category Name;
	//				(-2) - unexpected error;
	int CreateCategory(int iUserId, string sCategoryName);

	//return codes: (1) - success;
	//				(0) - invalid Category Id;
	//				(-1) - invalid User Id;
	//				(-2) - unexpected error;
	int DeleteCategory(int iCategoryId, int iUserId);

	//return codes: (1) - success;
	//				(0) - invalid Category Id;
	//				(-1) - invalid User Id;
	//				(-2) - invalid Category Name;
	//				(-3) - unexpected error;
	int ChangeCategoryName(int iCategoryId, int iUserId, string sCategoryName);
//------------------------------------------------------------------------------ 
//						NOTE
//------------------------------------------------------------------------------
	//return codes: (>0) - note id; 
	//				(0) - invalid Category Id;
	//				(-1) - invalid Key Words;
	//				(-2) - unexpected error;
	int AddNote(int iCategoryId, string sKeyWords);

	//return codes: (1) - success;
	//				( 0) - invalid Note Id;
	//				(-1) - invalid Category Id;
	//				(-2) - invalid User Id;
	//				(-3) - unexpected error;
	int ChangeCategoryId(int iNoteId, int iCategoryId, int iUserId);

	//return codes: (1) - success; 
	//				(0) - invalid Category Id;
	//				(-1) - invalid Header;
	//				(-2) - unexpected error;
	int SetHeader(int iCategoryId, string sHeader);

	//return codes: (1) - success; 
	//				(0) - invalid Category Id;
	//				(-1) - invalid Text;
	//				(-2) - unexpected error;
	int SetText(int iCategoryId, string sText);

	//return codes: ("1" ) - success;
	//				("0" ) - no such Note; 
	//				("-1") - no such friend;
	//				("-2") - unexpected error;
	int AddFriendAccess(int iNoteId, int iFriendId);

	//return codes: ("1" ) - success;
	//				("0" ) - no such Note; 
	//				("-1") - no such friend;
	//				("-2") - unexpected error;
	int DeleteFriendAccess(int iNoteId, int iFriendId);
};

#endif
