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

		FD_ZERO(&actionFlag);
		FD_SET(clientSocket, &actionFlag);
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

	errorCode = connect(clientSocket, (SOCKADDR*) &hostAddr, sizeof(SOCKADDR));		// connecting

	if(errorCode == SOCKET_ERROR)					// error handling
		throw "\nFAIL: Connecting failed!";

	else
		printf("\nSUCCESS: Connected to %s!", inet_ntoa(hostAddr.sin_addr));

}

void TwitterClient::serverListener(void)
{
	int errorCode;

	errorCode = select(1, &actionFlag, NULL, NULL, 0);

	if(errorCode == SOCKET_ERROR)							// check for error
		throw exceptionTexter("\nFAIL: Something went wrong with SELECT! (Error Code: ", errorCode);

	if(FD_ISSET(clientSocket, &actionFlag))
	{
		try
		{
			while(true)
			{
				receive(message);

				if(!strcmp("ETX", message))
				{
					break;
				}

				printf("%s", message);
				//printf("\n%d\n", foo);
			}
			//receive(message);

		}
		catch(string failure)
		{
			printf("%s", failure.c_str());

			closesocket(clientSocket);
			closesocket(serverSocket);
			FD_ZERO(&actionFlag);
			FD_SET(clientSocket, &actionFlag);
		}
	}
//	else
//	{
		try
		{
			printf("\n>");
			getline(cin, input);
			sendToServer(input.c_str());
		}
		catch(string failure)
		{
			printf("%s", failure.c_str());
		}

//	}

//	FD_ZERO(&actionFlag);
//	FD_SET(clientSocket, &actionFlag);
}

void TwitterClient::sendToServer(const char* message)
{
    int errorCode;

	errorCode = send(clientSocket, message, bufferSize, 0);	// sending

	if(errorCode == SOCKET_ERROR)							// error handling
		throw "\nFAIL: Unable to send message!";

}

void TwitterClient::receive(char* buffer)
{
    int errorCode;

	errorCode = recv(clientSocket, buffer, bufferSize, 0);	// receiving

	if(errorCode == 0)										// error handling
		throw "\nFAIL: Lost connection to server!";

	else if(errorCode == SOCKET_ERROR)
		throw "\nFAIL: Unable to receive message!";

}

unsigned int TwitterClient::getBufferSize(void){ return bufferSize; }

void TwitterClient::setBufferSize(unsigned int size){ bufferSize = size; }
