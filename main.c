#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Error function used for reporting issues
void error(const char *msg) {
  perror(msg);
//   exit(1);
} 

// Set up the address struct for the server socket
void setupAddressStruct(struct sockaddr_in* address, 
                        int portNumber){
 
  // Clear out the address struct
  memset((char*) address, '\0', sizeof(*address)); 

  // The address should be network capable
  address->sin_family = AF_INET;
  // Store the port number
  address->sin_port = htons(portNumber);
  // Allow a client at any address to connect to this server
  address->sin_addr.s_addr = INADDR_ANY;
}

void bindSection(int startPort, int endPort) {
		for(int i=startPort; i < endPort; i++) {
			struct sockaddr_in serverAddress;
			int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
			setupAddressStruct(&serverAddress, i);
			if (bind(listenSocket, 
					(struct sockaddr *)&serverAddress, 
					sizeof(serverAddress)) < 0) {
					error("ERROR on binding");
					continue;
			}

			printf("binding to: %d\n", i);
			listen(listenSocket, 5); 
		
	}
}

void forkProc(int startPort) {
	//
	pid_t spawnpid = -5;
  	// If fork is successful, the value of spawnpid will be 0 in the child, the child's pid in the parent
	spawnpid = fork();
	switch (spawnpid) {
		case -1:
      		// Code in this branch will be exected by the parent when fork() fails and the creation of child process fails as well
			perror("fork() failed!");
			exit(1);
			break;
		case 0:
      		// spawnpid is 0. This means the child will execute the code in this branch
			bindSection(startPort, (startPort+1010));
			while(1) {
				printf("holding sockets\n");
				sleep(10);
			}
			break;
		default:
      		// spawnpid is the pid of the child. This means the parent will execute the code in this branch
			// printf("I am the parent! ten = %d\n", intVal);
			break;
	}
}

int main(int argc, char *argv[]){
	// struct sockaddr_in serverAddress, clientAddress;
	// socklen_t sizeOfClientInfo = sizeof(clientAddress);
	
	//   // Create the socket that will listen for connections
	//   int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	//   if (listenSocket < 0) {
	//     error("ERROR opening socket");
	//   }

	// Set up the address struct for the server socket
	// setupAddressStruct(&serverAddress, atoi(argv[1]));

	// Associate the socket to the port
	//   if (bind(listenSocket, 
	//           (struct sockaddr *)&serverAddress, 
	//           sizeof(serverAddress)) < 0){
	//     error("ERROR on binding");
	//   }

	// bindSection(5500, 7500);

	int currPort = 1025;
	for(int i= 0; i < 65; i++) {
		forkProc(currPort);
		currPort += 1010;
	}
	
	


	// Close the listening socket
	// close(listenSocket); 
	return 0;
}