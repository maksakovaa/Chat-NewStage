#pragma once
#include "MsgBased.h"

extern UsrBase* UserBase;
extern MsgBase* AllMsgBase;

class net
{
public:
	net();
	~net();
	void netGateway();
	void sendRequest(string& reqName);
	void sendUsrBase();
	void sendMsgBase();
	void regUser();
	void regMSG();
	void delUsr();
	void chgPwd();
    void readConfig();
    void saveConfig();
private:
	string reqName;
	string delim = "<|>";
	static const int package_length = 1024;
	char package[package_length];
	string delim_settings = " = ";
    string server_ip;
    string chat_port;
#if defined (_WIN32) || defined (_WIN64)
	WSADATA wsaData;
	int iResult;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL;
	struct addrinfo hints;
	string netCfgPath = "net_settings.ini";
#elif defined (__linux__)
	string netCfgPath = "/var/lib/chatd/net_settings.ini";
	struct sockaddr_in srvaddress, client;
	socklen_t length;
	int socket_fd, connection, bind_status, connect_status;
#endif
};