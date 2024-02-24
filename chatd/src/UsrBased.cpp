#include "UsrBased.h"

UsrBase::UsrBase()
{
    readUsrBase();
}

UsrBase::~UsrBase()
{
    saveUsrBase();
}

void UsrBase::readUsrBase()
{
    std::ifstream userbase_file(UBPath);
    if (!userbase_file.is_open())
    {
        User admin("Administrator", "admin", sha256("admin2023"));
        addInBase(admin);
    }
    if (userbase_file.is_open())
    {
        string s;
        while (getline(userbase_file, s))
        {
            base->push_back(splitUsrPkg(s));
        }
        userbase_file.close();
    }
}

void UsrBase::saveUsrBase()
{
    std::ofstream userbase_file(UBPath, std::ios::trunc);
    if (!userbase_file.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
    }
    else
    {
        for (User account: *base)
        {
            userbase_file << packUsrPkg(account);
            userbase_file << "\n";
        }
        userbase_file.close();
    }
}

User UsrBase::splitUsrPkg(string& usrPkg)
{
    string s[usrAttr];
    for (int i = 0; i < usrAttr; i++)
    {
        s[i] = usrPkg.substr(usrPkg.find(sepBeg[i]) + sepBeg[i].length(), usrPkg.find(sepEnd[i]) - sepBeg[i].length());
        usrPkg.erase(0, usrPkg.find(sepEnd[i]) + sepEnd[i].length());
    }
    User newUser(s[0], s[1], s[2]);
    return newUser;
}

User UsrBase::getUser(int id)
{
    return base->at(id);
}

string UsrBase::packUsrPkg(User& account)
{
    string result;
    result.append(tagStructParam(indNam, account.name));
    result.append(tagStructParam(indLogin, account.login));
    result.append(tagStructParam(indPwd, account.pwd));
    return result;
}

void UsrBase::regUser(User& account)
{
    base->push_back(account);
    saveUsrBase();
}

void UsrBase::delUser(int id)
{
    base->erase(base->begin() + id);
    saveUsrBase();
}

void UsrBase::chgPwd(int id, string& pwd)
{
    base->at(id).pwd = pwd;
    saveUsrBase();
}

string UsrBase::tagStructParam(int id, string value)
{
    string result;
    result.append(sepBeg[id]);
    result.append(value);
    result.append(sepEnd[id]);
    return result;
}
