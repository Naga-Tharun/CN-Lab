#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5555

int main(int argc,char * argv[]){
    int s, t, len;
    struct sockaddr_in remote;
    char str[100];
    char buffer[100];

    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("socket creation failed..\n");
        exit(1);
    }

    memset(&remote, 0, sizeof(remote));

    remote.sin_family = AF_INET;
    remote.sin_port = htons(PORT);
    remote.sin_addr.s_addr = INADDR_ANY;

    

    while(printf("> "), fgets(str, 100, stdin), !feof(stdin)) {
        int n;
		
        if(sendto(s, (const char *)str, strlen(str), MSG_CONFIRM, (const struct sockaddr *) &remote, sizeof(remote)) < 0){
            perror("sendto failed");
            exit(1);
        }
        printf("message sent.\n");
        memset(buffer, 0, sizeof(buffer));      
        n = recvfrom(s, (char *)buffer, 100, MSG_WAITALL, (struct sockaddr *) &remote, &len);
        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
    }
	
	close(s);

	return 0;
}
