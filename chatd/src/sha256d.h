#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <new>
#include <fstream>
#include <wchar.h>
#include <string>
#include <ctime>
#if defined (_WIN32) || defined (_WIN64)
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment (lib, "Ws2_32.lib")
#include <string.h>
#define bzero(b,len) (memset((b), '0', (len)), (void) 0)
#pragma warning(disable : 4996)
#elif defined (__linux__)
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#ifdef _MSC_VER
typedef unsigned __int8  uint8_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

string curDateTime();

class SHA256
{
public:
    enum { BlockSize = 512 / 8, HashBytes = 32 };
    SHA256();
    std::string operator()(const void* data, size_t numBytes);
    std::string operator()(const std::string& text);
    void add(const void* data, size_t numBytes);
    std::string getHash();
    void        getHash(unsigned char buffer[HashBytes]);
    void reset();

private:
    void processBlock(const void* data);
    void processBuffer();
    uint64_t m_numBytes;
    size_t   m_bufferSize;
    uint8_t  m_buffer[BlockSize];
    enum { HashValues = HashBytes / 4 };
    uint32_t m_hash[HashValues];
};