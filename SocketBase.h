/*###############################
# FH Salzburg                   #
# WS2010 MMT-B2009              #
# Multimediale Netzwerke        #
# Uebungsprojekt                #
# Fritsch Andreas, Hanli Ismail #
# Sun, 28.11.2010 22:00         #
###############################*/

#ifndef SOCKETBASE_H_INCLUDED
#define SOCKETBASE_H_INCLUDED

#include <cstdio>
#include <winsock2.h>

// this socket base is the same as for the server
class SocketBase
{
	public:
		SocketBase(const WORD clientSocketVersion = MAKEWORD(2,0), const int type = SOCK_STREAM, const int protocol = 0);
		void createSocket(SOCKET* base, int af);

	private:
		WORD version;
		int type;
		int protocol;
};

#endif // SOCKETBASE_H_INCLUDED
