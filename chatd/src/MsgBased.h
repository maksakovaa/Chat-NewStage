#pragma once
#include "UsrBased.h"

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
    void readMsgBase();
    void saveMsgBase();
    Message splitMsgPkg(string& msgPkg);
    string packMsgPkg(Message& msgPkg);
    void sendMsg(Message& newMsg);
    Message getMsg(int id);
    string tagStructParam(int id, string value);
private:
    string delim = "<|>";
    static const int msgAttr{ 4 }, indFr{ 0 }, indTo{ 1 }, indDat{ 2 }, indTxt{ 3 };
    string sepBeg[msgAttr] = { "<from>", "<to>", "<date>", "<text>"};
    string sepEnd[msgAttr] = { "</from>", "</to>", "</date>", "</text>" };
#if defined (_WIN32) || defined (_WIN64)
    string MBPath = "srv_msg_base.dat";
#elif defined (__linux__)
    string MBPath = "/var/lib/chatd/msg_base.dat";
#endif
};