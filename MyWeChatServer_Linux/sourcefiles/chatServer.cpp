#include "chatServer.h"

chatServer::chatServer(Message messageInfo, SOCKET server, unordered_map<string, string>* accountData, accountDatabase account, unordered_map<string, SOCKET> *clientList):
	MessageInfo(messageInfo), ServerSocket(server), AccountData(accountData), Account(account),ClientList(clientList)
{
}

chatServer::~chatServer()
{
	delete Stanza;
}

void chatServer::responseToClient()
{
	FromName = MessageInfo.from();
	ToName = MessageInfo.to();
	sendMessageToFriend();
}

bool chatServer::sendMessageToFriend()
{
	MyMutex.lock();

	auto it = ClientList->find(ToName);
	if (it == ClientList->end())
	{
		MyMutex.unlock();

		cout << "好友" << "ToName" << "不在线" << endl;
		string result = ToName + " is not onLine!!";
		sendResult("chatResult", result);
		return false;
	}
	else
	{
		SOCKET ClientSocket = it->second;
		MyMutex.unlock();

		string msgToSend = getMsgToSend();		
		send(ClientSocket, msgToSend.c_str(), msgToSend.size(), 0);
		return true;
	}
}

void chatServer::sendResult(const string resultKind, const string result)
{
	xmlHandler *Stanza = new xmlHandler(resultKind);
	addChild("result", result, *Stanza->element());
	string msgToSend = Stanza->toString();

	send(ServerSocket, msgToSend.c_str(), msgToSend.size(), 0);
	delete Stanza;
}

string chatServer::getMsgToSend()
{
	xmlHandler *Stanza = new xmlHandler((string)"message");
	Stanza->setFrom(FromName);
	Stanza->setTo(ToName);

	string msgBody = MessageInfo.body();

	addChild("body", msgBody, *Stanza->element());
	string msgToSend = Stanza->toString();

	return msgToSend;
}

TiXmlElement chatServer::addChild(const string & tagName, const string & text, TiXmlElement & Aparent)
{
	TiXmlElement elem(tagName.c_str());
	TiXmlText elemText(text.c_str());
	elem.InsertEndChild(elemText);
	Aparent.InsertEndChild(elem);
	return elem;
}

TiXmlElement chatServer::findChild(const TiXmlElement & Aparent, const string & tagName) const
{
	TiXmlElement elem = *(Aparent.FirstChildElement(tagName.c_str()));
	return elem;
}
