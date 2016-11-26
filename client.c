  #include <netdb.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <stdio.h>
	#include <string.h>
	

	void readLine(char line[]); //prototype for the readLine function
	

	int main()
	{
		char username[20]; //char array to hold username
		char ipAddress[15]; //char array to hold the ipAddress
		unsigned int port; //integer to hold the port number
		
		printf("\n"); 
		printf("Enter IP: ");
		scanf("%s" , ipAddress); //input the ip address
		
		printf("Enter a port number: "); //input the port number
		scanf("%i" ,&port);
		
		while(port > 65535 || port < 1024) //makes sure port number is valid
		{
			port = 0;
			printf("Invalid input.\nEnter a port number: ");
			scanf("%i" , &port);
		}
		
		printf("Enter username: "); 
		scanf("%s" , username); //input username
	
    //creates socket to connect to server
		int sockFD = -1;
		sockFD = socket(AF_INET, SOCK_STREAM, 0);
		
    //set the address and port of the server to connect to
		struct sockaddr_in address;
		memset(&address,0,sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		inet_pton(AF_INET, ipAddress, &(address.sin_addr)); 
		
    //connect to the server
		connect(sockFD, (struct sockaddr *) &address,sizeof(address));
		
		char buffer[255] = "";
		char message[255];
		
		getchar();
		while(strcmp("quit",buffer) != 0) //sends message until user types "quit"
		{
			printf("%s: ",username); //prints user name in front of each message
			readLine(buffer); //reads in the message input
			strcpy(message,username); //to message
			strcat(message, ": "); //concatenate to have the username and ": " for each message
			strcat(message,buffer); //add content of the buffer to the message
			send(sockFD,message,strlen(message),0); //send socket to server
		}
		
		printf("\n");
		
		send(sockFD,buffer,strlen(buffer)+1,0); 
		close(sockFD); 
		return 0;
	}
	
  //readLine function to format the input into a string terminated with \0
	void readLine(char line[])
	{	
		int c = 0;	
		int i = 0;
	

		while( (c = getchar()) != '\n' )
		{
			line[i] = c;
			i++;
		}
	

		line[i] = '\0';
	}

