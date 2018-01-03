#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	char message[101];

	char* address = "Socket_multi_client.exe ";
	char *path = malloc(strlen(address) + strlen(argv[1]) + 1);
	strcpy(path, address);
	strcat(path, argv[1]);

	// Validate the parameters
	if (argc != 2){
		printf("usage: %s server-address\n", argv[0]);
		return 1;
	}

	printf("Enter 'shutdown' to close this program and the server\n");

	while (1){
		if (strstr(message, "shutdown") != NULL){
			break;
		}

		printf("Enter Message to Send:\n");
		fgets(message, 101, stdin);

		FILE *filePtr = fopen("User_Input.txt", "w");
		if (filePtr == NULL){
			printf("Error opening file!\n");
			return 1;
		}

		fprintf(filePtr, "%s", message);
		fclose(filePtr);

		system(path);
	}

	free(path);
	return 0;
}