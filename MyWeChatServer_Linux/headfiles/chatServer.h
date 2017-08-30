#pragma once
#include"server.h"
#include"user.h"
#include"global.h"
class chatServer :public server
{
public:
	chatServer(Message messageInfo, SOCKET server);
	~chatServer();

	virtual void responseToClient();
	//SOCKET findFriendClient(string friendName);
	bool sendMessageToFriend(const string& msgToSend);
	void sendResult(const string resultKind, const string result);
	string getMsgToSend();

	TiXmlElement addChild(const string &tagName, const string &text, TiXmlElement &Aparent);
	TiXmlElement findChild(const TiXmlElement &Aparent, const string &tagName) const;

private:
	Message MessageInfo;
	string FromName;
	string ToName;
	//unordered_map<string, friendData> FriendsList;
	SOCKET ServerSocket;
	xmlHandler *Stanza;
	mutex MyMutex;
};
