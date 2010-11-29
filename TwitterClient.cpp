#include "Client.h"

Client::Client(const char* hostIP, const unsigned short port, unsigned int size, const int af, const WORD version, const int type, const int protocol) :
               socketCreator(version, type, protocol), bufferSize(size)
{
    memset(&hostAddr, 0, sizeof(SOCKADDR_IN));
    hostAddr.sin_family = af;
    hostAddr.sin_port = htons(port);
    hostAddr.sin_addr.s_addr = inet_addr(hostIP);

    try{
        socketCreator.createSocket(&clientSocket, af);
    }
    catch(unsigned char* e){
        printf("%c", *e);
    }
}

Client::~Client(void){
    closesocket(clientSocket);
    WSACleanup();
}

void Client::connectToServer(void){
    int errorCode;

    printf("\nConnecting to host...");

    errorCode = connect(clientSocket, (SOCKADDR*) &hostAddr, sizeof(SOCKADDR));

    if(errorCode == SOCKET_ERROR){
        throw "\nFAIL: Connecting failed!";
    }
    else{
        printf("\nSUCCESS: Connected to %s!", inet_ntoa(hostAddr.sin_addr));
    }
}

void Client::sendToServer(const char* message){
    int errorCode;

    errorCode = send(clientSocket, message, bufferSize, 0);

    if(errorCode == SOCKET_ERROR){
        throw "\nFAIL: Unable to send message!";
    }
}

void Client::receive(char * buffer){
    int errorCode;

    errorCode = recv(clientSocket, buffer, bufferSize, 0);

    if(errorCode == 0){
        throw "\nFAIL: Lost connection to server!";
    }
    else if(errorCode == SOCKET_ERROR){
        throw "\nFAIL: Unable to receive message!";
    }
}

unsigned int Client::getBufferSize(void){ return bufferSize; }

void Client::setBufferSize(unsigned int size){ bufferSize = size; }
