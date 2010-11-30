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

class SocketBase
{
	public:
		SocketBase(const WORD clientSocketVersion, const int type, const int protocol);
		void createSocket(SOCKET* base, int af);

	private:
		WORD version;
		int type;
		int protocol;
};

#endif // SOCKETBASE_H_INCLUDED
