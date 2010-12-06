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
		memset(&hostAddr, 0, sizeof(SOCKADDR_IN));		// reset the host address to zero
		hostAddr.sin_family = AF_INET;					// set the protocol, tcp/ip in this case
		hostAddr.sin_port = htons(port);				// set the port
		hostAddr.sin_addr.s_addr = inet_addr(hostIP);	// set the ip-address

		socketCreator.createSocket(&clientSocket, AF_INET);		// finally create the socket
	}
	catch(unsigned char* e)
	{
		printf("%c", *e);
	}
}

TwitterClient::~TwitterClient(void)
{
	closesocket(clientSocket);		// close the client socket and cleanup
	WSACleanup();
}

void TwitterClient::connectToServer(void)
{

	int errorCode;

	printf("\nConnecting to host...");

	// connect to the server by giving the socket, address and size of the address
	errorCode = connect(clientSocket, (SOCKADDR*) &hostAddr, sizeof(SOCKADDR));

	if(errorCode == SOCKET_ERROR)
		throw "\nFAIL: Connecting failed!";

	else
		printf("\nSUCCESS: Connected to %s!\n", inet_ntoa(hostAddr.sin_addr));
}

void TwitterClient::serverListener(void)
{
	char message[BUFFERSIZE];
	string input;

	// dirty, kbhit is deprecated. we use it to switch mode from listen
	// to enter and vice versa.
	if(kbhit())
	{
		printf(">");							// await user tweet
		getline(cin, input);
		sendToServer(input.c_str());			// send it

		while(true)
		{
			receive(message);					// receive

			if(!strcmp("ETX", message))
				break;

			printf(">%s", message);
		}
	}
}

void TwitterClient::sendToServer(const char* message)
{
	int errorCode;

	// send the message to the server by giving the client socket, message and size
	errorCode = send(clientSocket, message, BUFFERSIZE, 0);

	if(errorCode == SOCKET_ERROR)
		throw "\nFAIL: Unable to send message!";
}

void TwitterClient::receive(char* buffer)
{
	int errorCode;

	// receive messages also by giving the client socket, message and size
	errorCode = recv(clientSocket, buffer, BUFFERSIZE, 0);

	if(errorCode == 0)
		throw "\nFAIL: Lost connection to server!";

	else if(errorCode == SOCKET_ERROR)
		throw "\nFAIL: Unable to receive message!";
}