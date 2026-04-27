#include <stdio.h>
#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")



using namespace std;

void main()
{
	//initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	
	int wsok  = WSAStartup (ver, &wsData);
	
	if(wsok != 0)
	{
		cerr << "Cant Initialize Winsock! Quitting" << endl;
		return 0;
	}
	//create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if(listening == INVALID_SOCKET)
	{
		cerr << "Can't Create Socket! Quitting" << endl;
		return 0;
	}
	
	//bind the socket to an ip address and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	
	bind(listening, hint, sizeof(hint));
	
	
	//tell winsock the socket is for listening
	
	//wait for connectuon 
	
	//close listening socket
	
	// While loop accept and echo message back to client
	
	
	//close the socket
	
	//shtutdown winsock
}
