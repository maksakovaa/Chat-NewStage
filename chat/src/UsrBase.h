#pragma once
#include "TmplBase.h"
#include <iomanip>
#include <new>
#include <wchar.h>

using std::setw;

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
    void getUsrBase();
    void printUsrBase();
    User splitUsrPkg(string& usrPkg);
    string packUsrPkg(User& account);
    string getUsrName(int id);
    string getUsrLogin(int id);
    int getUsrId(string& name);
    void setUsrPwd(int id, string& newPwd);
    void delUsr(int id);
    void regUsr(string& name, string& login, string& pwd);
    bool logInChk(string& login);
    bool pwdChk(int id, string& pwd);
    string tagStructParam(int id, string value);
private:
    string delim = "<|>";
    static const int usrAttr{ 3 }, indNam{ 0 }, indLogin{ 1 }, indPwd{ 2 };
    string sepBeg[usrAttr]{ "<name>", "<login>", "<pwd>" };
    string sepEnd[usrAttr] = { "</name>", "</login>", "</pwd>" };
    SHA256 sha256;
};