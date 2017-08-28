#include "myThreadPool.h"

MyThreadPool::MyThreadPool(int num)
{
	//ThreadPool = vector<thread>(num, thread(&MyThreadPool::runTask,this));
	for (int i = 0;i < num;++i)
	{
		ThreadPool.push_back(thread(&MyThreadPool::runTask, this));
	}
	//FreeThreads = ThreadPool;
}

MyThreadPool::~MyThreadPool()
{
	while(!TaskList.empty())
	{
		delete TaskList.front();
		TaskList.pop();
	}
}

//void MyThreadPool::removeToBusy()
//{
//	if (!FreeThreads.empty())//检查空闲线程是否为空
//	{
//		BusyThreads.push_back(FreeThreads.back());
//		FreeThreads.pop_back();		
//	}
//	else
//	{
//		cout << "freeThreadList empty!!";
//	}
//}
//
//bool MyThreadPool::returnToFree(thread busyThread)
//{
//	BusyThreads.remove(busyThread);
//	FreeThreads.push_back(busyThread);
//	return true;
//}

bool MyThreadPool::addThreads(int numToAdd)
{
	if (!FreeThreads.empty())
	{
		cout << "There is still freeThreads,no need to add new threads!";
		return false;
	}

	/*FreeThreads.insert(FreeThreads.end(), numToAdd, thread(&MyThreadPool::runTask,this));
	ThreadPool.insert(ThreadPool.end(), numToAdd, thread(&MyThreadPool::runTask, this));*/

	for (int i = 0;i < numToAdd;++i)
	{
		ThreadPool.push_back(thread(&MyThreadPool::runTask, this));
	}
	return true;
}

bool MyThreadPool::deleteThreads(int numToDelete)
{
	if (FreeThreads.size() < numToDelete)
	{
		cout << "not so many threads, delete fail!!";
		return false;
	}

	FreeThreads.erase(FreeThreads.end() - numToDelete, FreeThreads.end());
	ThreadPool.erase(ThreadPool.end() - numToDelete, ThreadPool.end());
	return true;
}

void MyThreadPool::addTask(server * task)
{
	TaskList.push(task);
}

server * MyThreadPool::takeTask()
{
	if(TaskList.empty())
		return nullptr;
	else
	{
		server *result = TaskList.front();
		TaskList.pop();
		return result;
	}
}

//void MyThreadPool::startTask(server * task)
//{
//	removeToBusy();
//	thread *&myThread = BusyThreads.back();
//	//myThread = new thread(task);
//	myThread= new thread(&MyThreadPool::runTask, this, myThread,task);
//}

void MyThreadPool::runTask()
{
	
	while (running)
	{
		myMutex.lock();
		//myMutex.lock();
		if (!TaskList.empty())
		{
			//myMutex.lock();
			server* task=takeTask();
			myMutex.unlock();
			//myMutex.unlock();
			cout << "thread " << std::this_thread::get_id() << " run" << endl;
			task->responseToClient();
			delete task;
			//this_thread::sleep_for(chrono::microseconds(1));
		}
		else
		{
			myMutex.unlock();
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			//myMutex.unlock();
		}
		
		//this_thread::sleep_for(chrono::microseconds(1));
	}
}

void MyThreadPool::stop()
{
	running = false;
}
