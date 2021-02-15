#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	int sock,k;
	struct sockaddr_in client;
	char buffer[1024];

	memset(&client,0,sizeof(client));
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Error in creating socket");
		exit(1);
	}
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	//client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=8000;
	if((k=connect(sock,(struct sockaddr *)&client,sizeof(client)))==-1)
	{
		perror("Error in connection");
		exit(1);
	}

	while(1)
	{
		printf("Say something : ");
		fgets(buffer,1024,stdin);
		if((k=send(sock,buffer,1024,0))==-1)
		{
			perror("Error in sending");
			exit(1);
		}
		if((k=recv(sock,buffer,1024,0))==-1)
		{
			perror("Error in receving data");
			exit(1);
		}
		printf("Message from server : %s\n",buffer);
	}
	close(sock);
	exit(1);
	return 0;
}