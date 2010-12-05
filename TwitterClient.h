/*###############################
# FH Salzburg                   #
# WS2010 MMT-B2009              #
# Multimediale Netzwerke        #
# Uebungsprojekt                #
# Fritsch Andreas, Hanli Ismail #
# Sun, 28.11.2010 22:00         #
###############################*/

#ifndef TWITTERCLIENT_H_INCLUDED
#define TWITTERCLIENT_H_INCLUDED

#include <iostream>
#include <string>
#include <conio.h>
#include "SocketBase.h"
#include "ExceptionTexter.h"

#define BUFFERSIZE 140

using namespace std;

class TwitterClient{
    public:
        TwitterClient(const char* hostIP, const unsigned short port = 3000);
        ~TwitterClient(void);
        void connectToServer(void);
        void serverListener(void);

	private:
		SOCKET clientSocket;
		SOCKADDR_IN hostAddr;
		SocketBase socketCreator;

		void sendToServer(const char* message);
        void receive(char* buffer);
};

#endif // CLIENT_H_INCLUDED
