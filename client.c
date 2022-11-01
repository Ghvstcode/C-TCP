#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#define SIZE 1000

int main(int argc, char* argv[])
{
            char *value;
    if(argc <= 1) {
        printf("provide the server port");
        exit(1);
    }; 

value = argv[1];
int port = atoi(value);
int n;

char *ip = "127.0.0.1";

  int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr(ip);

  n = connect(socketDescriptor, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (n < 0){
    perror("unable to bind");
    exit(1);
  }

  printf("extablished connection to the server.\n");

  char serverResponse[SIZE];
  recv(socketDescriptor, &serverResponse, sizeof(serverResponse), 0);

  printf("server response: %s\n", serverResponse);
  

  close(socketDescriptor);
  printf("disconnected from server.\n");
  return 0;
}