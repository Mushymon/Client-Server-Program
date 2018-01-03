#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	char *closeclient = "closeclient\r";

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0){
		printf("WSAStartup failed with error: %\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0){
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET){
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR){
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR){
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Recieve until the peer shuts down the connection
	do {
		if (ClientSocket == INVALID_SOCKET){
			ClientSocket = accept(ListenSocket, NULL, NULL);
		}
		if (ClientSocket != INVALID_SOCKET){
			iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0){
				if (recvbuf[0] != '0'){
					printf("Message: ");
					for (int i = 0; i < iResult - 1; i++){
						printf("%c", recvbuf[i]);
					}
					printf("\nBytes received: %d\n", iResult);
				}

				// Echo the buffer back to the sender
				if (recvbuf[0] == '0'){
					iSendResult = send(ClientSocket, closeclient, 11, 0);
				}
				else{
					iSendResult = send(ClientSocket, recvbuf, iResult, 0);
				}
				if (iSendResult == SOCKET_ERROR){
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				}

				if (recvbuf[0] == '0'){
					ClientSocket = INVALID_SOCKET;
				}
				else if (strstr(recvbuf, "shutdown") != NULL){
					break;
				}
				else{
					printf("Bytes sent: %d\n", iSendResult);
				}
			}
		}
	} while (1);

	// Shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR){
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// Cleanup
	closesocket(ListenSocket);
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}