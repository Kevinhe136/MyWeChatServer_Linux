#include "logInServer.h"

logInServer::logInServer(Message logInInfo, SOCKET server, unordered_map<string, string>* accountData, accountDatabase account, unordered_map<string, SOCKET> *clientList):
						 LogInInfo(logInInfo),ServerSocket(server),AccountData(accountData),Account(account),ClientList(clientList)
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
		ClientList->insert({ UserName,ServerSocket });//登录成功，将用户记录下来
		MyMutex.unlock();
		sendLogInSuccess();
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

void logInServer::setOnline()
{
	unordered_map<string, friendData> friendList;
	friendList = Account.getFriends(UserName);
	for (auto it = friendList.begin();it != friendList.end();++it)
	{
		Account.setStatus(it->first, UserName, true);
		//然后还要向其在线的联系人发送用户已上线的通知
	}
}

string logInServer::getUserName()
{
	return UserName;
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
