/*
        TCP_Client. This Program will implement the Client Side for TCP_Socket Programming.
        It will get some data from user and will send to the server and as a reply from the
        server, it will get its data back.
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr

void reverseWordsWithoutVowels(char *str)
{
    int size = strlen(str);
    int startIndex = 0;
    for (int i = 0; i <= size; i++)
    {

        if (str[i] == ' ' || str[i] == '\n' || i == size)
        {

            int endIndex = i - 1;
            //check if the this word has vowels
            int vowelFound = 0;
            int currIndex = startIndex;
            while (currIndex <= endIndex)
            {
                if (str[currIndex] == 'a' || str[currIndex] == 'e' || str[currIndex] == 'i' || str[currIndex] == 'o' || str[currIndex] == 'u' || str[currIndex] == 'A' || str[currIndex] == 'E' || str[currIndex] == 'I' || str[currIndex] == 'O' || str[currIndex] == 'U')
                {
                    vowelFound = 1;
                    break;
                }
                currIndex++;
            }
            //if vowel found,reverse that word
            if (!vowelFound)
            {
                //reverse that word
                while (startIndex < endIndex)
                {
                    char temp;
                    temp = str[startIndex];
                    str[startIndex] = str[endIndex];
                    str[endIndex] = temp;
                    // swap(str[startIndex], str[endIndex]);
                    startIndex++;
                    endIndex--;
                }
            }
            startIndex = i + 1;
        }
    }
}
int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];
    char id[2];
    //Cleaning the Buffers

    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    //Creating Socket

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0)
    {
        printf("Could Not Create Socket. Error!!!!!\n");
        return -1;
    }

    printf("Socket Created\n");

    //Specifying the IP and Port of the server to connect

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Now connecting to the server accept() using connect() from client side

    if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Connection Failed. Error!!!!!");
        return -1;
    }

    printf("Connected\n");

    //Get Input from the User
    printf("Enter message: ");
    gets(client_message);

    if (send(socket_desc, client_message, strlen(client_message), 0) < 0)
    {
        printf("Send Failed. Error!!!!\n");
        return -1;
    }

    //Receive the message back from the server

    if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0)
    {
        printf("Receive Failed. Error!!!!!\n");
        return -1;
    }

    printf("Server Message: %s\n", server_message);
    reverseWordsWithoutVowels(server_message);
    printf("Inverted Message: %s\n", server_message);

    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    //Closing the Socket

    close(socket_desc);

    return 0;
}
//doneq2client