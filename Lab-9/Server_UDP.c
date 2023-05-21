#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5555

int main(void){
    int s, s2, t, len;
    struct sockaddr_in local, remote;
    char* msg = "MSG from server!";
    char str[100];

    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("socket creation failed…\n");
        exit(1);
    }

    memset(&local, 0, sizeof(local));
    memset(&remote, 0, sizeof(remote));

    local.sin_family = AF_INET;
    local.sin_port = htons(PORT);
    local.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, (struct sockaddr *)&local, sizeof(local)) == -1){
        perror("bind");
        exit(1);
    }

    int n;
	
	len = sizeof(remote);
	
	n = recvfrom(s, (char *)str, 100, MSG_WAITALL, ( struct sockaddr *) &remote, &len);
	str[n] = '\0';
	printf("Client : %s\n", msg);
	sendto(s, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &remote, len);
	printf("message sent.\n");

    int done = 0;
    do {
        int n;
	
        len = sizeof(remote);
        
        n = recvfrom(s, (char *)str, 100, MSG_WAITALL, ( struct sockaddr *) &remote, &len);
        if(n <= 0){
            done = 1;
        }
        str[n] = '\0';
        printf("Client : %s\n", msg);
        sendto(s, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &remote, len);
        printf("message sent.\n");

    } while (!done);

	return 0;
}