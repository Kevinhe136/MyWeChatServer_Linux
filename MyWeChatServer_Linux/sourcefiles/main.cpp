#include"message.h"
#include<iostream>
#include"MyEpollPort.h"
#include"accountDatabase.h"

using std::cout;
int main()
{
	//string result;

	//Message message;
	//message.Stanza = new xmlHandler((string)"Test");
	//
	//message.setUserName("HeWenKai");
	//message.setPassword("FanHengXin");
	//result = message.Stanza->toString();
	//cout << result;

	myEpollServer *model = new myEpollServer(8000);
	model->start();

	//accountDatabase account;
	//account.initDatabase();
	//account.getAccount();
	//unordered_map<string, string> result;
	//result = account.showAccount();
	//for (auto i = result.begin();i != result.end();++i)
	//{
	//	cout << i->first << "  " << i->second << endl;
	//}

	////account.deleteFriend("hewenkai","xiaoli");

	//account.setStatus("hewenkai", "fanhengxin", false);

	//unordered_map<string, friendData> friendList;
	//friendList = account.getFriends("hewenkai");
	//for (auto i = friendList.begin();i != friendList.end();++i)
	//{
	//	cout << i->first << "  " << i->second.RemarkName <<"  "<< i->second.IsOnline << endl;
	//}

	//account.setFriendRemark("hewenkai", "fanhengxin", "mylove");

	//result = account.showAccount();
	//for (auto i = result.begin();i != result.end();++i)
	//{
	//	cout << i->first << "  " << i->second << endl;
	//}

	while (1);
	return 0;
}
