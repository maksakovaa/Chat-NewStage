#pragma once
#include "TmplBased.h"

struct User
{
    string name;
    string login;
    string pwd;
    User(string newName, string newLogin, string newPwd) : name(newName), login(newLogin), pwd(newPwd) {}
};

class UsrBase: public Base<User>
{
public:
	UsrBase();
	~UsrBase();
    void readUsrBase();
    void saveUsrBase();
    User splitUsrPkg(string& usrPkg);
    User getUser(int id);
    string packUsrPkg(User& account);
    void regUser(User& account);
    void delUser(int id);
    void chgPwd(int id, string& pwd);
    string tagStructParam(int id, string value);
private:
    string delim = "<|>";
    static const int usrAttr{ 3 }, indNam{ 0 }, indLogin{ 1 }, indPwd{ 2 };
    string sepBeg[usrAttr]{ "<name>", "<login>", "<pwd>" };
    string sepEnd[usrAttr] = { "</name>", "</login>", "</pwd>" };
    SHA256 sha256;
#if defined (_WIN32) || defined (_WIN64)
    string UBPath = "srv_users.dat";
#elif defined (__linux__)
    string UBPath = "/var/lib/chatd/users.dat";
#endif
};