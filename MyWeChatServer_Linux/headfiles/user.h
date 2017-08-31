#pragma once
#include<sys/types.h>
#include<sys/socket.h>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<vector>
#include<iostream>
#include"message.h"
#include"tinyxml.h"
#include"contacts.h"
#include"accountDatabase.h"
//#include "global.h"
using namespace std;

#define SOCKET int

#define ONLINE 1
#define OFFLINE 2
#define BUSY 3

#define MAX_STATUS 3

#define MAX_RECORD_COUNT 10
/*
enum STATUS 
{
	ONLINE=1,
	OFFLINE,
	BUSY
};
*/

struct chatRecord
{
	string m_friendName;
	string m_message;
	string m_time;
	int m_direction;
	chatRecord(){}
	chatRecord(string friendName, string message, string time, int direction):m_friendName(friendName),m_message(message),m_time(time),m_direction(direction){}
};


class user
{
public:
	user(const string userName,int status,SOCKET socket):m_userName(userName),m_status(status),m_recordCount(0),m_socket(socket)
{
	m_chatRecord.resize(MAX_RECORD_COUNT);
}
	~user(){};
	bool initFriendList();
	bool changeStatus(int status);
	void noticeFriends(int status) const;
	void addFriend(const string& friendName) const;
	void addChatRecord(const string& friendName,const string& message,const string& time, int direction);
	void addChatRecord(const chatRecord& record);
	bool uploadRecord();
	void updateFriendStatus(const string& friendName,int status);
	void friendStatusNotice(const string& FriendName,int status) const;

	bool isFriend(const string& friendName) const;
	bool isFriendOnline(const string& friendName) const;
	void addOnlineFriend(const string& friendName);
	user* getOnlineFriend(const string& friendName);

	SOCKET getSocket()
	{
		return m_socket;
	}

private:
	void sendAddReq(const string& friendName) const;
	bool statusValid(int status)
	{
		return (status>0&&status<=MAX_STATUS);
	}
	TiXmlElement addChild(const string & tagName, const string& text, TiXmlElement & Aparent) const;
	TiXmlElement findChild(const TiXmlElement & Aparent, const string & tagName) const;

private:
	string m_userName;
	unordered_map<string,friendData> m_friendList;
	unordered_map<string,user*> m_onlineFriends;
	vector<chatRecord> m_chatRecord;
	int m_recordCount;
	int m_status;
	SOCKET m_socket;
};
