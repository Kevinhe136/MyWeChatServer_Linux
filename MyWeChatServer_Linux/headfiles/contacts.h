#pragma once
#ifndef _CONTACTS_H_
#define _CONTACTS_H_

#include<string>
#include<unordered_map>
#include<iostream>
#include<map>
using std::string;
using std::unordered_map;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

//using namespace std;

class friendData
{
public:
	friendData();
	friendData(string username, string remarkName, bool isOnline);
	string UserName;
	bool IsOnline = false;
	string RemarkName;
	string Avatar;
};
ostream &operator<<(ostream &os, const friendData &friends);
istream &operator>>(istream &is, friendData &friends);

class Contacts
{
public:
	Contacts() {}
	Contacts(string username, string password);

	string UserName;
	string PassWord;
	unordered_map<string, friendData> FriendsList;

};
//QDataStream &operator<<(QDataStream &os,map<string,friendData> &friends);
//QDataStream &operator>>(QDataStream &is,map<string,friendData> &friends);

ostream &operator<<(ostream &os, const Contacts &contact);//IO运算符必须定义为类的非成员函数，具体原因见c++primer 494页
istream &operator>>(istream &is, Contacts &contact);



#endif // !_CONTACTS_H_
