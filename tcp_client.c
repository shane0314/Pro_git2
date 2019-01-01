#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
/*
#include <ctype.h>
#include <stdlib.h>
*/

const int port = 8887;
const int MAX = 10; //biggest number of connected clients
const char IP[] = "127.0.0.1";
const int port2 = 8887;

int main ()
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
    	perror("socket: ");
    	return -1;
    }
    
    puts("socket success");
    
    struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(IP); //
	server.sin_port = htons(port);
	
	/*
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = htonl(IP); //
	client.sin_port = htons(port2);
	
	if (bind(client_fd, (struct sockaddr *)&client, sizeof(client)) < 0)
	{
		perror("bind: ");
		return -1;
	}
	
	puts("bind success");
	*/
	//连接 
	if (connect(client_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("client_fdect: ");
		return -1;
	}
	
	puts("connect success");
	
	char sends[105],recvs[105];
	while (1)
	{
		//发送
		read(STDIN_FILENO, sends, sizeof(sends));
		
		if (send(client_fd, sends, strlen(sends), 0) <0)
		{
			perror("send: ");
			return -1;
		}
		if (strcmp(sends, "end\n") == 0)
		{
			puts("the client end.");
			break;
		}
		//接收
		memset(recvs, 0, sizeof(recvs));
		if (recv(client_fd, recv, sizeof(recvs), 0) < 0)
		{
			perror("recv: ");
			return -1;
		}
		printf("recv message from server: %s", recvs);

		memset(sends, 0, sizeof(sends));
	}
	close(client_fd);
	return 0;
}
		
		
		
		
