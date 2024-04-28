#include "std_lib_facilities.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
/**
 * Name:Lidor pahima
 * ID:206735961
 * This program will use as a client that asking to connect to the server than asking for the shortest path from source to destination
*/
int main(int argc, char* argv[]) {
    if(argc != 5){ //will checking the input from the user if correct
        perror("WORNG input");
    }
    const char* Serverip = argv[1];//taking the ip from the user
    int port = atoi(argv[2]);//taking the port from the user
    int from = atoi(argv[3]);//taking the source from the user
    int to = atoi(argv[4]);//taking the destination from the user
    int client_socket;//client socket to connect to the server
    struct sockaddr_in server_add;//server address will use later for connecting the server
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {//creating the socket and checking if socket created
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    server_add.sin_family = AF_INET ;//setting the address family
    server_add.sin_port = htons(port);//setting the port number
    if (inet_pton(AF_INET, Serverip, &server_add.sin_addr) <= 0) {//setting the ip address and checking if the ip is correct  if not will print the error
        perror("Worng address");
        exit(EXIT_FAILURE);
    }
    if (connect(client_socket, (struct sockaddr*)&server_add, sizeof(server_add) ) < 0) {//asking to connecting to the server if failed will print the error
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }
     string request = to_string(from) + " " + to_string(to);//create string that will send to the server using string "from" from the user and "to" from the user
    write(client_socket, request.c_str(), request.size() ); //writing to the server the request from the user
    char buffer[1024] = {0};//buffer to store the answer from the server will use later to read
    read(client_socket, buffer, sizeof(buffer));//reading the answer from the server (from the buffer)
    cout << "Answer: " << buffer << endl;//printing the answer from the server
    close(client_socket);//closing the client socket
    return 0;

}