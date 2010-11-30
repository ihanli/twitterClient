#include <iostream>
#include <sstream>
#include <string>
#include "TwitterClient.h"
#include <pthread.h>
#include <vector>

using namespace std;

char message[140];
string tweeterName;
vector<char*> incomingTweets;

void* doit(void* arg)
{
	char* argCopy = ((char *) arg);
	free(arg);
	pthread_detach(pthread_self());
//
//	if()

	printf("%s", message);
	printf("\nu sayin': ");
}



int main(int argc, char **argv)
{
	string input;
	string kbInput;

	pthread_t pid;
	int *iptr;

	printf("Please enter an IP and port (port is optional).\n");
	getline(cin, input);

    TwitterClient myClient(input.c_str());

    try{
        myClient.connectToServer();
    }
    catch(const char* failure){
        printf("%s", failure);
    }

	printf("\nu sayin': ");

    while(1){
        getline(cin, input);

        try{

        	myClient.sendToServer(input.c_str());

			myClient.receive(message);
        	pthread_create(&pid, NULL, &doit, message);
        }
        catch(const char* failure){
            printf("%s", failure);
        }
    }

    return 0;
}
