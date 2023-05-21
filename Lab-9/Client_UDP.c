#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5555

int main(){
    int s, t, len;
    struct sockaddr_in remote;
    char* msg = "MSG from client!";
    char str[100];

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
		
        sendto(s, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &remote, sizeof(remote));
        printf("message sent.\n");
                
        n = recvfrom(s, (char *)str, 100, MSG_WAITALL, (struct sockaddr *) &remote, &len);
        str[n] = '\0';
        printf("Server : %s\n", str);
    }
	
	close(s);

	return 0;
}
