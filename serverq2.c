/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr

void reverseWordsWithVowels(char *str)
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
            if (vowelFound)
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
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;     //SERVER ADDR will have all the server address
    char server_message[2000], client_message[2000]; // Sending values from the server and receive from the server we need this
    int isServevrunning = 1;
    //Cleaning the Buffers

    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message)); // Set all bits of the padding field
                                                          //Creating Socket

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0)
    {
        printf("Could Not Create Socket. Error!!!!!\n");
        return -1;
    }

    printf("Socket Created\n");

    //Binding IP and Port to socket

    server_addr.sin_family = AF_INET;                     /* Address family = Internet */
    server_addr.sin_port = htons(2000);                   // Set port number, using htons function to use proper byte order */
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); /* Set IP address to localhost */

    // BINDING FUNCTION

    if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) // Bind the address struct to the socket.  /
                                                                                     //bind() passes file descriptor, the address structure,and the length of the address structure
    {
        printf("Bind Failed. Error!!!!!\n");
        return -1;
    }

    printf("Bind Done\n");
    while (isServevrunning)
    {
        //Put the socket into Listening State

        if (listen(socket_desc, 1) < 0) //This listen() call tells the socket to listen to the incoming connections.
                                        // The listen() function places all incoming connection into a "backlog queue" until accept() call accepts the connection.
        {
            printf("Listening Failed. Error!!!!!\n");
            return -1;
        }

        printf("Listening for Incoming Connections.....\n");

        //Accept the incoming Connections

        client_size = sizeof(client_addr);

        client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size); // heree particular client k liye new socket create kr rhaa ha

        if (client_sock < 0)
        {
            printf("Accept Failed. Error!!!!!!\n");
            return -1;
        }

        printf("Client Connected with IP: %s and Port No: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        //inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation

        //Receive the message from the client

        if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
        {
            printf("Receive Failed. Error!!!!!\n");
            return -1;
        }

        printf("Client Message: %s\n", client_message);
        reverseWordsWithVowels(client_message);
        printf("Inverted Message: %s\n\n", client_message);

        //Send the message back to client

        strcpy(server_message, client_message);

        if (send(client_sock, server_message, strlen(server_message), 0) < 0)
        {
            printf("Send Failed. Error!!!!!\n");
            return -1;
        }

        memset(server_message, '\0', sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));
    }

    //Closing the Socket

    close(client_sock);
    close(socket_desc);
    return 0;
}
//doneq2server