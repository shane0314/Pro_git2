#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_TEXT 512

struct msg_st
{
	long int msg_type;
	char text[MAX_TEXT];
};

int main()
{
	int running = 1;
	struct msg_st data;
	char buffer[BUFSIZ];
	memset(buffer, 0, sizeof(buffer));
	
	printf("bufsize is %d\n", BUFSIZ);
	printf("MAX_TEXT is %d\n", MAX_TEXT);
	
	int msgid = -1;
	
	//建立消息队列
	msgid = msgget( (key_t)1234, 0666 | IPC_CREAT);
	if (msgid == -1)
	{
	    puts("msgget fail!\n");
	    exit(EXIT_FAILURE);
	}
	
	//向消息队列写消息， 知道写入end
	while (running)
	{
	    //输入数据
	    puts("input data:");
	    fgets(buffer, BUFSIZ, stdin);
	    //获取
	    data.msg_type = 2;
	    strcpy(data.text, buffer);
	    //发送
	    if (msgsnd(msgid, (void *)&data, MAX_TEXT, 0) == -1)
	    {
	        puts("send msg fail\n");
	        exit(EXIT_FAILURE);
	    }
	    //end
	    if ( strncmp(buffer, "end", 3) == 0 || strncmp(buffer, "END", 3)==0 )
	        running = 0;
	    sleep(1);
	}
    
	puts("exit sucess");
	exit(EXIT_SUCCESS);
}
	
