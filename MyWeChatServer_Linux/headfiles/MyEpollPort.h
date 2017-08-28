#include<sys/socket.h>
#include<sys/epoll.h>
#include<iostream>
#include<vector>
#include"tinyxml.h"
#include"message.h"
#include"serverHandler.h"
#include<string>
#include<unordered_map>
#include<errno.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#define MAX_SIZE 500
#define BUFF_SIZE 1000

using namespace std;
class myEpollServer
{
public:
    myEpollServer(int serverPort);
	~myEpollServer();
	int setnonblocking(int socketFd);
	void start();
	void stop();
	void setListenPort(int Port);
	//string getLocalIP();
	void setLocalAddr();
	void doRecv(string msgRecved,int sockfd);

	bool initializeEpoll(int maxSize);
	bool initializeServerSocket();
private:
	//listen socket info
	int ServerFd=0;
	sockaddr_in ServerAddr;
	int ServerPort;

	serverHandler *ServerHandler=nullptr;
	unordered_map<string,int> *ClientList=nullptr;
	
};
