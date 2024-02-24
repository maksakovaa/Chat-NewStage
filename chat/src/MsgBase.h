#pragma once
#include "UsrBase.h"

struct Message
{
    string msgFrom;
    string msgTo;
    string msgDate;
    string msgText;
    Message(string _msgFrom, string _msgTo, string _msgText) : msgFrom(_msgFrom), msgTo(_msgTo), msgText(_msgText)
    {
        msgDate = curDateTime();
    }
    Message(string _msgFrom, string _msgTo, string _msgDate, string _msgText) : msgFrom(_msgFrom), msgTo(_msgTo), msgDate(_msgDate), msgText(_msgText) {}
};

class MsgBase: public Base<Message>
{
public:
	MsgBase();
	~MsgBase();
	void getMsgBase();
    Message splitMsgPkg(string& msgPkg);
    string packMsgPkg(Message& msgPkg);
    void printPers(string usrFrom, string usrTo);
    void printMain();
    void printEmpty();
    void getMsgComp(vector<int>& msgComp, string msgTo = "ALL");
    void getMsgComp(vector<int>& msgComp, string msgFrom, string msgTo);
    void printMsgComp(vector<int>& msgComp);
	void printMsgStruct(Message& mesg);
    void sendMsg(string msgTo, string msgFrom, string& msg);
    string tagStructParam(int id, string value);
private:
    string delim = "<|>";
    static const int msgAttr{ 4 }, indFr{ 0 }, indTo{ 1 }, indDat{ 2 }, indTxt{ 3 };
    string sepBeg[msgAttr] = {"<from>", "<to>", "<date>", "<text>"};
    string sepEnd[msgAttr] = { "</from>", "</to>", "</date>", "</text>" };
};