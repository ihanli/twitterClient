#include "SocketBase.h"

SocketBase::SocketBase(const WORD clientSocketVersion, const int type, const int protocol) :
           version(clientSocketVersion), type(type), protocol(protocol){}

void SocketBase::createSocket(SOCKET* base, int af){
    WSADATA wsa;
    int errorCode;

    printf("\nStarting baseSocket...");

    errorCode = WSAStartup(version, &wsa);

    if(errorCode != 0){
        throw "\nFAIL: Couldn't start baseSocket (WSAStartup)";
    }
    else{
        printf("\nSUCCESS: baseSocket started!");
    }

    printf("\nCreating clientSocket...");

    *base = socket(af, type, protocol);

    if(*base == INVALID_SOCKET){
        throw "\nFAIL: Couldn't create socket (socket)";
    }
    else{
        printf("\nSUCCESS: Socket created!");
    }
}
