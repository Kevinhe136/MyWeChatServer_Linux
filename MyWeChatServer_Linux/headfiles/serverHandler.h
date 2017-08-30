#pragma once
#ifndef _SERVERHANDLER_H_
#define _SERVERHANDLER_H_

#include<iostream>
#include"myThreadPool.h"
//#include"server.h"
#include"message.h"
#include"logInServer.h"
#include"registerServer.h"
#include"friendServer.h"
#include"chatServer.h"
#include"fileServer.h"
#include "user.h"
#include "global.h"

istream &operator>>(istream &is, unordered_map<string, Contacts> *AccountData);

class serverHandler
{
public:
public:
	serverHandler(int threadNum = 20);
	~serverHandler();

	bool initThreadPool();
	bool getUserData();
	void changeThreadNumTo(int num);
	bool handleRegister(const Message &msg,SOCKET serverSocket);
	bool handleLogIn(const Message &msg, SOCKET serverSocket);
	bool handleFriendList(const Message &msg, SOCKET serverSocket);
	bool handleChat(const Message &msg, SOCKET serverSocket);
	bool handleFile(const Message &msg,SOCKET serverSocket, unordered_map<string,SOCKET> *clientList);
private:

	MyThreadPool *ServerThreadPool;
	int ThreadNum = 20;
//	accountDatabase account;
	unordered_map<string,SOCKET> *clientList;
	unordered_map<string,string> *AccountData;
};

#endif // !_SERVERHANDLER_H_
