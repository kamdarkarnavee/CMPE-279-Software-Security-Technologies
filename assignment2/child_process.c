#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

int main(int argc, char const *argv[], char const *envp[])
{
	int received_socket, valread;
	char buffer[1024] = { 0 };
	char *hello = "Hello from server";

	received_socket = atoi(argv[1]);
	// Assigning child process to Nobody user (id - 65534)
	if (setuid(65534) < 0)
	{
		perror("Error dropping privileges using setuid\n");
		exit(EXIT_FAILURE);
	}

	valread = read(received_socket, buffer, 1024);
	printf("%s\n", buffer);
	send(received_socket, hello, strlen(hello), 0);
	printf("Hello message sent\n");

	return 0;
}
