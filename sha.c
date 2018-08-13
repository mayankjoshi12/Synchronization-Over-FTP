#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>
#include <openssl/sha.h>

int main(void)
{
  DIR           *d;
  struct dirent *dir;
  FILE *f;
  char ch[50];
  unsigned char buffer[BUFSIZ];
  SHA256_CTX ctx;
  size_t len;
  d = opendir("/home/kush/Documents"); //change this according to your requirement
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
       /*if (!strcmp (dir->d_name, "."))
            continue;
        if (!strcmp (dir->d_name, ".."))    
            continue; */
          strcpy(ch,dir->d_name);
         if(ch[strlen(ch)-1]=='t' && ch[strlen(ch)-2]=='x' && ch[strlen(ch)-3]=='t' && strcmp("sync.txt",dir->d_name)!=0 && strcmp("hashc.txt",dir->d_name)!=0 && strcmp("hashs.txt",dir->d_name)!=0 && strcmp("sync.txt",dir->d_name)!=0){
           
           /*continue;

         if(ch[strlen(ch)-2]=='u')
          continue;
        if(ch[strlen(ch)-1]=='a')
          continue; */

      printf("%s\n", ch);
      f=fopen(dir->d_name,"r");
      SHA256_Init(&ctx);

      do {
        len = fread(buffer, 1, BUFSIZ, f);
        SHA256_Update(&ctx, buffer, len);
    } while (len == BUFSIZ);

      SHA256_Final(buffer, &ctx);
      fclose(fopen("hashc.txt", "w"));
      f = fopen("hashc.txt","a");
       fprintf(f,"%s",dir->d_name);
      fprintf(f,"%s","-");
    for (len = 0; len < SHA256_DIGEST_LENGTH; ++len)
      {
        fprintf(f,"%02x", buffer[len]);
        printf("%02x", buffer[len]);
      }
    putchar('\n');
    fprintf(f,"\n");

    }

    else
      continue;
  
}
    closedir(d);
}
    fclose(f);
  return(0);
}
