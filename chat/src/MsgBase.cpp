#include "MsgBase.h"

MsgBase::MsgBase()
{
	getMsgBase();
}

MsgBase::~MsgBase()
{

}

void MsgBase::getMsgBase()
{
	base->clear();
	net* online = new net;
	vector<string>* servBaseMsg = new vector<string>;
	online->getMsgBase(servBaseMsg);
	for (string msgStr : *servBaseMsg)
	{
		Message newMsg = splitMsgPkg(msgStr);
		addInBase(newMsg);
	}
	delete servBaseMsg, online;
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

void MsgBase::printPers(string usrFrom, string usrTo)
{
	if (base->empty())
	{
		printEmpty();
		return;
	}
	vector<int> msgComp;
	getMsgComp(msgComp, usrFrom, usrTo);
	printMsgComp(msgComp);
}

void MsgBase::printMain()
{
	if (base->empty())
	{
		printEmpty();
		return;
	}
	vector<int> msgComp;
	getMsgComp(msgComp);
	printMsgComp(msgComp);
}

void MsgBase::printEmpty()
{
	cout << "Пока здесь еще никто ничего не писал" << endl;
}

void MsgBase::getMsgComp(vector<int>& msgComp, string msgTo)
{
	for (int i = 0; i < base->size(); i++)
	{
		if (base->at(i).msgTo == msgTo)
		{
			msgComp.push_back(i);
		}
	}
}

void MsgBase::getMsgComp(vector<int>& msgComp, string msgFrom, string msgTo)
{
	for (int i = 0; i < base->size(); i++)
	{
		if (base->at(i).msgFrom == msgFrom && base->at(i).msgTo == msgTo || base->at(i).msgFrom == msgTo && base->at(i).msgTo == msgFrom)
		{
			msgComp.push_back(i);
		}
	}
}

void MsgBase::printMsgComp(vector<int>& msgComp)
{
	if (msgComp.empty())
	{
		printEmpty();
		return;
	}
	else
	{
		for (int i = 0; i < msgComp.size(); i++)
		{
			printMsgStruct(base->at(msgComp[i]));
		}
	}
}

void MsgBase::printMsgStruct(Message& mesg)
{
	string border = "-----------------------------------------------------------------------------------------------";
	printf("%-*s %s\n%s \n %s \n", 70, mesg.msgFrom.data(), mesg.msgDate.data(), mesg.msgText.data(), border.data());
}

void MsgBase::sendMsg(string msgTo, string msgFrom, string& msg)
{
	net* online = new net;
	Message newMsg(msgTo, msgFrom, msg);
	string req = "SND_MSG<|>";
	req.append(packMsgPkg(newMsg));
	online->sendReq(req);
	delete online;
	getMsgBase();
	return;
}

string MsgBase::tagStructParam(int id, string value)
{
	string result;
	result.append(sepBeg[id]);
	result.append(value);
	result.append(sepEnd[id]);
	return result;
}
