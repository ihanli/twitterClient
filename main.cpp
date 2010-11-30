/*###############################
# FH Salzburg                   #
# WS2010 MMT-B2009              #
# Multimediale Netzwerke        #
# Uebungsprojekt                #
# Fritsch Andreas, Hanli Ismail #
# Sun, 28.11.2010 22:00         #
###############################*/

#include <iostream>
#include <sstream>
#include <string>
#include "TwitterClient.h"

#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	string input;
	string kbInput;
	char* message;
	bool eod = true;

	printf("Please enter an IP and port (port is optional).\n");
	getline(cin, input);

    TwitterClient myClient(input.c_str());

    message = new char[myClient.getBufferSize()];

	try
	{
		myClient.connectToServer();			// connect with server

   		while(true)
   		{
   			printf("\n>");
        	getline(cin, input);

        	myClient.sendToServer(input.c_str());
        	myClient.receive(message);
        	printf("%s", message);
    	}
	}
	catch(const char* failure)
	{
		printf("%s", failure);
	}

	delete [] message;

    return 0;
}
