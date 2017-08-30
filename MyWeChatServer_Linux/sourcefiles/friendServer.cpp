#include "friendServer.h"

friendsServer::friendsServer(Message friendInfo, SOCKET server, unordered_map<string, string>* accountData):
	FriendInfo(friendInfo),ServerSocket(server),AccountData(accountData)
{
}

friendsServer::~friendsServer()
{
	delete Stanza;
	//Stanza = NULL;
}

void friendsServer::responseToClient()
{
	UserName = FriendInfo.userName();
	//当客户端的要求是取得联系人列表
	if (FriendInfo.Stanza->kind() == "friendList")
	{
		sendFriendList();
	}
	//当客户端要求是添加联系人
	else if(FriendInfo.Stanza->kind()=="addFriend")
	{
		string friendName;
		friendName = FriendInfo.findChild(FriendInfo.Stanza->element(), "friendName").GetText();

		MyMutex.lock();
		if (addNewFriend(friendName))
		{
			MyMutex.unlock();
			sendResult("addFriendResult", "successful");
			//return;
		}
		else
		{
			MyMutex.unlock();
			sendResult("addFriendResult", "fail");
		}
	}
	//当客户端要求是删除联系人
	else if (FriendInfo.Stanza->kind() == "deleteFriend")
	{
		string friendName;
		friendName = FriendInfo.findChild(FriendInfo.Stanza->element(), "friendName").GetText();

		MyMutex.lock();
		if (deleteFriend(friendName))
		{
			MyMutex.unlock();
			sendResult("addFriendResult", "successful");
			//return;
		}
		else
		{
			MyMutex.unlock();
			sendResult("addFriendResult", "fail");
		}
	}
}

bool friendsServer::getFriendsList()
{
/*	if (!Account.initDatabase())
	{
		cout << "数据库初始化失败！！" << endl;
		return false;
	}
*/	//account.getAccount();

	FriendsList = accountDatabase::instance()->getFriends(UserName);
	return true;
	/*FriendsList = AccountData->find(UserName)->second.FriendsList;*/

	//将联系人列表转为xml，用以发送给客户端

}

void friendsServer::sendFriendList()
{
	MyMutex.lock();
	if (!getFriendsList())
	{
		MyMutex.unlock();
		sendResult("friendListResult", "fail");
		return;
	}
	else
	{
		MyMutex.unlock();
	}


	Stanza = new xmlHandler((string)"friendList");

	for (auto iterator = FriendsList.begin();iterator != FriendsList.end();++iterator)
	{
		//TiXmlElement elem = addChild("friend", nullptr, *Stanza->element());
		TiXmlElement elem("friend");
		
		elem.SetAttribute("username", iterator->second.UserName.c_str());
		elem.SetAttribute("remarkname", iterator->second.RemarkName.c_str());
		elem.SetAttribute("status", iterator->second.IsOnline);
		elem.SetAttribute("avatar", iterator->second.Avatar.c_str());
		Stanza->element()->InsertEndChild(elem);
	}

	string msgToSend = Stanza->toString();
	send(ServerSocket, msgToSend.c_str(), msgToSend.size(), 0);

	delete Stanza;
	Stanza = nullptr;
}

bool friendsServer::addNewFriend(const string &friendName)
{
	//首先要请求对方的同意
	//

	if (FriendsList.find(friendName) != FriendsList.end())
	{
		cout << "联系人" << friendName << "已存在" << endl;
		return true;
	}

	FriendsList.insert({ friendName, friendData(friendName, friendName, true) });

	if (accountDatabase::instance()->addFriend(UserName, friendName))
	{
		cout << "添加好友失败！！" << endl;
		return false;
	}
	else
	{
		cout << "添加好友成功!!" << endl;
		return true;
	}

}

bool friendsServer::deleteFriend(const string &friendName)
{
	if (FriendsList.erase(friendName) == 0)
	{
		cout << "没有联系人" << friendName << endl;
		return true;
	}

	if (accountDatabase::instance()->deleteFriend(UserName, friendName))
	{
		cout << "删除联系人" << friendName << "失败" << endl;
		return false;
	}

	return true;

}

void friendsServer::sendResult(const string resultKind, const string result)
{
	xmlHandler *Stanza = new xmlHandler(resultKind);
	addChild("result", result, *Stanza->element());
	string msgToSend = Stanza->toString();

	send(ServerSocket, msgToSend.c_str(), msgToSend.size(), 0);
	delete Stanza;
}

TiXmlElement friendsServer::addChild(const string & tagName, const string & text, TiXmlElement & Aparent)
{
	TiXmlElement elem(tagName.c_str());
	TiXmlText elemText(text.c_str());
	elem.InsertEndChild(elemText);
	Aparent.InsertEndChild(elem);
	return elem;
}

TiXmlElement friendsServer::findChild(const TiXmlElement & Aparent, const string & tagName) const
{
	TiXmlElement elem = *(Aparent.FirstChildElement(tagName.c_str()));
	return elem;
}


