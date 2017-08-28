#pragma once
#ifndef _XMLHANDLER_H_
#define _XMLHANDLER_H_

#include"tinyxml.h"
#include<string>
#include<sstream>

using std::string;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
//using namespace std;

class xmlHandler
{
public:
	xmlHandler(const TiXmlElement &element);
	xmlHandler(const string &kind = "message");
	xmlHandler(const TiXmlDocument doc) :FDoc(doc) {}

	void detach();
	bool isNull();
	bool isResult();
	bool isError();
	bool isFromServer();

	TiXmlDocument document() const;
	TiXmlElement* element() const;
	string nameSpace() const;
	string kind() const;
	xmlHandler &setKind(const string &kind);
	string type() const;
	xmlHandler setType(const string &type);
	string id() const;
	xmlHandler setId(const string &id);
	string to() const;
	xmlHandler setTo(const string &to);
	string from() const;
	xmlHandler setFrom(const string &from);
	string lang() const;
	xmlHandler setLang(string &lang);

	bool hasAttribute(const string &name);
	string attribute(const string &name) const;
	xmlHandler setAttribute(const string &name, const string &value);
	TiXmlElement firstElement(const string &TagName);
	TiXmlElement addElement(const string &name);
	TiXmlElement createElement(const string &name);
	TiXmlText createTextNode(const string &data);

	string toString(int indent=-1) const;
	// toByteArray() const;

	static bool isValidXmlChar(uint32_t code);
	//static string replaceInvalidXmlChars(string &aXml,const QChar &withChar="?");
	static TiXmlElement findElement(const TiXmlElement &AParent, const string &TagName);


private:
	TiXmlDocument FDoc;
};


#endif // !_XMLHANDLER_H_
