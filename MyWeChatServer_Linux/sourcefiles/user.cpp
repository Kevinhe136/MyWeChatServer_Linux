#include "user.h"
#include "global.h"

bool user::initFriendList()
{
	m_friendList = accountDatabase::instance()->getFriends(m_userName);

	for(auto it=m_friendList.begin();it!=m_friendList.end();++it)
	{
		string friendName=it->first;
		user* friendUser =global::instance()->getOnlineUser(friendName);
		if(friendUser!=nullptr)
		{
			m_onlineFriends.insert({friendName,friendUser});
		}
	}

	return true;
}

bool user::changeStatus(int status)
{
	if(!statusValid(status))
	{
		cout<<"the status is not valid"<<endl;
		return false;
	}

	if(status==m_status)
		return true;

	m_status=status;

	noticeFriends(status);
	return true;
}

void user::noticeFriends(int status) const
{
	for(auto it=m_onlineFriends.begin();it!=m_onlineFriends.end();++it)
	{
		it->second->updateFriendStatus(m_userName,status);

		//here is mainbody of changing friends status
		xmlHandler *Stanza = new xmlHandler((string)"change status");
		addChild("friend name", m_userName, *Stanza->element());
		addChild("status",to_string(status),*Stanza->element());
		string msgToSend = Stanza->toString();
	
		SOCKET peerSocket=it->second->getSocket();

		send(peerSocket, msgToSend.c_str(), msgToSend.size(), 0);
		delete Stanza;
	}
}

void user::addFriend(const string& friendName) const
{
	if(m_friendList.find(friendName)!=m_friendList.end())
	{
		return;
	}

	//next is send the notice to the friend ,if he approves, the addfriend action is over
	sendAddReq(friendName);	

}

void user::sendAddReq(const string& friendName) const
{
	if(!global::instance()->hasUser(friendName))
	{
		xmlHandler *Stanza = new xmlHandler((string)"waring");
		addChild("add friend waring", friendName+" is not exist !!", *Stanza->element());
		string msgToSend = Stanza->toString();

	
		send(m_socket, msgToSend.c_str(), msgToSend.size(), 0);
		delete Stanza;
	}
	else
	{
		xmlHandler *Stanza = new xmlHandler((string)"add friend");
		addChild("friend name", friendName, *Stanza->element());
		string msgToSend = Stanza->toString();

		SOCKET peerSocket=global::instance()->userSocket(friendName);
		if(peerSocket==-1)
		{
			cout<<"the user "<<friendName<<" is not online!!"<<endl;
			global::instance()->addOfflineMsg(m_userName,friendName,0);
			//add the require to the offline buffer
		}
		send(peerSocket, msgToSend.c_str(), msgToSend.size(), 0);
		delete Stanza;
	}
}


void user::addChatRecord(const string& friendName,const string& message,const string& time, int direction)
{
	m_chatRecord[m_recordCount]=chatRecord(friendName,message,time,direction);
	m_recordCount++;
	if(m_recordCount==MAX_RECORD_COUNT)
	{
		uploadRecord();
		m_chatRecord.clear();
		m_chatRecord.resize(MAX_RECORD_COUNT);
		m_recordCount=0;
	}
}

void user::addChatRecord(const chatRecord& record)
{
	m_chatRecord[m_recordCount]=record;
	m_recordCount++;
	if(m_recordCount==MAX_RECORD_COUNT)
	{
		uploadRecord();
		m_chatRecord.clear();
		m_chatRecord.resize(MAX_RECORD_COUNT);
		m_recordCount=0;
	}
}

bool user::uploadRecord()
{
	for(int i=0;i<m_chatRecord.size();++i)
	{
		string sqlstr;
		sqlstr = "insert into records_";
		sqlstr += m_userName;
		sqlstr += " (friendname,message,time,direction) VALUES(";
		sqlstr += "'" + m_chatRecord[i].m_friendName + "','"+m_chatRecord[i].m_message+"','" + m_chatRecord[i].m_time + "',";
		if(m_chatRecord[i].m_direction==1)
			sqlstr += "1);";
		else
			sqlstr += "0);";
		if (0 != mysql_query(&accountDatabase::instance()->accountData(), sqlstr.c_str()))
		{
			cout << "add chat record with " << m_chatRecord[i].m_friendName << " fail !! " << endl;
			return false;
		}
	}
	return true;
}

void user::updateFriendStatus(const string& friendName,int status)
{
	if(status==ONLINE)
	{
		user* friendUser=global::instance()->getOnlineUser(friendName);
		if(friendUser==nullptr)
			return;
		if(m_friendList.find(friendName)==m_friendList.end())
			return;
		if(m_onlineFriends.find(friendName)==m_onlineFriends.end())
		{
			m_onlineFriends.insert({friendName,friendUser});
			friendStatusNotice(friendName,status);
		}
		return;
	}
	else if(status==OFFLINE)
	{
		if(m_onlineFriends.find(friendName)!=m_onlineFriends.end())
		{
			m_onlineFriends.erase(friendName);
			friendStatusNotice(friendName,status);
		}
		return;
	}
}

void user::friendStatusNotice(const string& friendName,int status) const
{
	xmlHandler *Stanza = new xmlHandler((string)"change status");
	addChild("friend name", friendName, *Stanza->element());
	addChild("status",to_string(status),*Stanza->element());
	string msgToSend = Stanza->toString();

	send(m_socket, msgToSend.c_str(), msgToSend.size(), 0);
	delete Stanza;
}

bool user::isFriend(const string& friendName) const
{
	return (m_friendList.find(friendName)!=m_friendList.end());
}

bool user::isFriendOnline(const string& friendName) const
{
	return (m_onlineFriends.find(friendName)!=m_onlineFriends.end());
}


user* user::getOnlineFriend(const string& friendName)
{
	auto it=m_onlineFriends.find(friendName);
	if(it==m_onlineFriends.end())
		return nullptr;
	return it->second;
}

TiXmlElement user::addChild(const string & tagName, const string& text, TiXmlElement & Aparent) const
{
	TiXmlElement elem(tagName.c_str());
	TiXmlText elemText(text.c_str());
	elem.InsertEndChild(elemText);
	Aparent.InsertEndChild(elem);
	return elem;
}

TiXmlElement user::findChild(const TiXmlElement & Aparent, const string & tagName) const
{
	TiXmlElement elem = *(Aparent.FirstChildElement(tagName.c_str()));
	return elem;
}


