#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "html.h"
#include "/home/rar294/Documents/Project/C/Algorithm/generic_pointer/genericPtr.h"

void http_url_parse(ptr_1b *page,int clientFd){
  recv(clientFd,page,1500,0);

  ptr_1b *api_e = memchr(page,32,1500) + 1;
  ptr_1b *query_p = memchr(page,63,1500) + 1;

  *(api_e - 1) = 0;
  *(query_p - 1) = 0;
  *((ptr_1b*)memchr(query_p,32,1500)) = 0;

  if(!strcmp(api_e,"/query_parameter") && !strcmp(page,"GET")){

    for(ptr_1b* q = query_p;*q;){
       q = memchr(q,61,1500) + 1;
       while(*q){
         if(*q == 38){
           *q = 0;
           break;
         }
         q++;
       }
    }

    char *nama = memchr(query_p,61,1500) + 1;
    char *umur = memchr(memchr(nama,0,1500),61,1500) + 1;

    char n_save = *(nama + 7);
    char u_save = *(umur + 7);

    *(nama + 7) = 0;
    *(umur + 7) = 0;

    if(!strcmp(nama + 1,"script") || !strcmp(umur + 1,"script")){
      printf("xxs detected\n");
      close(clientFd);
      return;
    }

    *(nama + 7) = n_save;
    *(umur + 7) = u_save;

    ptr_1b *store = page + 4096;
    ptr_1b *respon = store + 2048;

    snprintf(store,2048,html,nama,umur);
    snprintf(respon,2048,resp,strlen(store));

    ptr_1b *body = respon + strlen(respon);
    memcpy(body,store,strlen(store) + 1);
    send(clientFd,respon,strlen(respon),0);
  }

  close(clientFd);
}


void* init_mem(){
   return mmap(NULL,(4096 * 3),PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
};

int init(){
   int sockfd = socket(AF_INET,SOCK_STREAM,0);

   struct sockaddr_in dest;
   dest.sin_family = AF_INET;
   dest.sin_port = htons(80);
   dest.sin_addr.s_addr = INADDR_ANY;

   bind(sockfd,(struct sockaddr*)&dest,sizeof(dest));
   listen(sockfd,5);

   return sockfd;
};

void server(int fd,ptr_1b *page){
  while(1){
    http_url_parse(page,accept(fd,NULL,NULL));
  }
}

int main(){
   server(init(),(ptr_1b*)init_mem());
};

