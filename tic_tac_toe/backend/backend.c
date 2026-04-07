#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <bsd/stdlib.h>
#include <bsd/unistd.h>
#include "netResource.h"
#include "ttt_resource.h"
#include "pthread_resource.h"
#include <stdio.h>

void winDetect(int Client1,int Client2,char winControl){
   char sendToLost[3] = {11,data[0],data[1]};
   if(winControl == 0){
      send(Client1,win_code,1,0);
      send(Client2,sendToLost,3,0);
      return;
   }
   send(Client2,&win_code[0],1,0);
   send(Client1,sendToLost,3,0);
};

void init(){
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  server_init.sin_family = AF_INET;
  server_init.sin_port = htons(8080);
  server_init.sin_addr.s_addr = INADDR_ANY;

  bind(sockfd,(struct sockaddr*)&server_init,sizeof(server_init));
  listen(sockfd,2);
  memset(column,0,10);
}

void accept_init(){
  char counter = 0;
  gohere:
  pthread_mutex_lock(&lock);
  while(1){
    int clientFd = accept(sockfd,NULL,NULL);
    clientSockFd[counter] = clientFd;
    counter++;
    if(counter == 2){
      break;
    }
  }
  counter = 0;
  pthread_cond_signal(&cond_var);
  pthread_cond_wait(&control_accept_init,&lock);
  pthread_mutex_unlock(&lock);
  sleep(5);
  goto gohere;
}

void *Logic_Thread(void* args){
   gohere:
   pthread_mutex_lock(&lock);
   pthread_cond_wait(&cond_var,&lock);

   char drawCounter = 0;
   char rand_idx = arc4random_uniform(2);
   char sendPlayer[2] = {13,symbol[rand_idx]};

   if(rand_idx == 0){
      send(clientSockFd[rand_idx],sendPlayer,2,0);

      sendPlayer[0] = 14;
      sendPlayer[1] = symbol[rand_idx + 1];
      send(clientSockFd[rand_idx + 1],sendPlayer,2,0);

      while(1){
         recv(clientSockFd[rand_idx],data,2,0);
         column[data[0]] = data[1];
         drawCounter++;

         // logic check
         if(column[1] == data[1] && column[2] == data[1] && column[3] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[4] == data[1] && column[5] == data[1] && column[6] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[7] == data[1] && column[8] == data[1] && column[9] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[1] == data[1] && column[4] == data[1] && column[7] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[2] == data[1] && column[5] == data[1] && column[8] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[3] == data[1] && column[6] == data[1] && column[9] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[1] == data[1] && column[5] == data[1] && column[9] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[3] == data[1] && column[5] == data[1] && column[7] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }
         //

         if(drawCounter == 9){
            draw[2] = data[0];
            draw[3] = data[1];
            send(clientSockFd[rand_idx],&draw[0],2,0);
            draw[1] = 2;
            if(rand_idx == 0){
               send(clientSockFd[rand_idx + 1],&draw[0],4,0);
               break;
            }
            send(clientSockFd[rand_idx - 1],&draw[0],4,0);
         }

         send(clientSockFd[((rand_idx == 0) ? 1 : 0)],data,2,0);
         rand_idx++;
         if(rand_idx == 2){
            rand_idx = 0;
         }
      }
   }else if(rand_idx == 1){
      send(clientSockFd[rand_idx],sendPlayer,2,0);

      sendPlayer[0] = 14;
      sendPlayer[1] = symbol[rand_idx - 1];
      send(clientSockFd[rand_idx - 1],sendPlayer,2,0);

      while(1){
         recv(clientSockFd[rand_idx],data,2,0);
         column[data[0]] = data[1];
         drawCounter++;

         // logic check
         if(column[1] == data[1] && column[2] == data[1] && column[3] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[4] == data[1] && column[5] == data[1] && column[6] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[7] == data[1] && column[8] == data[1] && column[9] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[1] == data[1] && column[4] == data[1] && column[7] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[2] == data[1] && column[5] == data[1] && column[8] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[3] == data[1] && column[6] == data[1] && column[9] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[1] == data[1] && column[5] == data[1] && column[9] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }else if(column[3] == data[1] && column[5] == data[1] && column[7] == data[1]){
            winDetect(clientSockFd[0],clientSockFd[1],rand_idx);
            break;
         }
         //

         if(drawCounter == 9){
            draw[2] = data[0];
            draw[3] = data[1];
            send(clientSockFd[rand_idx],&draw[0],2,0);
            draw[1] = 2;
            if(rand_idx == 0){
               send(clientSockFd[rand_idx + 1],&draw[0],4,0);
               break;
            }
            send(clientSockFd[rand_idx - 1],&draw[0],4,0);
         }

         send(clientSockFd[((rand_idx == 1) ? 0 : 1)],data,2,0);
         rand_idx--;
         if(rand_idx == -1){
            rand_idx = 1;
         }
      }
   }
   close(clientSockFd[0]);
   close(clientSockFd[1]);
   memset(column,0,10);
   pthread_cond_signal(&control_accept_init);
   pthread_mutex_unlock(&lock);
   goto gohere;
}

int main(){
  init();

  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&cond_var,NULL);
  pthread_cond_init(&control_accept_init,NULL);

  pthread_t thread_logic;
  pthread_create(&thread_logic,NULL,Logic_Thread,NULL);
  sleep(5);

  accept_init();
}
