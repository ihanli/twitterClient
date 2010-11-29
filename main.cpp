#include <iostream>
#include <sstream>
#include <string>
#include "Client.h"

using namespace std;

int main(int argc, char **argv)
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

	printf("Please enter an IP and port (port is optional).\n");
	getline(cin, input);
//	scanf("%s", kbInput);

    Client myClient(input.c_str());

    try{
        myClient.connectToServer();
    }
    catch(const char* failure){
        printf("%s", failure);
    }

	printf("\n");

    while(1){
        printf("u sayin': ");
        getline(cin, input);
//        twitterCommand << input;
//        twitterCommand >> *kbInput;
//        scanf("%s", kbInput);

//        if(kbInput[0] == 'q'){
//            myClient.sendToServer(input.c_str());
//            break;
//        }

        try{
            myClient.sendToServer(input.c_str());
            myClient.receive(message);
            printf("server echoin': %s\n", message);
        }
        catch(const char* failure){
            printf("%s", failure);
        }
    }

    return 0;
}