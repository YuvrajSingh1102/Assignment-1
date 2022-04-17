/*
Q2.Write a program that implement reliable transmission in TCP protocol,in which server
uses child to handle client request.
*/

//SERVER CHILD

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

void handleClient(int connfd)
{
	int n;
	char buff[200];

	n = read(connfd, buff, 200);
	buff[n] = '\0';

	printf("Data record from client : %s\n",buff);
	printf("\nrequested handled by server: %d\n",getpid());
	write(connfd, "Good bye", 8);

	printf("\nData sended to client\n");
        exit(0);
}

int main()
{
	int fd1, connfd, retval;
	pid_t childpid;

	socklen_t clilen;
	struct sockaddr_in clientaddr, servaddr;

	fd1 = socket(AF_INET, SOCK_STREAM, 0);
	if(fd1 < 0)
	{
		perror("sock: ");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8000); 

	retval = bind(fd1, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(retval < 0)
	{
		perror("bind: ");
		exit(2);
	}

	listen(fd1, 5);

	while(1)
	{
		char s_buf[200];
		char r_buf[200];
		pid_t p;

		int n;

		clilen = sizeof(clientaddr);
		connfd = accept(fd1, (struct sockaddr *) &clientaddr, &clilen);
		printf("client connected\n");
		
		p = fork();
		if(p == 0)
		{
			close(fd1);
			handleClient(connfd);
		}
		close(connfd);
	}

	return 0;
}