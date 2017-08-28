#include "friendServer.h"

friendsServer::friendsServer(Message friendInfo, SOCKET server, unordered_map<string, string>* accountData, accountDatabase account):
	FriendInfo(friendInfo),ServerSocket(server),AccountData(accountData),Account(account)
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
	//���ͻ��˵�Ҫ����ȡ����ϵ���б�
	if (FriendInfo.Stanza->kind() == "friendList")
	{
		sendFriendList();
	}
	//���ͻ���Ҫ���������ϵ��
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
	//���ͻ���Ҫ����ɾ����ϵ��
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
	if (!Account.initDatabase())
	{
		cout << "���ݿ��ʼ��ʧ�ܣ���" << endl;
		return false;
	}
	//account.getAccount();

	FriendsList = Account.getFriends(UserName);
	return true;
	/*FriendsList = AccountData->find(UserName)->second.FriendsList;*/

	//����ϵ���б�תΪxml�����Է��͸��ͻ���

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
	//����Ҫ����Է���ͬ��
	//

	if (FriendsList.find(friendName) != FriendsList.end())
	{
		cout << "��ϵ��" << friendName << "�Ѵ���" << endl;
		return true;
	}

	FriendsList.insert({ friendName, friendData(friendName, friendName, true) });

	if (!Account.addFriend(UserName, friendName))
	{
		cout << "��Ӻ���ʧ�ܣ���" << endl;
		return false;
	}
	else
	{
		cout << "��Ӻ��ѳɹ�!!" << endl;
		return true;
	}

}

bool friendsServer::deleteFriend(const string &friendName)
{
	if (FriendsList.erase(friendName) == 0)
	{
		cout << "û����ϵ��" << friendName << endl;
		return true;
	}

	if (!Account.deleteFriend(UserName, friendName))
	{
		cout << "ɾ����ϵ��" << friendName << "ʧ��" << endl;
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


