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
	registerServer(Message registerInfo, SOCKET serverSocket, unordered_map<string, string> *accountData,accountDatabase account);
	~registerServer();

public:
	virtual void responseToClient();//��Ϊ��Ӧ����˺ŵ���Ӧ
							  //void sendMessage(string message);
	void sendRegisterFail();//���������˺�ʧ��
	void sendRegisterSuccess();//���������˺ųɹ�
	bool isUserNameRegistered();//�ж��Ƿ�����û�������
	bool addNewAccount();//����˺�
	void sendResult(const string result);//�������������ͻ���
	TiXmlElement addChild(const string &tagName, const string &text, TiXmlElement &Aparent);
	TiXmlElement findChild(const TiXmlElement &Aparent, const string &tagName) const;
private:
	Message RegisterInfo;
	SOCKET ServerSocket;

	string UserName;
	string PassWord;
	unordered_map<string, string> *AccountData;
	accountDatabase Account;
	mutex MyMutex;
	//    QDataStream accountStream;
	//    QFile accountFile;
};

#endif // !_REGISTERSERVER_H_ 
