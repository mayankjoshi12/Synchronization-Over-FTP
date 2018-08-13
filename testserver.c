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
#define BACKLOG 5
#define LENGTH 3000000
void error(const char *msg)
{
	perror(msg);
	exit(1);
}
struct htable{

   char name[100];
    char hash[100];

    };



int main ()
{
	/* Defining Variables */
	int sockfd; 
	int nsockfd; 
	int num;
	int sin_size; 
	struct sockaddr_in addr_local; /* client addr */
	struct sockaddr_in addr_remote; /* server addr */
	char revbuf[LENGTH]; // Receiver buffer

   struct htable client[100];
    struct htable server[100]; 
   
    char line[1000],line1[1000],line3[1000],line4[1000];
    
	/* Get the Socket file descriptor */
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
	    error("ERROR: Failed to obtain Socket Descriptor.\n");
	}
	else 
		printf("[Server] Obtaining socket descriptor successfully.\n");

	/* Fill the client socket address struct */
	addr_local.sin_family = AF_INET; // Protocol Family
	addr_local.sin_port = htons(PORT); // Port number
	addr_local.sin_addr.s_addr = INADDR_ANY; // AutoFill local address
	bzero(&(addr_local.sin_zero), 8); // Flush the rest of struct

	/* Bind a special Port */
	if( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
	{
	    error("ERROR: Failed to bind Port.\n");
	}
	else 
		printf("[Server] Binded tcp port %d in addr sucessfully.\n",PORT);

	/* Listen remote connect/calling */
	if(listen(sockfd,BACKLOG) == -1)
	{
	    error("ERROR: Failed to listen Port.\n");
	}
	else
		printf ("[Server] Listening the port %d successfully.\n", PORT);

	int success = 0;
	while(success == 0)
	{
	    sin_size = sizeof(struct sockaddr_in);

	    /* Wait a connection, and obtain a new socket file despriptor for single connection */
	    if ((nsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, &sin_size)) == -1) 
		{
	        error("ERROR: Obtaining new Socket Despcritor.\n");
		}
	    else 
			printf("[Server] Server has got connected from %s.\n", inet_ntoa(addr_remote.sin_addr));

		/*Receive File from Client */
		
		
		char* fr_name = "/home/kush/Downloads/hashc.txt";
		fclose(fopen(fr_name,"w"));
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
			printf("File %s Cannot be opened file on server.\n", fr_name);
		else
		{
			bzero(revbuf, LENGTH); 
			int fr_block_sz = 0;
			
			    while(fr_block_sz = recv(nsockfd, revbuf, LENGTH, 0)) //could it be sockfd?
			    {
			        if(fr_block_sz < 0)
			        {
			            error("Error receiving file from client to server.\n");
			        }
			        int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
			        if(write_sz < fr_block_sz)
			        {
			            error("File write failed on server.\n");
			        }
					else if(fr_block_sz)
					{
						break;
					}
			        bzero(revbuf, LENGTH);
			    }
			    printf("Ok received from client!\n");
			    fclose(fr);
			
		}


FILE *f,*f1,*f2;

		f=fopen("hashc.txt","r");
    


int i=0;

 
while(fgets(line,1000,f)!=NULL)
{

    int j=0,k,l=0;
    while(line[j]!='-')
    {
        client[i].name[j]=line[j];
        j++;
    }
    for(k=j+1;k<=strlen(line)-1;k++)
    {

        client[i].hash[l]=line[k];
        l++;
    }




    
    printf("%s\n",client[i].name);
    printf("%s\n",client[i].hash);
    i++;
}
int c=i;
fclose(f);

f1=fopen("hashs.txt","r");

i=0;
    while(fgets(line1,1000,f1)!=NULL)
{

    int j=0,k,l=0;
    while(line1[j]!='-')
    {
        server[i].name[j]=line1[j];
        j++;
    }
    for(k=j+1;k<=strlen(line1)-1;k++)
    {

        server[i].hash[l]=line1[k];
        l++;
    }




    
    printf("%s\n",server[i].name);
    printf("%s\n",server[i].hash);
    i++;
}
int c1=i;


fclose(f1);
fclose(fopen("sync.txt","w"));
f2=fopen("sync.txt","a+");
for(int i=0;i<=c-1;i++)
{

  for(int j=0;j<=c1-1;j++)
  {

     if(strcmp(client[i].name,server[j].name)==0)

     {

        if(strcmp(client[i].hash,server[j].hash)==0)
            printf("no change needed for %s\n",client[i].name);

        else
        {
            fwrite(client[i].name,1,strlen(client[i].name),f2);
            fwrite("\n",1,1,f2);
        }



     }
    


  }


}
int e=0;
for(int i=0;i<=c1-1;i++)
{

  for(int j=0;j<=c-1;j++)
  {

     if(strcmp(server[i].name,client[j].name)==0)

     {

        e++;



     }


  }

printf("%d",e);
  if(e==0){

    fwrite(server[i].name,1,strlen(server[i].name),f2);
    fwrite("\n",1,1,f2);
}

e=0;

} 

fclose(f2);

		

		char* fs_name = "/home/kush/Downloads/sync.txt";
	        char sdbuf[LENGTH]; // Send buffer
	        printf("[Server] Sending %s to the Client...", fs_name);
	        FILE *fs = fopen(fs_name, "r");
	        if(fs == NULL)
	        {
	            printf("ERROR: File %s not found on server.\n", fs_name);
				exit(1);
	        }

	        bzero(sdbuf, LENGTH); 
	        int fs_block_sz; 
	        while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0)
	        {
	            if(send(nsockfd, sdbuf, fs_block_sz, 0) < 0)
	            {
	                printf("ERROR: Failed to send file %s.\n", fs_name);
	                exit(1);
	            }
	            bzero(sdbuf, LENGTH);
	        }
	        printf("Ok sent to client!\n");
	        sleep(3);

	       FILE *ff=fopen("sync.txt","r");
	       
           while(fgets(line4,1000,ff)!=NULL)
             { 
                int l=strlen(line4);
           
                line4[l-1]=0;



                 FILE *f5=fopen(line4,"r");
                 if(f5 == NULL)
	        {
	            printf("ERROR: File %s not found on server.\n", line4);
			exit(1);
	        }
	        
	   
	      
	        int fs_block_sz; 
	        while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, f5))>0)
	        {
	            if(send(nsockfd, sdbuf, fs_block_sz, 0) < 0)
	            {
	                printf("ERROR: Failed to send file %s.\n", line4);
	                exit(1);
	            }
	           
	        }
	        printf("Ok sent to client!\n");
	        sleep(3);
            fclose(f5);
            } 

             

	        success = 1;
	        close(nsockfd);
	        printf("[Server] Connection with Client closed. Server will wait now...\n");
	      
	}
}
