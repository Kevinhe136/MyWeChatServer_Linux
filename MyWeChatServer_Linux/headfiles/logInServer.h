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
	virtual void responseToClient();//��Ϊ��Ӧ����˺ŵ���Ӧ
						   //void sendMessage(string message);
	void sendLogInFail();//���������˺�ʧ��
	void sendLogInSuccess();//���������˺ųɹ�
	bool isUserNameRegistered();//�ж��Ƿ�����û�������
	void sendResult(const string result);//�������������ͻ���
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
