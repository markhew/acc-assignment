#include	"acc.h"

int
main(int argc, char **argv)
{
	int			sockfd;
	struct 		sockaddr_in	servaddr;
	char		servIP[INET6_ADDRSTRLEN];

	if (argc != 3){
		err_quit("usage: client <Hostname> <port number>");
	}

	char* servname = argv[1];
	struct hostent *servEnt;

	servEnt = gethostbyname(servname);
	if(servEnt == NULL){
		err_quit("Server %s does not exist\n",servname);
	}
	else{
		sockfd = Socket(AF_INET, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(atoi(argv[2]));
		
		Inet_ntop(servEnt->h_addrtype, servEnt->h_aliases, servIP, sizeof(servIP));
		Inet_pton(AF_INET, servIP, &servaddr.sin_addr);
		//servaddr.sin_addr.s_addr = servEnt->h_addr_list;
	  	//memcpy(&servaddr.sin_addr, servEnt->h_addr_list, servEnt->h_length);

		Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

		str_cli(stdin, sockfd);		/* do it all */
		printf("Closing connection\n");
	}

	
	
	exit(0);
}
