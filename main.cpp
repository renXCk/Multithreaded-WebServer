#define _WIN32_WINNT 0x0600 

#include <stdio.h>
#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")



using namespace std;

int main()
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

	bind(listening, (sockaddr*)&hint, sizeof(hint));
		
	//tell winsock the socket is for listening
	listen(listening, SOMAXCONN);
	
	//wait for connectuon 
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	
	if(clientSocket == INVALID_SOCKET)
	{
		cerr << "Error! Invalid Socket" << endl;
		return 0;
	}
	
	char host[NI_MAXHOST]; //client's remote name
	char service[NI_MAXHOST]; //port the client is conncected on
	
	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);
	
					//lookup host name of the client connected to 
	if(getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << "Host Connected on Port " << service << endl;
	}
	else{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << "Host Connect on Port " << ntohs(client.sin_port) << endl;
	}
	
	//close listening socket
	closesocket(listening);
	
	// While loop accept and echo message back to client
	char buffer[4096];
	
	while(true)
	{
		ZeroMemory(buffer, 4096);
		
		//wait for client to send data
		int bytesReceived = recv(clientSocket, buffer, 4096, 0);
		if(bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv()! Quitting!" << endl;
			break;
		}
		else if ( bytesReceived == 0)
		{
			cout << "Client Disconnected" << endl;
			break;
		}
			//exho message back to client
		send(clientSocket, buffer, bytesReceived + 1, 0);
		
	}
	
	

	//close the socket
	closesocket(clientSocket);
	
	//shtutdown winsock
	WSACleanup();
}
