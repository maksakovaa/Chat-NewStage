#include "MsgBased.h"

MsgBase::MsgBase()
{
	readMsgBase();
}

MsgBase::~MsgBase()
{
	saveMsgBase();
}

void MsgBase::readMsgBase()
{
	std::ifstream msgbase_file(MBPath);
	if (msgbase_file.is_open())
	{
		string s;
		while (getline(msgbase_file, s))
		{
			base->push_back(splitMsgPkg(s));
		}
		msgbase_file.close();
	}
}

void MsgBase::saveMsgBase()
{
	std::ofstream msgbase_file(MBPath, std::ios::trunc);
	if (!msgbase_file.is_open())
	{
		cout << "Ошибка открытия файла!!" << endl;
	}
	else
	{
		for (Message newMsg: *base)
		{
			msgbase_file << packMsgPkg(newMsg);
			msgbase_file << "\n";
		}
		msgbase_file.close();
	}
}

Message MsgBase::splitMsgPkg(string& msgPkg)
{
	string s[msgAttr];
	for (int i = 0; i < msgAttr; i++)
	{
		s[i] = msgPkg.substr(msgPkg.find(sepBeg[i]) + sepBeg[i].length(), msgPkg.find(sepEnd[i]) - sepBeg[i].length());
		msgPkg.erase(0, msgPkg.find(sepEnd[i]) + sepEnd[i].length());
	}
	Message newMsg(s[0], s[1], s[2], s[3]);
	return newMsg;
}

string MsgBase::packMsgPkg(Message& msgPkg)
{
	string result;
	result.append(tagStructParam(indFr, msgPkg.msgFrom));
	result.append(tagStructParam(indTo, msgPkg.msgTo));
	result.append(tagStructParam(indDat, msgPkg.msgDate));
	result.append(tagStructParam(indTxt, msgPkg.msgText));
	return result;
}

void MsgBase::sendMsg(Message& newMsg)
{
	addInBase(newMsg);
	saveMsgBase();
}

Message MsgBase::getMsg(int id)
{
	Message temp = base->at(id);
	return temp;
}

string MsgBase::tagStructParam(int id, string value)
{
	string result;
	result.append(sepBeg[id]);
	result.append(value);
	result.append(sepEnd[id]);
	return result;
}
