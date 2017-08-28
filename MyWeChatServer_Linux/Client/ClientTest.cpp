#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<iostream>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<string>

using namespace std;
/*
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
*/
int main(void)
{
	int ClientFd;
	sockaddr_in ClientAddr;

	ClientAddr.sin_family=AF_INET;
	ClientAddr.sin_addr.s_addr=htons(INADDR_ANY);
/*	if(inet_aton("192.168.1.113",&ClientAddr.sin_addr)==0)
	{
		cout<<"client IPAddress error!!"<<endl;
		return 0;
	}*/
	string cIpAddress=inet_ntoa(ClientAddr.sin_addr);
	cout<<cIpAddress<<endl;

	ClientAddr.sin_port=4000;
	ClientFd=socket(AF_INET,SOCK_STREAM,0);
	if(ClientFd==-1)
	{
		cout<<"Client socket created falied!!"<<errno<<endl;
		return 0;
	}
	
/*	if(bind(ClientFd,(struct sockaddr*)&ClientAddr,sizeof(ClientAddr))==-1)
	{
		cout<<"bind Client address failed!!"<<errno<<endl;
		return 0;
	}
*/
	int ServerFd;
	sockaddr_in ServerAddr;
	ServerAddr.sin_family=AF_INET;
	if(inet_aton("127.0.0.1",&ServerAddr.sin_addr)==0)
	{
		cout<<"server IPAddress error!!"<<endl;
		return 0;
	}

	string ipAddress=inet_ntoa(ServerAddr.sin_addr);
	cout<<ipAddress<<endl;
	ServerAddr.sin_port=htons(8000);
	socklen_t ServerLen=sizeof(ServerAddr);

	if(connect(ClientFd,(struct sockaddr*)&ServerAddr,ServerLen)==-1)
	{
		cout<<"can't connect to server!!"<<endl;
		cout<<errno<<endl;
		return 0;
	}
	
	const char *buffer="Hello, My Server!!";
	send(ClientFd,buffer,18,0);
	shutdown(ClientFd,SHUT_RDWR);
	if(close(ClientFd)==-1)
		cout<<"close Client failed"<<endl;
	return 0;
}


