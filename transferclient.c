#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>          
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 2000
#define LENGTH 1000000


void error(const char *msg)
{
	perror(msg);
	exit(1);
}


int main(int argc, char *argv[])
{
	/* Variable Definition */
	int sockfd; 
	int nsockfd;
	char revbuf[LENGTH]; 
	struct sockaddr_in remote_addr;
	char line[1000],line4[1000];
     
	/* Get the Socket file descriptor */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
	    error("ERROR: Failed to obtain Socket Descriptor!\n");
	}

	/* Fill the socket address struct */
	remote_addr.sin_family = AF_INET; 
	remote_addr.sin_port = htons(PORT); 
	inet_pton(AF_INET, "192.168.43.232", &remote_addr.sin_addr); 
	bzero(&(remote_addr.sin_zero), 8);

	/* Try to connect the remote */
	if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
	{
	    error("ERROR: Failed to connect to the host!\n");
	}
	else 
		printf("[Client] Connected to server at port %d...ok!\n", PORT);

	/* Send File to Server */
	//if(!fork())
	//{
		char* fs_name = "/home/kush/Documents/hashc.txt";
		char sdbuf[LENGTH]; 
		printf("[Client] Sending %s to the Server...", fs_name);
		FILE *fs = fopen(fs_name, "r");
		if(fs == NULL)
		{
		    printf("ERROR: File %s not found.\n", fs_name);
			exit(1);
		}

		bzero(sdbuf, LENGTH); 
		int fs_block_sz; 
		//int success = 0;
		while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0)
	    {
	        if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
	        {
	            printf("ERROR: Failed to send file %s.\n", fs_name);
	            break;
	        }
	        bzero(sdbuf, LENGTH);
	    }
	    printf("Ok File %s from Client was Sent!\n", fs_name);
	    //success = 1;
	//}

	/*Receive File from Server */
	printf("[Client] Receiveing file from Server and saving it as sync.txt...");

	char* fr_name = "/home/kush/Documents/sync.txt";
	fclose(fopen(fr_name,"w"));
	FILE *fr = fopen(fr_name, "a");
	if(fr == NULL)
		printf("File %s Cannot be opened.\n", fr_name);
	else
	{
	    bzero(revbuf, LENGTH); 
	    int fr_block_sz = 0;
	    int success = 0;
	    //while(success == 0)
	    //{
	        while(fr_block_sz = recv(sockfd, revbuf, LENGTH, 0))
	        {
	            if(fr_block_sz < 0)
	            {
	                error("Receive file error.\n");
	            }
	            int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
	            if(write_sz < fr_block_sz)
	            {
	                error("File write failed.\n");
	            }
				else if(fr_block_sz)
				{
					break;
				}
	            bzero(revbuf, LENGTH);
	        }
	        printf("Ok received from server!\n");
	        sleep(1);
	        success = 1;
	        fclose(fr);
	    //}
	   } 

	    FILE *ff=fopen("sync.txt","r");
	       
	      while(fgets(line4,1000,ff)!=NULL)
             { 
                int l=strlen(line4);
           
                line4[l-1]=0;



                 FILE *f5=fopen(line4,"w");
                    if(f5 == NULL)
	        {
	            printf("ERROR: File %s not found on server.\n", line4);
			exit(1);
	        }

	
	else
	{
	    bzero(revbuf, LENGTH); 
	    int fr_block_sz = 0;
	    int success = 0;
	    //while(success == 0)
	    //{
	        while(fr_block_sz = recv(sockfd, revbuf, LENGTH, 0))
	        {
	            if(fr_block_sz < 0)
	            {
	                error("Receive file error.\n");
	            }
	            int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, f5);
	            if(write_sz < fr_block_sz)
	            {
	                error("File write failed.\n");
	            }
				else if(fr_block_sz)
				{
					break;
				}
	            bzero(revbuf, LENGTH);
	        }
	        printf("Ok received from server!\n");
	        sleep(3);
	        success = 1;
	        fclose(f5);
	    //}
	   } 
	}

	
	

	       

	close (sockfd);
	printf("[Client] Connection lost.\n");
	return (0);
}
