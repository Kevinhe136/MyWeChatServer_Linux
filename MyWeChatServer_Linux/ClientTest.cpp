#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<iostream>
#include<errno.h>
#include<netinet/in.h>
using namespace std;

class clientTest
{
private:
	sockaddr_in ClientAddr;
	int ClientFd;
public:
	clientTest();
	~clientTest();
	void initialClient();
	void stopConnection();
	void sendMsg(string msg);
};

int main(void)
{
	int ClientFd;
	sockaddr_in ClientAddr;

	ClientAddr.sin_family=AF_INET;
	ClientAddr.sin_addr.s_addr=htons(INADDR_ANY);
	ClientAddr.sin_port=htons(0);

	ClientFd=socket(AF_INET,SOCK_STREAM,0);
	if(Client==-1)
	{
		cout<<"Client socket created falied!!"<<errno<<endl;
		return 0;
	}
	
	if(bind(ClientFd,(struct sockaddr*)&ClientAddr,sizeof(ClientAddr))==-1)
	{
		cout<<"bind Client address failed!!"<<errno<<endl;
		return 0;
	}

	int ServerFd;
	sockaddr_in ServerAddr;
	ServerAddr.sin_family=AF_INET;
	if(inet_aton("192.168.1.112",&ServerAddr.sin_addr)==0)
	{
		cout<<"server IPAddress error!!"<<endl;
		return 0;
	}
	ServerAddr.sin_port=6000;
	socklen_t ServerLen=sizeof(ServerAddr);

	if(connect(ClientFd,(struct sockaddr*)&ServerAddr,ServerLen)==-1)
	{
		cout<<"can't connect to server!!"<<endl;
		return 0;
	}
	
	char *buffer="Hello, My Server!!";
	send(ClientFd,buffer,18,0);
}


