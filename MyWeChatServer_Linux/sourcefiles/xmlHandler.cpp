#include "xmlHandler.h"

xmlHandler::xmlHandler(const TiXmlElement & element)
{
	FDoc.InsertEndChild(element);
}

xmlHandler::xmlHandler(const string & kind)
{
	FDoc.InsertEndChild(TiXmlElement(kind.c_str()));
}

bool xmlHandler::isNull()
{
	return element()->NoChildren();
}

bool xmlHandler::isResult()
{
	return type()=="result";
}

bool xmlHandler::isError()
{
	return type()=="error";
}

TiXmlDocument xmlHandler::document() const
{
	return FDoc;
}

TiXmlElement* xmlHandler::element() const
{
	TiXmlElement* result = NULL;
	result = (TiXmlElement*)(FDoc.RootElement());
	return result;
}

string xmlHandler::kind() const
{
	return FDoc.RootElement()->Value();
}

xmlHandler & xmlHandler::setKind(const string & kind)
{
	// TODO: 在此处插入 return 语句
	element()->SetValue(kind.c_str());
	return *this;
}

string xmlHandler::type() const
{
	return attribute("type");
}

xmlHandler xmlHandler::setType(const string &type)
{
	setAttribute("type", type);
	return *this;
}

string xmlHandler::id() const
{
	return attribute("id");
}

xmlHandler xmlHandler::setId(const string &id)
{
	setAttribute("id", id);
	return *this;
}

string xmlHandler::to() const
{
	return attribute("to");
}

xmlHandler xmlHandler::setTo(const string &to)
{
	setAttribute("to", to);
	return *this;
}

string xmlHandler::from() const
{
	return attribute("from");
}

xmlHandler xmlHandler::setFrom(const string &from)
{
	setAttribute("from", from);
	return *this;
}

bool xmlHandler::hasAttribute(const string & name)
{
	if (FDoc.RootElement()->Attribute(name.c_str()) == nullptr)
		return false;
	else return true;
}

string xmlHandler::attribute(const string & name) const
{
	return FDoc.RootElement()->Attribute(name.c_str());
}

xmlHandler xmlHandler::setAttribute(const string & name, const string & value)
{
	FDoc.RootElement()->SetAttribute(name.c_str(), value.c_str());
	return *this;
}

TiXmlElement xmlHandler::firstElement(const string & TagName)
{
	return findElement(*element(), TagName);
}

TiXmlElement xmlHandler::addElement(const string & name)
{
	return *(FDoc.InsertEndChild(TiXmlElement(name.c_str()))->ToElement());
}

TiXmlElement xmlHandler::createElement(const string & name)
{
	return TiXmlElement(name.c_str());
}

TiXmlText xmlHandler::createTextNode(const string & data)
{
	return TiXmlText(data.c_str());
}

string xmlHandler::toString(int indent) const
{
	string tmp;
	TiXmlPrinter strPrinter;
	if (FDoc.RootElement()->Accept(&strPrinter))
	{
		return strPrinter.CStr();
	}
	else
		return NULL;
}

TiXmlElement xmlHandler::findElement(const TiXmlElement & AParent, const string & TagName)
{
	TiXmlElement tmp = *(AParent.FirstChildElement(TagName.c_str()));
	return tmp;
}
