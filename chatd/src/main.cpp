#include "netd.h"

UsrBase* UserBase = new UsrBase;
MsgBase* AllMsgBase = new MsgBase;

int main()
{
#if defined (_WIN32) || defined (_WIN64)
    SetConsoleOutputCP(65001);
    SetConsoleCP(1251);
    system("cls");
#elif defined (__linux__)
    setlocale(LC_ALL, "ru_RU.utf8");
    system("clear");
#endif
    net* online = new net;
    online->netGateway();

    delete online, AllMsgBase, UserBase;
    return 0;
}