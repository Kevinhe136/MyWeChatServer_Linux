#include"xmlHandler.h"
#include"contacts.h"
//#include<Windows.h>
//#include<WinSock2.h>
//#include<WS2tcpip.h>
//#include<MSWSock.h>
#include<fstream>
#include"server.h"
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<sys/socket.h>
#include<string>
#include<string.h>

using namespace std;

class fileServer:public server
{
public:
	fileServer(Message messageInfo, SOCKET serverSocket,unordered_map<string,string> *accountData,unordered_map<string,SOCKET> *clientList);
	~fileServer();
	void askForPermission();
	void sendIPAddress();
	void sendDeny();
	void getIPAddress();

	virtual void responseToClient();
private:
	Message MessageInfo;
	string FromName;
	string ToName;
	string FileName;
	string IPAddress;
	int Port;
	unordered_map<string,string> *AccountData;
	SOCKET ServerSocket;
	xmlHandler *Stanza;
	mutex MyMutex;
	unordered_map<string,SOCKET> *ClientList;
};
