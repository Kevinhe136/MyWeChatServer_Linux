#include "logInServer.h"

bool earlySend(const chatRecord& chat1, const chatRecord& chat2)
{
	return (chat1.m_time<chat2.m_time);
}

logInServer::logInServer(Message logInInfo, SOCKET server, unordered_map<string, string>* accountData): LogInInfo(logInInfo),ServerSocket(server),AccountData(accountData)
{
}

logInServer::~logInServer()
{
}

void logInServer::responseToClient()
{
	UserName = LogInInfo.userName();
	PassWord = LogInInfo.password();

	MyMutex.lock();
	if (isUserNameRegistered())
	{
		newUser=new user(UserName,ONLINE,ServerSocket);
		global::instance()->addOnlineUser(UserName,newUser);
		newUser->initFriendList();
		newUser->noticeFriends(ONLINE);
		MyMutex.unlock();
		sendLogInSuccess();
		sendOfflineMsg();
		//return true;
	}
	else
	{
		MyMutex.unlock();
		sendLogInFail();
		//return false;
	}
}

void logInServer::sendLogInFail()
{
	sendResult("fail");
}

void logInServer::sendLogInSuccess()
{
	sendResult("successful");
}

bool logInServer::isUserNameRegistered()
{
	if (AccountData->find(UserName) != AccountData->end())
	{
		if (AccountData->find(UserName)->second == PassWord)
			return true;
	}
	
	return false;
}

void logInServer::sendResult(const string result)
{
	xmlHandler *Stanza = new xmlHandler((string)"logInResult");
	addChild("result", result, *Stanza->element());
	string msgToSend = Stanza->toString();

	send(ServerSocket, msgToSend.c_str(), msgToSend.size(), 0);
	delete Stanza;
}
/*
void logInServer::setOnline()
{
	unordered_map<string, friendData> friendList;
	friendList = Account.getFriends(UserName);
	for (auto it = friendList.begin();it != friendList.end();++it)
	{
		Account.setStatus(it->first, UserName, true);
		//Ȼ��Ҫ�������ߵ���ϵ�˷����û������ߵ�֪ͨ
	}
}
*/
bool sendNotice()
{
	
}


string logInServer::getUserName()
{
	return UserName;
}

void logInServer::sendOfflineMsg() const
{
	vector<chatRecord> offlineMsgs=global::instance()->offlineMsg(UserName);
	if(offlineMsgs.empty())
		return;
	sort(offlineMsgs.begin(),offlineMsgs.end(),earlySend);

	unsigned int size=offlineMsgs.size();

	for(int i=0;i<size;++i)
	{
		send(ServerSocket,offlineMsgs[i].m_message.c_str(),offlineMsgs[i].m_message.size(),0);
		newUser->addChatRecord(offlineMsgs[i]);
	}
}

TiXmlElement logInServer::addChild(const string & tagName, const string & text, TiXmlElement & Aparent)
{
	TiXmlElement elem(tagName.c_str());
	TiXmlText elemText(text.c_str());
	elem.InsertEndChild(elemText);
	Aparent.InsertEndChild(elem);
	return elem;
}

TiXmlElement logInServer::findChild(const TiXmlElement & Aparent, const string & tagName) const
{
	TiXmlElement elem = *(Aparent.FirstChildElement(tagName.c_str()));
	return elem;
}



