/*###############################
# FH Salzburg                   #
# WS2010 MMT-B2009              #
# Multimediale Netzwerke        #
# Uebungsprojekt                #
# Fritsch Andreas, Hanli Ismail #
# Sun, 28.11.2010 22:00         #
###############################*/

#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include "SocketBase.h"

using namespace std;

class Client
{
	public:
		Client(const char* hostIP, const unsigned short port = 3000, const unsigned int size = 140, const int af = AF_INET, const WORD version = MAKEWORD(2,0), const int type = SOCK_STREAM, const int protocol = 0);
		~Client(void);
		void connectToServer(void);
		void sendToServer(const char* message);
		void receive(char* buffer);
		unsigned int getBufferSize(void);
		void setBufferSize(unsigned int size);

	private:
		SOCKET clientSocket;		// socket for client
		SOCKADDR_IN hostAddr;		// host address
		SocketBase socketCreator;
		unsigned int bufferSize;	// message size
};

#endif // CLIENT_H_INCLUDED
