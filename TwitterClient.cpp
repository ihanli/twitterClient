/*###############################
# FH Salzburg                   #
# WS2010 MMT-B2009              #
# Multimediale Netzwerke        #
# Uebungsprojekt                #
# Fritsch Andreas, Hanli Ismail #
# Sun, 28.11.2010 22:00         #
###############################*/

#include "TwitterClient.h"

TwitterClient::TwitterClient(const char* hostIP, const unsigned short port) :
               socketCreator()
{
	try
	{
		memset(&hostAddr, 0, sizeof(SOCKADDR_IN));
		hostAddr.sin_family = AF_INET;
		hostAddr.sin_port = htons(port);
		hostAddr.sin_addr.s_addr = inet_addr(hostIP);

		socketCreator.createSocket(&clientSocket, AF_INET);
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

void TwitterClient::connectToServer(void)
{

	int errorCode;

	printf("\nConnecting to host...");

	errorCode = connect(clientSocket, (SOCKADDR*) &hostAddr, sizeof(SOCKADDR));

	if(errorCode == SOCKET_ERROR)
		throw "\nFAIL: Connecting failed!";

	else
	{
		printf("\nSUCCESS: Connected to %s!\n", inet_ntoa(hostAddr.sin_addr));
	}
}

void TwitterClient::serverListener(void)
{
	char message[BUFFERSIZE];
	string input;

	if(kbhit())
	{
		printf(">");
		getline(cin, input);
		sendToServer(input.c_str());

		while(true)
		{
			receive(message);

			if(!strcmp("ETX", message))
			{
				break;
			}

			printf(">%s", message);
		}
	}
}

void TwitterClient::sendToServer(const char* message)
{
    int errorCode;

	errorCode = send(clientSocket, message, BUFFERSIZE, 0);

	if(errorCode == SOCKET_ERROR)
	{
		throw "\nFAIL: Unable to send message!";
	}
}

void TwitterClient::receive(char* buffer)
{
    int errorCode;

	errorCode = recv(clientSocket, buffer, BUFFERSIZE, 0);

	if(errorCode == 0)
	{
		throw "\nFAIL: Lost connection to server!";
	}
	else if(errorCode == SOCKET_ERROR)
	{
		throw "\nFAIL: Unable to receive message!";
	}
}