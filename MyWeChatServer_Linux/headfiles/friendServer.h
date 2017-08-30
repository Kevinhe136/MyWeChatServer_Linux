#pragma once
#ifndef _FRIEND_SERVER_H_
#define _FRIEND_SERVER_H_

#include"xmlHandler.h"
#include"contacts.h"
//#include<Windows.h>
//#include<WinSock2.h>
//#include<WS2tcpip.h>
//#include<MSWSock.h>
#include<fstream>
#include"server.h"

class friendsServer:public server
{
	//typedef string string;
	//typedef TiXmlElement TiXmlElement;
public:
	friendsServer(Message friendInfo, SOCKET server, unordered_map<string, string> *accountData);
	~friendsServer();

	virtual void responseToClient();
	bool getFriendsList();
	void sendFriendList();
	bool addNewFriend(const string &friendName);
	bool deleteFriend(const string &friendName);
	void sendResult(const string resultKind,const string result);

	TiXmlElement addChild(const string &tagName, const string &text, TiXmlElement &Aparent);
	TiXmlElement findChild(const TiXmlElement &Aparent, const string &tagName) const;

private:
	Message FriendInfo;
	string UserName;
	unordered_map<string, friendData> FriendsList;
	unordered_map<string, string> *AccountData;
	SOCKET ServerSocket;
	xmlHandler *Stanza;
	mutex MyMutex;
};

#endif // !_FRIEND_SERVER_H_
