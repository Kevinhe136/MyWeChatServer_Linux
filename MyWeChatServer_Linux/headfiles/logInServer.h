#pragma once
#ifndef _LOGINSERVER_H_ 
#define _LOGINSERVER_H_

#include"message.h"
#include"xmlHandler.h"
#include"contacts.h"
#include<unordered_map>
//#include<WinSock2.h>
#include"server.h"

class logInServer:public server
{
public:
	logInServer(Message logInInfo, SOCKET server, unordered_map<string, string> *accountData, 
		accountDatabase account, unordered_map<string, SOCKET> *clientList);
	~logInServer();

public:
	virtual void responseToClient();//作为回应添加账号的响应
						   //void sendMessage(string message);
	void sendLogInFail();//返回申请账号失败
	void sendLogInSuccess();//返回申请账号成功
	bool isUserNameRegistered();//判断是否这个用户名已用
	void sendResult(const string result);//发送申请结果给客户端
	void setOnline();

	string getUserName();
	TiXmlElement addChild(const string &tagName, const string &text, TiXmlElement &Aparent);
	TiXmlElement findChild(const TiXmlElement &Aparent, const string &tagName) const;


private:
	Message LogInInfo;
	SOCKET ServerSocket;

	string UserName;
	string PassWord;
	unordered_map<string, string> *AccountData;
	accountDatabase Account;
	mutex MyMutex;
	unordered_map<string, SOCKET> *ClientList;
};

#endif // !_LOGINSERVER_H_ 
