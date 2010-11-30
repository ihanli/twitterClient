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
#include "Client.h"

using namespace std;

int main(int argc, char **argv)		// possibility to start the client with arguments
{
	string input;
	char kbInput[140];
	char message[140];

// if(argc == 1)
// {
//	printf("Please enter an IP and port (port is optional).\n");
//	getline(cin, input);
//	scanf("%s", *argv);
// }

//	printf("Please enter an IP and port (port is optional).\n");
//	getline(cin, input);
//	scanf("%s", kbInput);

	Client myClient("127.0.0.1");//input.c_str());		// create client with port and ip

	try
	{
		myClient.connectToServer();			// connect with server
	}
	catch(const char* failure)
	{
		printf("%s", failure);
	}

	printf("\n");

	while(true)
	{
		printf("u sayin': ");
		getline(cin, input);
		while(input.length() > 140)		// check for the user if entered message is too long
		{
			printf("You entered %d letters. Only 140 allowed.\nEnter new message: ", input.length());
			getline(cin, input);
		}
//      twitterCommand << input;
//      twitterCommand >> *kbInput;
//      scanf("%s", kbInput);

//      if(kbInput[0] == 'q')
//		{
//          myClient.sendToServer(input.c_str());
//          break;
//      }

		try		// send and receive
		{
			myClient.sendToServer(input.c_str());
			myClient.receive(message);
			printf("server echoin': %s\n", message);
		}
		catch(const char* failure)		// exception handling
		{
			printf("%s", failure);
		}
	}
	return 0;
}
