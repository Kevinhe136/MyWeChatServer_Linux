#pragma once
#ifndef _REGISTERSERVER_H_ 
#define _REGISTERSERVER_H_

#include"message.h"
#include"xmlHandler.h"
#include"contacts.h"
#include<unordered_map>
#include<fstream>
//#include<WinSock2.h>
#include"server.h"

class registerServer:public server
{
	//typedef string string;
	//typedef TiXmlElement TiXmlElement;
public:
	registerServer(Message registerInfo, SOCKET serverSocket, unordered_map<string, string> *accountData);
	~registerServer();

public:
	virtual void responseToClient();//作为回应添加账号的响应
							  //void sendMessage(string message);
	void sendRegisterFail();//返回申请账号失败
	void sendRegisterSuccess();//返回申请账号成功
	bool isUserNameRegistered();//判断是否这个用户名已用
	bool addNewAccount();//添加账号
	void sendResult(const string result);//发送申请结果给客户端
	TiXmlElement addChild(const string &tagName, const string &text, TiXmlElement &Aparent);
	TiXmlElement findChild(const TiXmlElement &Aparent, const string &tagName) const;
private:
	Message RegisterInfo;
	SOCKET ServerSocket;

	string UserName;
	string PassWord;
	unordered_map<string, string> *AccountData;
	mutex MyMutex;
	//    QDataStream accountStream;
	//    QFile accountFile;
};

#endif // !_REGISTERSERVER_H_ 
