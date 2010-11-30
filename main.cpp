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
#include <conio.h>
#include <vector>

using namespace std;

//char message[140];
//string tweeterName;
//vector<char*> incomingTweets;

//void* doit(void* arg)
//{
//	char* argCopy = ((char *) arg);
//	free(arg);
//	pthread_detach(pthread_self());
//	myClient.receive(message);
////
////	if()
//
//	printf("%s", message);
//	printf("\nu sayin': ");
//}

int main(int argc, char **argv)
{
	string input;
	char message[140];

	printf("Please enter an IP and port (port is optional).\n");
	getline(cin, input);

    TwitterClient myClient(input.c_str());

	try
	{
		myClient.connectToServer();			// connect with server
	}
	catch(const char* failure)
	{
		printf("%s", failure);
	}

	while(true)
	{
		if(kbhit())
		{
			char commandFlag = getch();

			if(commandFlag == ':')
			{
				getline(cin, input);

				try
				{
        			myClient.sendToServer(input.c_str());
				}
        		catch(const char* failure){
           			printf("%s", failure);
           			break;
        		}
			}
		}
		else
		{
			try
			{
				myClient.receive(message);
				printf("%s", message);
			}
			catch(const char* failure){
				printf("%s", failure);
				break;
			}
		}
	}

//	string input;
//	string kbInput;
//
//	pthread_t pid;
//	int *iptr;
//
//	printf("Please enter an IP and port (port is optional).\n");
//	getline(cin, input);
//
//    TwitterClient myClient(input.c_str());
//
//	try
//	{
//		myClient.connectToServer();			// connect with server
//	}
//	catch(const char* failure)
//	{
//		printf("%s", failure);
//	}
//
////	pthread_create(&pid, NULL, &myClient.receive, message);
//
//	printf("\nu sayin': ");
//
//    while(1){
//    //	iptr = malloc(sizeof(int));
//
//
//        getline(cin, input);
//
//        try{
//
//        	myClient.sendToServer(input.c_str());
//
//			//*iptr = myClient.receive(message);
//        }
//        catch(const char* failure){
//            printf("%s", failure);
//        }
//    }

    return 0;
}
