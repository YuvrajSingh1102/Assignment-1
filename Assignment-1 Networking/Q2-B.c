/*
Q2.Write a program that implement reliable transmission in TCP protocol,in which server
uses child to handle client request.
*/

//CLIENT CHILD

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>

int main()
{
	char *serv_ip = "127.0.0.1";
	int fd1, retval;

	struct sockaddr_in servaddr;

	fd1 = socket(AF_INET, SOCK_STREAM, 0);
	if(fd1 < 0)
	{
		perror("sock: ");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);

	retval = connect(fd1, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(retval < 0)
	{
		perror("connect: ");
		exit(2);
	}

	printf("client established connection with server\n");

	while(1)
	{
		int n;

		char s_buffer[200];
		char r_buffer[200];

		printf("\nEnter the data to send to the server: \n");
		gets(s_buffer);
	
		write(fd1 , s_buffer, strlen(s_buffer));

		n = read(fd1, r_buffer, sizeof(r_buffer));
		r_buffer[n] = '\0';
		printf("\nData rec'd from server:\n %s\n", r_buffer);
	}

	close(fd1);

	return 0;
}