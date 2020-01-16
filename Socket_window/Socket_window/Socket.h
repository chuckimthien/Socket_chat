#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#include"stdio.h"
#include "stdint.h"
#include "Winsock2.h"
#include "Ws2tcpip.h"


#pragma comment(lib,"ws2_32.lib") //Winsock Library

class Socket
{
private:
    char dstData[1234];
    char dstAddr[1234];
    WSADATA wsa;
    SOCKET s1;
    SOCKET s2;
    struct sockaddr_in server;
    char* message;
public: void Socket_client(char* ip_server, u_short port, char* data_send);
        Socket(u_short port);
        int Socket_Send(char* data, uint16_t size);
        int Socket_Recv(char* src, uint16_t size);
        void Socket_ServerTask();
        char* getDirAddr(char* buff);
        char*getDirData(char*buff);
};

 