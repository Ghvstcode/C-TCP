#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
        char *value;
    if(argc <= 1) {
        printf("provide the server port");
        exit(1);
    }; 

value = argv[1];
int port = atoi(value);

char *ip = "127.0.0.1";
char server_message[256] = "server responded";
int server_socket, n;


server_socket = socket(AF_INET,SOCK_STREAM,0);
  if (server_socket < 0){
    perror("unable to open socket");
    exit(1);
  }

struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(port);
server_address.sin_addr.s_addr = inet_addr(ip);

//calling bind function on the specified IP and port
n = bind(server_socket,(struct sockaddr*) &server_address,sizeof(server_address));
  if (n < 0){
    perror("unable to bind");
    exit(1);
  }

printf("Bind to the port number: %d\n", port);

listen(server_socket,5);


int client_socket;
client_socket = accept(server_socket,NULL,NULL);
printf("client connected.\n");
send(client_socket,server_message,sizeof(server_message),0);

close(server_socket);
printf("client disconnected.\n\n");
return 0;
}