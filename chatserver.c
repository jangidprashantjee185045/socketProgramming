#include<sys/socket.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include <netdb.h>
int main(int argc, char const *argv[])
{
	int sock,temp_sock;
	char buffer[1024];
	struct sockaddr_in  server, client;
    int k;
	memset(&server,0,sizeof(server));
	memset(&client,0,sizeof(client));

	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror(" Error in creating socket");
		exit(1);
	}

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	//server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=8000;

    if((k=bind(sock,(struct sockaddr *)&server,sizeof(server)))==-1)
    {
    	perror("Error in binding");
    	exit(1);
    }

    if((k=listen(sock,20))==-1)
    {
    	perror("Error in listning");
    	exit(1);
    }

    socklen_t len=sizeof(client);

    if((temp_sock=accept(sock,(struct sockaddr *)&client,&len))==-1)
    {
    	perror("Error in acceptence");
    	exit(1);
    }
    
    while(1)
    {
    	if((k=recv(temp_sock,buffer,1024,0))==-1)
    	{
    		perror("Error , but i cann't explain");
    		exit(1);
    	}
    	printf("Message from client %s\n",buffer);
    	printf("\nSay something : ");
    	fgets(buffer,1024,stdin);
    	if(strncmp(buffer,"end",3)==0)
    		 break;
    	if((k=send(temp_sock,buffer,1024,0))==-1)
    	{
    		perror("Error in sent");
    		exit(1);
    	}

    } 

    close(temp_sock);
    exit(1); 
	return 0;
}