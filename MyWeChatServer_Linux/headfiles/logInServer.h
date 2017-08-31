#pragma once
#ifndef _LOGINSERVER_H_ 
#define _LOGINSERVER_H_

#include"message.h"
#include"xmlHandler.h"
#include"contacts.h"
#include<unordered_map>
#include<algorithm>
//#include<WinSock2.h>
#include"server.h"
#include "user.h"
#include "global.h"
using namespace std;


class logInServer:public server
{
public:
	logInServer(Message logInInfo, SOCKET server, unordered_map<string, string> *accountData);
	~logInServer();

public:
	virtual void responseToClient();//作为回应添加账号的响应
						   //void sendMessage(string message);
	void sendLogInFail();//返回申请账号失败
	void sendLogInSuccess();//返回申请账号成功
	bool isUserNameRegistered();//判断是否这个用户名已用
	void sendResult(const string result);//发送申请结果给客户端
	void setOnline();
	bool sendNotice();
	
	void sendOfflineMsg() const;

	string getUserName();
	TiXmlElement addChild(const string &tagName, const string &text, TiXmlElement &Aparent) const;
	TiXmlElement findChild(const TiXmlElement &Aparent, const string &tagName) const;


private:
	Message LogInInfo;
	SOCKET ServerSocket;

	string UserName;
	string PassWord;
	unordered_map<string, string> *AccountData;
	mutex MyMutex;
	user *newUser;
};

#endif // !_LOGINSERVER_H_ 
