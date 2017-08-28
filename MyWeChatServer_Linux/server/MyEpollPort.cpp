#include"MyEpollPort.h"

#define MAX_EVENTS 100

bool myEpollServer::initializeServerSocket()
{
//	struct sockaddr_in serverAddr;
//	char buff[BUFF_SIZE];
	using namespace std;
				
	if((ServerFd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
										   
		cout<<"create server socket fail!!,error:"<<strerror(errno)<<endl;
		return false;
	}   
    
	setListenPort(8000);
	memset(&ServerAddr,0,sizeof(ServerAddr));
	ServerAddr.sin_family=AF_INET;
	ServerAddr.sin_addr.s_addr=htons(INADDR_ANY);
	ServerAddr.sin_port=htons(ServerPort);
									
	if(bind(ServerFd,(struct sockaddr*)&ServerAddr,sizeof(ServerAddr))==-1)
	{
		cout<<"bind server addr fail,error:"<<strerror(errno)<<endl;
		return false;
	}   
										
	if(listen(ServerFd,10)==-1)
	{
		cout<<"server listen fail,error:"<<strerror(errno)<<endl;
		return false;
	}  
	return true;
}

bool myEpollServer::initializeEpoll(int maxSize)
{
	struct epoll_event ev,events[100];
	int connectFd,nfds,epollFd;

	epollFd=epoll_create(maxSize);
	if(epollFd==-1)
	{
		perror("epoll_create");
		return false;
	}
	ev.events=EPOLLIN|EPOLLRDHUP;
	ev.data.fd=ServerFd;
	if(epoll_ctl(epollFd,EPOLL_CTL_ADD,ServerFd,&ev)==-1)
	{
		perror("epoll_ctl:ServerFd");
		return false;
	}

	for(;;)
	{
		nfds=epoll_wait(epollFd,events,MAX_EVENTS,-1);
		if(nfds==-1)
		{
			perror("epoll_wait");
			close(ServerFd);
			return false;
		}

		for(int i=0;i<nfds;++i)
		{
			cout<<i<<endl;
			if(events[i].data.fd==ServerFd)
			{
				cout<<1<<endl;
				sockaddr_in clientAddr;
				socklen_t len;
				connectFd=accept(ServerFd,(struct sockaddr*)&clientAddr,&len);
				if(connectFd==-1)
				{
					perror("accept");
					close(ServerFd);
					return false;
				}
				cout<<"client addr is: "<<inet_ntoa(clientAddr.sin_addr)<<endl;
				setnonblocking(connectFd);
				ev.events=EPOLLIN|EPOLLET;
				ev.data.fd=connectFd;
				if(epoll_ctl(epollFd,EPOLL_CTL_ADD,connectFd,&ev)==-1)
				{
					perror("epoll_ctl:connectFd");
					close(ServerFd);
					return false;
				}
			}
			else
			{
				cout<<2<<endl;
				if(events[i].events&EPOLLRDHUP||events[i].events&EPOLLERR)
				{
					sockaddr_in addr;
					socklen_t len=sizeof(addr);
					if(getpeername(events[i].data.fd,(struct sockaddr*)&addr,&len)==-1)
					{
						cout<<"get client address fail!1"<<endl;
					}
					cout<<"client:"<<inet_ntoa(addr.sin_addr)<<"out of link!!"<<endl;

				}
				//do_use_fd(events[i].data.fd);
				char buff[BUFF_SIZE]; 
				int n=recv(events[i].data.fd,buff,1000,0);
				if(n==0)
				{
					sockaddr_in addr;
					socklen_t len=sizeof(addr);
					if(getpeername(events[i].data.fd,(struct sockaddr*)&addr,&len)==-1)
					{
						cout<<"get client address fail!1"<<endl;
					}
					cout<<"client:"<<inet_ntoa(addr.sin_addr)<<"out of link!!"<<endl;


				}
				buff[n]='\0';
				cout<<buff<<endl;
			}
		}
	}

	return true;

}

void myEpollServer::doRecv(string msgRecved,int sockFd)
{
	TiXmlDocument* recvDoc=new TiXmlDocument();
	recvDoc->Parse(msgRecved.c_str());

	TiXmlPrinter strPrinter;
	recvDoc->Accept(&strPrinter);

	string test=strPrinter.CStr();

	Message *message=new Message(xmlHandler(*recvDoc));
	string msgKind=message->Stanza->kind();

	if(msgKind=="register")
	{
		ServerHandler->handlerRegister(*messgae,sockFd);
	}
	else if(msgKind=="login")
	{
		

	}











}

void myEpollServer::setListenPort(int port)
{
	ServerPort=port;
}



void myEpollServer::start()
{
	initializeServerSocket();
	initializeEpoll(100);
}

int myEpollServer::setnonblocking(int sockFd)
{
	if(fcntl(sockFd,F_SETFL,fcntl(sockFd,F_GETFD,0)|O_NONBLOCK)==-1)
	{
		return -1;
	}
	return 0;
}
