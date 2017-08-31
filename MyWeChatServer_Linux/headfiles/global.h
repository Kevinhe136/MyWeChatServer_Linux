#pragma once
#include <unordered_map>
#include <iostream>
#include"user.h"
#include <time.h>
#include <unordered_set>
using namespace std;

static string getTime()
{
	time_t timep;
	time(&timep);
	tm p;
	localtime_r(&timep,&p);

	string result;
	result+=to_string(p.tm_year+1900);
	if(p.tm_mon>9)
		result+=to_string(1+p.tm_mon);
	else
		result=result+"0"+to_string(1+p.tm_mon);
	if(p.tm_mday>9)
		result+=to_string(p.tm_mday);
	else
		result=result+"0"+to_string(p.tm_mday);
	if(p.tm_hour>9)
		result+=to_string(p.tm_hour);
	else
		result=result+"0"+to_string(p.tm_hour);
	if(p.tm_min>9)
		result+=to_string(p.tm_min);
	else
		result=result+"0"+to_string(p.tm_min);
	if(p.tm_sec>9)
		result+=to_string(p.tm_sec);
	else
		result=result+"0"+to_string(p.tm_sec);
	return result;
}


class global
{
private:
	global();
public:
	static global* instance();

	void addOnlineUser(const string& UserName,user* newUser);

	SOCKET userSocket(const string& userName);

	bool hasUser(const string& userName) const;

	user* getOnlineUser(const string& userName);

	void addOfflineMsg(const string& fromName, const string& toName,const string& msg);

	vector<chatRecord> offlineMsg(const string& userName);

	bool hasOnlineUser(const string& userName);

	void addUser(const string& userName);
private:
	static global* m_instance;
	unordered_map<string,user*> m_onlineUsers;
	unordered_multimap<string,chatRecord> m_offlineMsg;
	unordered_map<string,SOCKET> m_clientList;
	unordered_set<string> m_allUsers;
};

