#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5555

int main (int argc,char * argv[])
{
    int s, t, len;
    struct sockaddr_in remote;
    char str[100];
    char buffer[100];

    if(argc!=2)
{
    		printf("\n Invalid server address\n");
    		exit(0);     

}
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
{
        		perror("socket creation failed..\n");
        		exit(1);
    	}

    printf("Trying to connect... to %s\n",argv[0]);

    bzero((char *)&remote,sizeof(remote));
    remote.sin_family = AF_INET;
    remote.sin_port =htons(PORT);
    remote.sin_addr.s_addr =inet_addr( argv[1]);


    
    if (connect(s, (struct sockaddr *)&remote, sizeof(remote) ) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");
	
    while(printf("> "), fgets(str, 100, stdin), !feof(stdin)) {
        if (send(s, str, strlen(str), 0) == -1) {
            perror("send");
            exit(1);
        }
	memset(buffer, 0, sizeof(buffer));
        if ((t=recv(s, buffer, 100, 0)) > 0) {
            str[t] = '\0';
            
            if(strlen(buffer) == 0){
            	continue;
            }
            printf("clientecho> %s\n", buffer);
        } else {
            if (t < 0) perror("recv");
            else printf("Server closed connection\n");
            exit(1);
        }
    }

    pclose(s);

    return 0;
}