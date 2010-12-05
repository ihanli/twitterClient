/*###############################
# FH Salzburg                   #
# WS2010 MMT-B2009              #
# Multimediale Netzwerke        #
# Uebungsprojekt                #
# Fritsch Andreas, Hanli Ismail #
# Sun, 28.11.2010 22:00         #
###############################*/

#include "TwitterClient.h"

TwitterClient::TwitterClient(const char* hostIP, const unsigned short port, unsigned int size, const int af, const WORD version, const int type, const int protocol) :
               socketCreator(version, type, protocol), bufferSize(size)
{
	try
	{
		memset(&hostAddr, 0, sizeof(SOCKADDR_IN));
		hostAddr.sin_family = af;						// set host address
		hostAddr.sin_port = htons(port);
		hostAddr.sin_addr.s_addr = inet_addr(hostIP);

		socketCreator.createSocket(&clientSocket, af);	// try to create clientsocket
	}
	catch(unsigned char* e)
	{
		printf("%c", *e);
	}
}

TwitterClient::~TwitterClient(void)
{
    closesocket(clientSocket);
    WSACleanup();
}

void* listenThread(void* arg);

struct threadParam
{
	TwitterClient* client;
	SOCKET socket;
};

void TwitterClient::connectToServer(void)
{

	int errorCode;

	printf("\nConnecting to host...");

	errorCode = connect(clientSocket, (SOCKADDR*) &hostAddr, sizeof(SOCKADDR));		// connecting

	if(errorCode == SOCKET_ERROR)					// error handling
		throw "\nFAIL: Connecting failed!";

	else
	{
		printf("\nSUCCESS: Connected to %s!", inet_ntoa(hostAddr.sin_addr));
		printf("\n>");
		getline(cin, input);
		sendToServer(input.c_str());
	}
}

void* listenThread(void* arg)
{
	pthread_detach(pthread_self());

	threadParam threadArg = *((threadParam*) arg);
	free(arg);

	char message[140];
	string input;

	try
	{
		while(true)
		{
			threadArg.client->receive(message);

			if(!strcmp("ETX", message))
			{
				getline(cin, input);
				threadArg.client->sendToServer(input.c_str());
				break;
			}

			printf(">%s", message);
			printf(">");
		}
	}
	catch(const char* failure)
	{
		closesocket(threadArg.socket);
		printf("%s", failure);
	}

	return NULL;
}

void TwitterClient::serverListener(void)
{
	pthread_t pid;
	threadParam classPointer;

	classPointer.client = this;
	classPointer.socket = clientSocket;

	pthread_create(&pid, NULL, &listenThread, &classPointer);
}

void TwitterClient::sendToServer(const char* message)
{
    int errorCode;

	errorCode = send(clientSocket, message, bufferSize, 0);

	if(errorCode == SOCKET_ERROR)
	{
		throw "\nFAIL: Unable to send message!";
	}
}

void TwitterClient::receive(char* buffer)
{
    int errorCode;

	errorCode = recv(clientSocket, buffer, bufferSize, 0);

	if(errorCode == 0)
	{
		throw "\nFAIL: Lost connection to server!";
	}
	else if(errorCode == SOCKET_ERROR)
	{
		throw "\nFAIL: Unable to receive message!";
	}
}

unsigned int TwitterClient::getBufferSize(void){ return bufferSize; }

void TwitterClient::setBufferSize(unsigned int size){ bufferSize = size; }
