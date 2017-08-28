#include "contacts.h"

friendData::friendData()
{
}

friendData::friendData(string username, string remarkName, bool isOnline):UserName(username),RemarkName(remarkName),IsOnline(isOnline)
{
}

ostream & operator<<(ostream & os, const friendData & friends)
{
	os << friends.UserName << friends.RemarkName << friends.IsOnline << friends.Avatar;
	return os;
	// TODO: 在此处插入 return 语句
}

istream & operator>>(istream & is, friendData & friends)
{
	is >> friends.UserName >> friends.RemarkName >> friends.IsOnline >> friends.Avatar;
	if (!is)
	{
		cout << "friendData写入失败，失败用户为：" << friends.UserName << endl;
	}
	return is;
	// TODO: 在此处插入 return 语句
}

ostream & operator<<(ostream & os, const Contacts & contact)
{
	os << contact.UserName << contact.PassWord << contact.FriendsList.size();

	for (auto it = contact.FriendsList.begin();it != contact.FriendsList.end();++it)
	{
		os << it->first << it->second;
	}
	return os;
	// TODO: 在此处插入 return 语句
}

istream & operator>>(istream & is, Contacts & contact)
{
	is >> contact.UserName >> contact.PassWord;

	size_t size = 0;;
	string friendName;
	friendData data;
	is >> size;//读取联系人数量
	if (!is)
	{
		cout << "联系人数量读取失败" << endl;
	}

	for (int i = 0;i < size;++i)
	{
		is >> friendName >> data;
		contact.FriendsList.insert({ friendName, data });

		if (!is)
		{
			cout << "联系人信息读取失败，联系人为：" << friendName << endl;
		}
	}

	return is;
	// TODO: 在此处插入 return 语句
}

Contacts::Contacts(string username, string password):UserName(username),PassWord(password)
{
}
