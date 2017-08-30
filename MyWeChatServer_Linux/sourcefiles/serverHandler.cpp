#include "serverHandler.h"

istream & operator>>(istream & is, unordered_map<string, string>* AccountData)
{
	size_t size = 0;;
	is >> size;
	for (int i = 0;i < size;++i)
	{
		string userName;
		string password;
		is >> userName >> password;
		if (is)
		{
			AccountData->insert({ userName,password });
		}
		else
		{
			cout << "��ȡ�û�ʧ�ܣ���" << endl;
		}
	}
	return is;
	// TODO: �ڴ˴����� return ���
}

serverHandler::serverHandler(int threadNum):ThreadNum(threadNum)
{
}

serverHandler::~serverHandler()
{
	delete ServerThreadPool;
	delete AccountData;
}

bool serverHandler::initThreadPool()
{
	if (ThreadNum < 0)
	{
		cout << "��ʼ�߳���Ϊ�㣬�˳���" << endl;
		return false;
	}
	else
	{
		ServerThreadPool = new MyThreadPool(ThreadNum);
		return true;
	}

}

bool serverHandler::getUserData()
{
	AccountData = new unordered_map<string, string>;
	
	if (!accountDatabase::instance()->initDatabase())
	{
		cout << "init database failed����" << endl;
		return false;
	}
	if (!accountDatabase::instance()->getAccount())
	{
		cout << "��ȡ�˺���Դʧ�ܣ���" << endl;
		return false;
	}
	*AccountData = accountDatabase::instance()->showAccount();
	return true;

	/*ifstream accountFile("E:/file/Qt/MyWeChat_Server/MyWeChat_Server/Account.txt");
	if (accountFile)
	{
		accountFile >> AccountData;
		return true;
	}
	else
	{
		cout << "���û��ļ�ʧ�ܣ���" << endl;
		return false;
	}*/
}

void serverHandler::changeThreadNumTo(int num)
{
	if (num == ThreadNum)
		return;
	if (num > ThreadNum)
	{
		ServerThreadPool->addThreads(num - ThreadNum);
		return;
	}
	else
	{
		ServerThreadPool->deleteThreads(ThreadNum - num);
		return;
	}
}

bool serverHandler::handleRegister(const Message & msg, SOCKET serverSocket)
{
	registerServer *server = new registerServer(msg, serverSocket, AccountData);
	ServerThreadPool->addTask(server);
	return true;
}

bool serverHandler::handleLogIn(const Message & msg, SOCKET serverSocket)
{
	logInServer *server = new logInServer(msg, serverSocket, AccountData);
	ServerThreadPool->addTask(server);
	return true;
}

bool serverHandler::handleFriendList(const Message & msg, SOCKET serverSocket)
{
	friendsServer *server = new friendsServer(msg, serverSocket, AccountData);
	ServerThreadPool->addTask(server);
	return true;
}

bool serverHandler::handleChat(const Message & msg, SOCKET serverSocket)
{
	chatServer *server = new chatServer(msg, serverSocket);
	ServerThreadPool->addTask(server);
	return true;
}

bool serverHandler::handleFile(const Message &msg,SOCKET serverSocket, unordered_map<string,SOCKET> *clientList)
{
	fileServer *server=new fileServer(msg, serverSocket, AccountData,clientList);
	ServerThreadPool->addTask(server);
	return true;
}

