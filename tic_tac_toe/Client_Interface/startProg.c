#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/Tic_Tac_Toe/backend/netResource.h"
#include "clientResource.h"
#include <arpa/inet.h>

void init(){
   sockfd = socket(AF_INET,SOCK_STREAM,0);
   server_init.sin_family = AF_INET;
   server_init.sin_port = htons(8080);
   inet_pton(AF_INET,"192.168.1.9",&server_init.sin_addr);
};

void Gameplay(int sockfd){
  while(1){
    printf("%s\n",column);
    if(server_code[0] == 14){
       printf("Other Player Playing\nWait For Your Turn\n");
       recv(sockfd,server_code,3,0);
       column[mid_idx[server_code[0]]] = server_code[1];
       system("clear");
       continue;
    }

    printf("%s(%c): ",player,column_input[1]);
    scanf(" %hhu",&column_input[0]);
    column[mid_idx[column_input[0]]] = column_input[1];
    system("clear");
    printf("%s\n",column);
    printf("Other Player Playing\nWait For Your Turn\n");

    send(sockfd,column_input,2,0);
    recv(sockfd,server_code,4,0);
    if(server_code[0] == 10){
       system("clear");
       printf("%s\n",column);
       printf("Congratulations You Win !\nClearing The Room...\n");
       sleep(3);
       return;
    }else if(server_code[0] == 11){
      column[mid_idx[server_code[1]]] = server_code[2];
      system("clear");
      printf("%s\n",column);
      printf("Opps You Lost !\nClearing The Room...\n");
      sleep(3);
      return;
    }else if(server_code[0] == 12){
      if(server_code[1] == 1){
         system("clear");
         printf("%s\n",column);
         printf("game is draw !\nClearing The Room...\n");
         sleep(3);
         return;
      }
      column[mid_idx[server_code[2]]] = server_code[3];
      system("clear");
      printf("%s\n",column);
      printf("game is draw !\nClearing The Room...\n");
      sleep(3);
      return;
    }
    column[mid_idx[server_code[0]]] = server_code[1];
    system("clear");
  }
};

void render_init(){
   if(server_code[0] == 14){
      player[6] = '2';
      return;
   }
   player[6] = '1';
};

void startGameplay(int sockfd){
  recv(sockfd,server_code,2,0);
  system("clear");
  column_input[1] = server_code[1]; //configure symbol

  render_init();
  printf("Game Started !\n");
  printf("You Played as = %s ",player);
  printf("Using = %c\n\n",column_input[1]);
  Gameplay(sockfd);
};


void startProg(){
  char menu;
  while(1){
    init();
    printf("(1). Start Game\n");
    printf("(2). Exit\n");
    printf("Choose Menu = ");
    scanf(" %c",&menu);
    if(menu == '2'){
      exit(1);
    }
    printf("Waiting For Other Player\n");
    connect(sockfd,(struct sockaddr*)&server_init,sizeof(server_init));
    startGameplay(sockfd);
    strcpy(column,"   |   |   \n   |   |   \n   |   |   \n");
    system("clear");
    close(sockfd);
  }
};
