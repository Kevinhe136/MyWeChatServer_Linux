#pragma once
#ifndef _ACCOUNT_DATABASE_H_ 
#define _ACCOUNT_DATABASE_H_

#include<thread>
#include<mutex>
#include<unordered_map>
#include<string>
#include<iostream>
#include<string.h>
#include"mysql.h"
#include"contacts.h"

using std::thread;
using std::string;
using std::unordered_map;
using std::cout;
using std::endl;


class accountDatabase
{
public:
	accountDatabase();
	~accountDatabase();

	bool initDatabase();
	bool getAccount();
	unordered_map<string, string> showAccount();
	bool addAccount(string username, string password);
	bool deleteAccount(string username, string password);
	bool addFriend(string username, string friendname);
	bool deleteFriend(string username, string friendname);
	unordered_map<string,friendData> getFriends(string username);
	bool setFriendRemark(string username, string friendname, string remark);
	bool setStatus(string username, string friendname, bool status);

private:
	unordered_map<string, string> Account;
	MYSQL AccountData;
	
};

#endif // !_ACCOUNT_DATABASE_H_ 
