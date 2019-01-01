# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
 
 
void sigchld_handler( int signo ){
    printf("sigchld_handler\n");
    sleep(3);
    return;
}
 
 
int main()
{
    int i;
    pid_t pid;
    pid_t cpid;
    signal( SIGCHLD, sigchld_handler );
    for( i=0; i<5; i++ ){
        pid = fork();
        if ( pid == 0 ){
            sleep(2);
            exit(0); // child exit.
        }
        else if ( pid == -1 ){
            perror( "fork" ); // fork failed.
            exit(-1);
        }
    }
    printf("before wait\n");
    system( "ps -ef | grep test1130-signal" );
    // while((cpid = waitpid(-1,NULL,0)!=-1)) {
    while ((cpid = wait(NULL)) != -1) {
        printf("wait pid is %d\n", cpid);
        continue;
    }
    printf("after wait\n");
    system( "ps -ef | grep ttt" );
}
