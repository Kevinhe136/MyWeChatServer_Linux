#include "registerServer.h"

registerServer::registerServer(Message registerInfo, SOCKET serverSocket, unordered_map<string, string>* accountData, accountDatabase account):
							   RegisterInfo(registerInfo),ServerSocket(serverSocket),AccountData(accountData),Account(account)
{
}

registerServer::~registerServer()
{
}

void registerServer::responseToClient()
{
	UserName = RegisterInfo.userName();
	PassWord = RegisterInfo.password();

	MyMutex.lock();
	if (isUserNameRegistered())
	{
		MyMutex.unlock();
		sendRegisterFail();
	}
	else
	{
		if (addNewAccount())
		{
			MyMutex.unlock();
			sendRegisterSuccess();
		}
		else
		{
			MyMutex.unlock();
		}
	}
}

void registerServer::sendRegisterFail()
{
	sendResult("fail");
}

void registerServer::sendRegisterSuccess()
{
	sendResult("successful");
}

bool registerServer::isUserNameRegistered()
{
	if (AccountData->find(UserName) == AccountData->end())
		return false;
	else 
		return true;
}

bool registerServer::addNewAccount()
{
	AccountData->insert({ UserName,PassWord });

	if (!Account.initDatabase())
	{
		cout << "���ݿ��ʼ��ʧ�ܣ���" << endl;
		return false;
	}
	//account.getAccount();
	if (!Account.addAccount(UserName, PassWord))
	{
		cout << "������û�" << UserName << "�����ݿ�ʧ�ܣ���" << endl;
		return false;
	}
	return true;

	//ofstream accountFile("E:/file/Qt/MyWeChat_Server/MyWeChat_Server/Account.txt");
	//if (accountFile)
	//{
	//	accountFile << AccountData->size();
	//	accountFile.seekp(std::ios::end);
	//	accountFile << UserName << Contacts(UserName, PassWord);
	//	accountFile.close();
	//	return true;
	//}
	//else
	//{
	//	cout << "д��ע���û�" << UserName << "ʧ��";
	//	return false;
	//}
}

void registerServer::sendResult(const string result)
{
	xmlHandler *Stanza = new xmlHandler((string)"RegisterResult");
	addChild("result", result, *Stanza->element());
	string msgToSend = Stanza->toString();

	send(ServerSocket, msgToSend.c_str(), msgToSend.size(), 0);
	delete Stanza;
}

TiXmlElement registerServer::addChild(const string & tagName, const string & text, TiXmlElement & Aparent)
{
	TiXmlElement elem(tagName.c_str());
	TiXmlText elemText(text.c_str());
	elem.InsertEndChild(elemText);
	Aparent.InsertEndChild(elem);
	return elem;
}

TiXmlElement registerServer::findChild(const TiXmlElement & Aparent, const string & tagName) const
{
	TiXmlElement elem = *(Aparent.FirstChildElement(tagName.c_str()));
	return elem;
}
