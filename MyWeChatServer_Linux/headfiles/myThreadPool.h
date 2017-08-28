#pragma once
#ifndef _MYTHREADPOOL_H_ 
#define _MYTHREADPOOL_H_

#include<thread>
//#include<functional>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<list>
#include<iostream>
#include<queue>
#include"server.h"
//#include"myThread.h"
//using namespace std;
using std::vector;
using std::thread;
using std::mutex;
using std::queue;

class MyThreadPool
{
public:
	MyThreadPool(int num);
	~MyThreadPool();

	//void removeToBusy();
	//bool returnToFree(thread busyThread);

	bool addThreads(int numToAdd);
	bool deleteThreads(int numToDelete);

	void addTask(server* task);//感觉这边多态必须要用指针
	server* takeTask();
	//void startTask(server* task);
	void runTask();
	void stop();



private:
	list<thread> BusyThreads;
	vector<thread> FreeThreads;
	vector<thread> ThreadPool;
	queue<server*> TaskList;//不一定是vector做容器，暂时先这么写着
	int ThreadNum;
	mutex myMutex;
	bool running=true;
};


#endif // !_MYTHREADPOOL_H_ 
