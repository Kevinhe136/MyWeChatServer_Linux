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
	virtual void responseToClient();//��Ϊ��Ӧ����˺ŵ���Ӧ
						   //void sendMessage(string message);
	void sendLogInFail();//���������˺�ʧ��
	void sendLogInSuccess();//���������˺ųɹ�
	bool isUserNameRegistered();//�ж��Ƿ�����û�������
	void sendResult(const string result);//�������������ͻ���
	void setOnline();
	bool sendNotice();
	
	void sendOfflineMsg() const;

	string getUserName();
	TiXmlElement addChild(const string &tagName, const string &text, TiXmlElement &Aparent);
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
