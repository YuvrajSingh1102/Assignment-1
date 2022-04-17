/*
Q1.Write a udp client server program,client writing messages to server program and server
return back the same toggled msg to client.

SERVER PROGRAM
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
	int fd1, retval, accfd;

	struct sockaddr_in srvadd, clientadd;
	socklen_t clintlen;

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

	retval = bind(fd1, (struct sockaddr *) &srvadd, sizeof(srvadd));
	if(retval < 0)
	{
		perror("bind: ");
		exit(2);
	}

	listen(fd1, 5);

	accfd = accept(fd1, (struct sockaddr *) &clientadd, &clintlen);
	if(accfd < 0)
	{
		perror("accept: ");
		exit(3);
	}
	printf("Client connected\n");

	while(1)
	{
		char buffr[100];
		int n;

		n = recv(accfd, buffr, sizeof(buffr), 0);
		if(n < 0)
		{
			perror("recv: ");
			exit(4);
		}
		printf("Rev'd data from client : %s\n", buffr);

		for(int i=0; i<n; i++)
		{
			if(buffr[i] >= 'a' && buffr[i] <= 'z')
				buffr[i] -= 32;
			else 
				buffr[i] += 32;
		}

		send(accfd, buffr, strlen(buffr), 0);
		printf("Data sended to client\n");
	}	

	close(fd1);
	return 0;
}