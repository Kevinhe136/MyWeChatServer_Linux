#pragma once
#include"server.h"

class chatServer :public server
{
public:
	chatServer(Message messageInfo, SOCKET server, unordered_map<string, string> *accountData, accountDatabase account, unordered_map<string, SOCKET> *clientList);
	~chatServer();

	virtual void responseToClient();
	//SOCKET findFriendClient(string friendName);
	bool sendMessageToFriend();
	void sendResult(const string resultKind, const string result);
	string getMsgToSend();

	TiXmlElement addChild(const string &tagName, const string &text, TiXmlElement &Aparent);
	TiXmlElement findChild(const TiXmlElement &Aparent, const string &tagName) const;

private:
	Message MessageInfo;
	string FromName;
	string ToName;
	//unordered_map<string, friendData> FriendsList;
	unordered_map<string, string> *AccountData;
	SOCKET ServerSocket;
	xmlHandler *Stanza;
	accountDatabase Account;
	mutex MyMutex;
	unordered_map<string, SOCKET> *ClientList;
};
