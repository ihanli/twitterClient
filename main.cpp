/*###############################
# FH Salzburg                   #
# WS2010 MMT-B2009              #
# Multimediale Netzwerke        #
# Uebungsprojekt                #
# Fritsch Andreas, Hanli Ismail #
# Sun, 28.11.2010 22:00         #
###############################*/

#include "TwitterClient.h"

using namespace std;

int main(void)
{
	string input;
	char* message;

	printf("Please enter an IP: ");
	getline(cin, input);

    TwitterClient myClient(input.c_str());

    message = new char[myClient.getBufferSize()];

	try
	{
		myClient.connectToServer();

   		while(true)
   		{
   			myClient.serverListener();
    	}
	}
	catch(const char* failure)
	{
		printf("%s", failure);
	}

	delete [] message;

    return 0;
}
