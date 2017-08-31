#include "global.h"

global* global::m_instance=nullptr;

global::global()
{
}

global* global::instance()
{
		if(m_instance==nullptr)
			m_instance=new global;
		return m_instance;
}

	void global::addOnlineUser(const string& UserName,user* newUser)
	{
		m_onlineUsers.insert({UserName,newUser});
	}


	SOCKET global::userSocket(const string& userName)
	{
		if(m_onlineUsers.find(userName)==m_onlineUsers.end())
			return -1;
		return m_onlineUsers[userName]->getSocket();
	}

	bool global::hasUser(const string& userName) const
	{
		return (m_allUsers.find(userName)!=m_allUsers.end());
	}

	user* global::getOnlineUser(const string& userName)
	{
		auto it=m_onlineUsers.find(userName);
		if(it==m_onlineUsers.end())
			return nullptr;
		return it->second;
	}

	void global::addOfflineMsg(const string& fromName, const string& toName,const string& msg)
	{
		string sendTime=getTime();
		chatRecord tmpmsg(fromName,msg,sendTime,0);
		m_offlineMsg.insert({toName,tmpmsg});
	}

void global::addUser(const string& userName)
{
	m_allUsers.insert(userName);
}

	vector<chatRecord> global::offlineMsg(const string& userName)
	{
		vector<chatRecord> result;
		if(m_offlineMsg.find(userName)==m_offlineMsg.end())
			return result;
		int count=m_offlineMsg.count(userName);
		auto it=m_offlineMsg.find(userName);
		while(count--)
		{
			result.push_back(it->second);
			++it;
		}

		m_offlineMsg.erase(m_offlineMsg.find(userName),it);
		return result;
	}

	bool global::hasOnlineUser(const string& userName)
	{
		return m_onlineUsers.find(userName)!=m_onlineUsers.end();
	}


