#include"Socket.h"
#include"stdio.h"

void main()
{
	printf("hello word\r\n");
	Socket Chat(4321);
	while (1)
	{
		Chat.Socket_ServerTask();
	}
	
	
}