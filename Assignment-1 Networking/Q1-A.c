/*
Q1.Write a udp client server program,client writing messages to server program and server
return back the same toggled msg to client.

CLIENT PROGRAM
*/

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 8000

int main()
{
	int fd1, retval;

	struct sockaddr_in srvadd;

	fd1 = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd1 < 0)
	{
		perror("socket: ");
		exit(1);
	}

	bzero(&srvadd, sizeof(srvadd));
	srvadd.sin_family = AF_INET;
	srvadd.sin_addr.s_addr = inet_addr("127.0.0.1");
	srvadd.sin_port = htons(PORT);

	connect(fd1, (struct sockaddr *) &srvadd, sizeof(srvadd));
	
	printf("Client connecting to server.............\n");

	while(1)
	{
		char buffr[100];
		int n;

		printf("Enter message to send on server: \n");
		gets(buffr);
	
		send(fd1, buffr, strlen(buffr), 0);
		
		printf("Data sent to server\n");

		n = recv(fd1, buffr, sizeof(buffr), 0);
		
		if(n < 0)
		{
			perror("recv: ");
			exit(4);
		}
		
		printf("Received data from server : %s\n", buffr);		
	}	

	close(fd1);
	return 0;
}