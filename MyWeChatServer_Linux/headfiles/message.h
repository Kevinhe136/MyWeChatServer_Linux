#pragma once
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include"xmlHandler.h"
#include<list>
//#include<QVariant>

//using namespace std;

#define MESSAGE_TYPE_NORMAL "normal"
#define MESSAGE_TYPE_CHAT "chat"
#define MESSAGE_TYPE_GROUPCHAT "groupchat"
#define MESSAGE_TYPE_HEADLINE "headline"
#define STANZA_TYPE_ERROR "error"

class Message
{
public:
	xmlHandler *Stanza;
	//QHash<int, QVariant> FData;

public:
	enum MessageType {
		Noraml = 0x01,
		Chat = 0x02,
		GroupChat = 0x04,
		HeadLine = 0x08,
		Error = 0x10
	};

public:

	Message();
	Message(const xmlHandler &stanza);
	xmlHandler &stanza() const;
	//const xmlHandler &stanza() const;
	MessageType type() const;
	Message &setType(MessageType type);
	string id() const;
	/*Message &setRandomId() const;*/
	Message &setId(const string id);
	string to() const;
	Message &setTo(string to);
	string from() const;
	Message &setFrom(string from);
	/*string deflang() const;
	Message &setDefLang(string lang);*/
	//list<string> subjectLang() const;
	/*string subject() const;
	Message &setSubject(const string subject);
	string bodyLangs() const;*/
	string body() const;
	Message &setBody(const string body);
	string result() const;
	Message &setResult(const string result);
	string userName() const;
	Message &setUserName(const string userName);
	string password() const;
	Message &setPassword(const string password);
	/*string threadId() const;
	Message &setThreadId(const string threadId);*/
	//QVariant data(int role) const;
	//void setData(int role, const QVariant data);
	//void setData(const QHash<int, QVariant> data);
	//QStringList availableLangs(const TiXmlElement &Aparent, const string tagName) const;
	//TiXmlElement findChildByLang(const TiXmlElement &Aparent, const string &tagName, const string &lang) const;
	TiXmlElement findChild(const TiXmlElement *Aparent, const string &tagName) const;
	//TiXmlElement addChildByLang(const TiXmlElement &Aparent, const string &tagName, const string &lang, const string &text);
	TiXmlElement addChild(TiXmlElement *Aparent, const string &tagName, const string &text);

protected:
	TiXmlElement setTextToElem(TiXmlElement &elem, const string text) const;
};


#endif // !_MESSAGE_H_
