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
	// TODO: �ڴ˴����� return ���
}

istream & operator>>(istream & is, friendData & friends)
{
	is >> friends.UserName >> friends.RemarkName >> friends.IsOnline >> friends.Avatar;
	if (!is)
	{
		cout << "friendDataд��ʧ�ܣ�ʧ���û�Ϊ��" << friends.UserName << endl;
	}
	return is;
	// TODO: �ڴ˴����� return ���
}

ostream & operator<<(ostream & os, const Contacts & contact)
{
	os << contact.UserName << contact.PassWord << contact.FriendsList.size();

	for (auto it = contact.FriendsList.begin();it != contact.FriendsList.end();++it)
	{
		os << it->first << it->second;
	}
	return os;
	// TODO: �ڴ˴����� return ���
}

istream & operator>>(istream & is, Contacts & contact)
{
	is >> contact.UserName >> contact.PassWord;

	size_t size = 0;;
	string friendName;
	friendData data;
	is >> size;//��ȡ��ϵ������
	if (!is)
	{
		cout << "��ϵ��������ȡʧ��" << endl;
	}

	for (int i = 0;i < size;++i)
	{
		is >> friendName >> data;
		contact.FriendsList.insert({ friendName, data });

		if (!is)
		{
			cout << "��ϵ����Ϣ��ȡʧ�ܣ���ϵ��Ϊ��" << friendName << endl;
		}
	}

	return is;
	// TODO: �ڴ˴����� return ���
}

Contacts::Contacts(string username, string password):UserName(username),PassWord(password)
{
}
