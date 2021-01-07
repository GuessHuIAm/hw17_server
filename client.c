#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


int main(){
	//client pipe
	char clientN[32];

	sprintf(clientN, "%d", getpid());
	mkfifo(clientN, 0644);
    	printf("Client's pipe created.\n");

	//client to server
    	int server = open("WKP", O_WRONLY);
    	write(server, clientN, sizeof(clientN));
	printf("Waiting for connection...\n");

	int client = open(clientN, O_RDONLY);
	printf("Server connected to client.\n");

	//client reads from server
    	char message[32];
	read(client, message, sizeof(message));
    	printf("Client received server's message <%s>.\n", message);

	remove(clientN);
	printf("Client removed pipe.\n");

	//client sends back to server
    	write(server, "Hello!", sizeof("Hello!"));
	printf("Client sent <Hello!>, the handshake is complete!\n");

	int input;
	int output;

    	while(1){
        	printf("I will square this number: ");
        	scanf("%d", &input);
		write(server, &input, sizeof(input));

		read(client, &output, sizeof(output));
        	printf("The square of %d is %d\n", input, output);
 	}

	return 0;
}
