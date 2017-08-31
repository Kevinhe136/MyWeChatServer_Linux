#pragma once
#ifndef _SERVER_H_
#define _SERVER_H_

//#include<Windows.h>
//#include<WS2tcpip.h>
#include<list>
//#include<winsock2.h>
#include<mutex>
#include"message.h"
#include"accountDatabase.h"
#include<sys/types.h>
#include<sys/socket.h>


using std::string;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::list;
using std::mutex;
using std::endl;

using std::cout;

#define SOCKET int

class server
{
public:
	server(){}
	~server(){}
	virtual void responseToClient() = 0;
private:	
};




#endif // !_SERVER_H_
