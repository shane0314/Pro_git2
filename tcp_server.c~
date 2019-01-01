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
/*
char *strupr(char *str)
{
	if (str == NULL)
		return NULL;
   char *ptr = str;

   while (*ptr != '\0') {
       if (islower(*ptr)) 
            *ptr = toupper(*ptr);
       ptr++;
   }

   return str;
} 
*/
int main()
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("scoket: ");
		return -1;
	}
	
	puts("socket success");
	
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY); //IP
	server.sin_port = htons(port);
	
	if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("bind: ");
		return -1;
	}
	
	puts("bind success");
	
	if (listen(server_fd, MAX) < 0)
	{
		perror("listen: ");
		return -1;
	}
	
	puts("listen success");
	
	struct sockaddr_in client;
	int client_len = sizeof(client);
	
	int conn;
	if ((conn = accept(server_fd, (struct sockaddr *)&client , &client_len) < 0))
	{
		perror("accept: ");
		return -1;
	}
	
	puts("accept success");
	/*
	else
	{
		printf("One client connected %s:%4d\n", (char *)client.sin_addr.s_addr, (short)client.sin_port);
	}
	*/
	char buff[105];
	while (1)
	{
		//接收
		memset(buff, 0, sizeof(buff));
		if (recv(conn, buff, sizeof(buff), 0) < 0)
		{
			perror("read: ");
			return -1;
		}
		if (strcmp(buff, "end\n") == 0)
		{
			puts("the server process end.");
			break;
		}
		printf("recv message from client: %s", buff);
		//发送
		
		memset(buff, 0, sizeof(buff));
		if (read(STDIN_FILENO, buff, sizeof(buff)) < 0)
		{
			perror("read2: ");
			return -1;
		}
		/*
		strupr(buff);
		*/
		if (send(conn, buff, strlen(buff), 0) < 0)
		{
			perror("send2: ");
			return -1;
		}
		
	}
	//关闭
	close(conn);
	close(server_fd);
	
	return 0;
}

