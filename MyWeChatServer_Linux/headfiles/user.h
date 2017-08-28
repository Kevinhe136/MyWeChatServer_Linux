#include<string>
#include<unordered_map>
#include<map>
#include<vector>
#include<iostream>
using namespace std;

class user
{
public:
	user(const string userName,int status, shared_ptr<accountDatabase> account):m_userName(userName),m_status(status){}
	~user(){};
	void initFriendList(shared_ptr<accountDatabase> account);
	void changeStatus(int status);
	void addFriend(string friendName);
	void addChatRecord(string chatRecord);
	void uploadRecord();
	void updateFriendStatus(string friendName,int status);
	void sendStatusNotice(string FriendName,int status);

private:
	string m_userName;
	unordered_map<string,friendData> m_friendList;
	unordered_map<string,friendData> m_onlineFreinds;
	vector<string> m_chatRecord;
	int m_status;
//	shared_ptr<accountDatabase> m_account;
	
}
