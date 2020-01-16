#include"Socket.h"
#include"stdio.h"


   
	void Socket::Socket_client(char* ip_server, u_short port, char* data_send)
	{
		printf(" \nInitialising Winsock... ");
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf(" Failed.Error Code : % d ", WSAGetLastError());
		}

		printf(" Initialised.\n ");

		//Create a socket
		if ((s2 = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		{
			printf("Could not create socket : % d", WSAGetLastError());
		}

		printf(" Socket created.\n ");

		server.sin_addr.s_addr = inet_addr(ip_server);

		server.sin_family = AF_INET;
		server.sin_port = htons(port);
		

		//Connect to remote server
		if (connect(s2, (struct sockaddr*) & server, sizeof(server)), 0)
		{
			puts("connect error");
		}

		puts("Connected");
		send(s2, dstData, strlen(dstData), NULL);
		
	}
	Socket::Socket(u_short port)
	{
		printf(" \nInitialising Winsock... ");
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf(" Failed.Error Code : % d ", WSAGetLastError());
		
		}

		printf(" Initialised.\n ");

		//Create a socket
		if ((s1 = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		{
			printf("Could not create socket : % d", WSAGetLastError());
		}

		printf(" Socket created.\n ");

		server.sin_addr.s_addr = htonl(INADDR_ANY);
		server.sin_family = AF_INET;
		server.sin_port = htons(port);

		bind(s1, (struct sockaddr*) & server, sizeof(struct sockaddr));

		listen(s1, 5);
		
	}

	int Socket::Socket_Send(char* data, uint16_t size)
	{
		return send(s2, data, size, 0);
	}

	int Socket::Socket_Recv(char* src, uint16_t size)
	{
		return recv(s2, src, size, 0);
	}

	void Socket::Socket_ServerTask()
	{
		SOCKET clientSocket = INVALID_SOCKET;
		sockaddr_in client;
		int lenClient = sizeof(client);
		clientSocket = accept(s1, (sockaddr*)&client, &lenClient);
		printf("Client:\r\n");
		printf("\tAddr:%s\r\n", inet_ntoa(client.sin_addr));
		printf("\tPort:%d\r\n", client.sin_port);
		int temp = 0;
		char buff[1024];
		memset(buff, 0, sizeof(buff));
		int timeout = 0;
		
		while (temp == 0)
		{
			temp = recv(clientSocket, buff, sizeof(buff), NULL);
			Sleep(100);
			if (timeout++ > 100)
			break;
		}
		
		char* msg = NULL;
		if (temp > 0)
		{
			msg = (char*)"server: da nhan thanh cong data\r\n";
			printf("ip of client: %s\r\n", getDirAddr(buff));
			printf("data from client: %s\r\n", getDirData(buff));
			SOCKET dstSocket = INVALID_SOCKET;
			struct sockaddr_in dstAddr;

			//dstAddr.sin_addr.s_addr = inet_addr(GetDiraddr(buff));
			//dstAddr.sin_family = AF_INET;
			//dstAddr.sin_port = htons(2222);
			//creat a socket
			if ((dstSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
			{
				printf("Could not creat socket: %d\r\n", WSAGetLastError());
			}
		}
		Socket::Socket_client(dstAddr, 1234,dstData);
		closesocket(s2);
	}
	char* Socket::getDirAddr(char* buff)
	{
		memset(dstAddr, 0, sizeof(dstAddr));
		char* key = (char*)"Dst";
		char* startAddr = strstr(buff, key) + strlen(key)+3;
		int index = 0;
		
		//char temp = 0;
		/*char step = 0;
		while (step < 2)
		{
			switch (step)
			{
			case 0:
					if (buff[index] == '"')
					{
						step = 1;
					}
					break;
			case 1:
				if (buff[index] != '"')
				{
					memcpy(dstAddr + temp++, buff + index, 1);
				}
				else
				{
					step = 2;
				}
				break;
			case 2: 
				if (buff[index] == '"')
					break;
				}
			printf("Addr:%s\r\n", &dstAddr);
		}*/
		while (1)
		{
			if (*(startAddr + index) == '"')
			{
				break;
			}
			memcpy(dstAddr + index, startAddr + index, 1);
			index++;
			
		}
		return dstAddr;
	}

	char* Socket::getDirData(char* buff)
	{
		memset(dstData, 0, sizeof(dstData));
		char* key2 = (char*)"Data";
		char* startData = strstr(buff, key2) + strlen(key2) + 3;
		int index2 = 0;
		while (1)
		{
			if (*(startData + index2) == '"')
			{
				break;
			}
			memcpy(dstData + index2, startData + index2, 1);
			index2++;
		}
		return dstData;
	}


