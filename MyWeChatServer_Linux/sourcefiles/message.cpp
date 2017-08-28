#include "message.h"

Message::Message()
{
}

Message::Message(const xmlHandler & stanza)
{
	Stanza = new xmlHandler(stanza);
}

Message::MessageType Message::type() const
{
	if (Stanza->type() == MESSAGE_TYPE_CHAT) return Message::Chat;
	if (Stanza->type() == MESSAGE_TYPE_GROUPCHAT) return Message::GroupChat;
	if (Stanza->type() == MESSAGE_TYPE_HEADLINE) return Message::HeadLine;
	if (Stanza->type() == STANZA_TYPE_ERROR) return Message::Error;
	return Message::Noraml;
}

Message &Message::setType(MessageType type)
{
	switch (type)
	{
	case Message::Chat:
		Stanza->setType(MESSAGE_TYPE_CHAT);
		break;
	case Message::GroupChat:
		Stanza->setType(MESSAGE_TYPE_GROUPCHAT);
		break;
	case Message::HeadLine:
		Stanza->setType(MESSAGE_TYPE_HEADLINE);
		break;
	case Message::Error:
		Stanza->setType(STANZA_TYPE_ERROR);
		break;
	}
	return *this;
}

string Message::id() const
{
	return Stanza->id();
}

//Message &Message::setRandomId() const
//{
//    Stanza->setId(QU)
//}

Message &Message::setId(const string id)
{
	Stanza->setId(id);
	return *this;
}

string Message::to() const
{
	return Stanza->to();
}

Message &Message::setTo(string to)
{
	Stanza->setTo(to);
	return *this;
}

string Message::from() const
{
	return Stanza->from();
}

Message &Message::setFrom(string from)
{
	Stanza->setFrom(from);
	return *this;
}

string Message::body() const
{
	return findChild(Stanza->element(), "body").GetText();
}

Message &Message::setBody(const string body)
{
	addChild(Stanza->element(), "body", body);
	return *this;
}

string Message::result() const
{
	return findChild(Stanza->element(), "result").GetText();
}

Message &Message::setResult(const string result)
{
	addChild(Stanza->element(), "result", result);
	return *this;
}

string Message::userName() const
{
	return findChild(Stanza->element(), "username").GetText();
}

Message &Message::setUserName(const string userName)
{
	addChild(Stanza->element(), "username", userName);
	return *this;
}

string Message::password() const
{
	return findChild(Stanza->element(), "password").GetText();
}

Message &Message::setPassword(const string password)
{
	addChild(Stanza->element(), "password", password);
	return *this;
}

TiXmlElement Message::findChild(const TiXmlElement * Aparent, const string & tagName) const
{
	TiXmlElement elem = *(Aparent->FirstChildElement(tagName.c_str()));
	return elem;
}

TiXmlElement Message::addChild(TiXmlElement * Aparent, const string & tagName, const string & text)
{
	TiXmlElement elem(tagName.c_str());
	TiXmlText elemText(text.c_str());
	elem.InsertEndChild(elemText);
	Aparent->InsertEndChild(elem);
	return elem;
}
