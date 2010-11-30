#ifndef TWITTERCLIENT_H_INCLUDED
#define TWITTERCLIENT_H_INCLUDED

#include "SocketBase.h"

using namespace std;

class TwitterClient{
    public:
        TwitterClient(const char* hostIP, const unsigned short port = 3000, const unsigned int size = 140, const int af = AF_INET, const WORD version = MAKEWORD(2,0), const int type = SOCK_STREAM, const int protocol = 0);
        ~TwitterClient(void);
        void connectToServer(void);
        void sendToServer(const char* message);
        void receive(char* buffer);
        unsigned int getBufferSize(void);
        void setBufferSize(unsigned int size);

    private:
        SOCKET clientSocket;
        SOCKADDR_IN hostAddr;
        SocketBase socketCreator;
        unsigned int bufferSize;
};

#endif // CLIENT_H_INCLUDED
