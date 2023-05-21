#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5555

int main(void){

    FILE *fp;
    fp = fopen("output.txt", "w");

    int s, s2, t, len;
    struct sockaddr_in local, remote;
    char str[100];
    char input[100];	

    if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket creation failed…\n");
        exit(1);
    }

    bzero((char *)&local,sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port =htons(PORT);
    local.sin_addr.s_addr =htonl(INADDR_ANY);


    
    if(bind(s, (struct sockaddr *)&local,sizeof(local)) == -1){
        perror("bind");
        exit(1);
    }

    if(listen(s, 5) == -1){
        perror("listen");
        exit(1);
    }

    for(;;){
        int done, n;
        printf("Waiting for a connection...\n");
        t = sizeof(remote);
        if((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1){
            perror("accept");
            exit(1);
        }

        printf("Connected.\n");

        done = 0;
        do{
            memset(str, 0, sizeof(str));
            n = recv(s2, str, 100, 0);
            if(n <= 0){
                if (n < 0) perror("recv");
                done = 1;
            }
            printf("serverecho> %s\n",str);
            fputs(str, fp);
            fputs("\n", fp);
            fclose(fp);
            
            printf("> ");
            fgets(input, 100, stdin);
            if(!done) 
                if (send(s2, input, n, 0) < 0) {
                    perror("send");
                    done = 1;
                }
        } while(!done);

        pclose(s2);
    }

    return 0;
}