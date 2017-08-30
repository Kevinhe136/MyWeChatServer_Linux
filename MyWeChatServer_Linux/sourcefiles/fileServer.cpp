#include"fileServer.h"


fileServer::fileServer(Message messageInfo,SOCKET server, unordered_map<string,string> *accountData, unordered_map<string,SOCKET> *clientList):MessageInfo(messageInfo),ServerSocket(server),AccountData(accountData),ClientList(clientList)
{
}

fileServer::~fileServer()
{
}

void fileServer::responseToClient()
{
	FromName=MessageInfo.from();
	ToName=MessageInfo.to();
	string type=MessageInfo.Stanza->attribute("type");

	if(type=="ask for permission")
	{
		askForPermission();
	}
	else if(type=="answer")
	{
		string answer=MessageInfo.Stanza->attribute("answer");
		if(answer=="deny")
			sendDeny();
		else if(answer=="accepted")
			sendIPAddress();
		else
			cout<<"undefined answer for file!!"<<endl;
	}
}

void fileServer::askForPermission()
{
	FileName=MessageInfo.Stanza->attribute("filename");
	string filePath=MessageInfo.Stanza->attribute("filepath");
	xmlHandler *stanza=new xmlHandler((string)"file");
	stanza->setFrom(FromName);
	stanza->setTo(ToName);

	SOCKET clientSocket=ClientList->find(ToName)->second;
	stanza->setAttribute("type","ask for permission");
	stanza->setAttribute("filename",FileName);
	stanza->setAttribute("filepath",filePath);
	string msgToSend=stanza->toString();
	send(clientSocket,msgToSend.c_str(),msgToSend.size(),0);
	delete stanza;
}

void fileServer::sendDeny()
{
	
	FileName=MessageInfo.Stanza->attribute("filename");
	string filePath=MessageInfo.Stanza->attribute("filepath");
	xmlHandler *stanza=new xmlHandler((string)"file");
	stanza->setFrom(FromName);
	stanza->setTo(ToName);
	SOCKET clientSocket=ClientList->find(ToName)->second;

	stanza->setAttribute("type","answer");
	stanza->setAttribute("result","deny");
	stanza->setAttribute("filename",FileName);
	stanza->setAttribute("filepath",filePath);
	string msgToSend=stanza->toString();

	send(clientSocket,msgToSend.c_str(),msgToSend.size(),0);
	delete stanza;
}

void fileServer::sendIPAddress()
{
	
	FileName=MessageInfo.Stanza->attribute("filename");
	xmlHandler *stanza=new xmlHandler((string)"file");
	getIPAddress();
	stanza->setFrom(FromName);
	stanza->setTo(ToName);
	SOCKET clientSocket=ClientList->find(ToName)->second;

	string filePath=MessageInfo.Stanza->attribute("filepath");
	stanza->setAttribute("filepath",filePath);

	stanza->setAttribute("type","answer");
	stanza->setAttribute("result","accept");
 	stanza->setAttribute("IPAddress",IPAddress);
	stanza->setAttribute("Port",to_string(Port));
	stanza->setAttribute("filename",FileName);
	string msgToSend=stanza->toString();

	send(clientSocket,msgToSend.c_str(),msgToSend.size(),0);
	delete stanza;
}

void fileServer::getIPAddress()
{
	sockaddr_in addr;
	socklen_t len=sizeof(addr);
	if(getpeername(ServerSocket,(struct sockaddr*)&addr,&len)==-1)
	{
		cout<<"get client address fail!1"<<endl;
	}
	IPAddress=inet_ntoa(addr.sin_addr);
	Port=addr.sin_port;

}
