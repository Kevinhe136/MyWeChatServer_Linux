#include "chatServer.h"

chatServer::chatServer(Message messageInfo, SOCKET server):
	MessageInfo(messageInfo), ServerSocket(server)
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

	if(!global::instance()->hasUser(FromName))
		return;
	user* from = global::instance()->getOnlineUser(FromName);
	if(!from->isFriend(ToName))
	{
		return;
	}
	else
	{
		user* to=global::instance()->getOnlineUser(ToName);
		string msgToSend= getMsgToSend();
		string msgBody=MessageInfo.body();
		string sendTime=getTime();
		from->addChatRecord(ToName,msgBody,sendTime,1);
		if(from->isFriendOnline(ToName))
		{
			to->addChatRecord(FromName,msgBody,sendTime,0);
			sendMessageToFriend(msgToSend);
		}
		else
		{
			global::instance()->addOfflineMsg(FromName,ToName,msgBody);
		}
	}
}

bool chatServer::sendMessageToFriend(const string& msgToSend)
{
	MyMutex.lock();

	SOCKET ClientSocket = global::instance()->userSocket(ToName);
	MyMutex.unlock();

	send(ClientSocket, msgToSend.c_str(), msgToSend.size(), 0);
	return true;
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
	delete Stanza;
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
