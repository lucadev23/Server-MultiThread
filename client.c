#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define PORT 4587
#define ADDR "127.0.0.1"

int main(void){
    int sockfd;
    struct sockaddr_in address;
    char req='c',res;
    socklen_t client_len;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        fprintf(stderr,"Impossibile creare la socket\n");
        exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_port=htons(PORT);
    address.sin_addr.s_addr=inet_addr(ADDR);
    client_len=sizeof(address);
    if(connect(sockfd,(struct sockaddr*)&address,sizeof(struct sockaddr_in))==-1){
        fprintf(stderr,"Impossibile connettersi al server\n");
        exit(EXIT_FAILURE);
    }
    if(write(sockfd,(void*)&req,1)==-1){
        fprintf(stderr,"Impossibile inviare la richiesta\n");
        exit(EXIT_FAILURE);
    }
    if(read(sockfd,(void*)&res,1)==-1){
        fprintf(stderr,"Impossibile ricevere la risposta\n");
        exit(EXIT_FAILURE);
    }
    printf("Il server mi ha mandato %c\n",res);
    close(sockfd);
    exit(EXIT_SUCCESS);
}
