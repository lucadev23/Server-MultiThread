#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include"def.h"

int main(void){
    int serverfd, clientfd;
    int *threadfd;
    int req,res;
    struct sockaddr_in server_address,client_address;
    socklen_t server_len,client_len;
    int flag=1; //per usi futuri
    pthread_t tid;
    int count=0;

    serverfd=socket(AF_INET,SOCK_STREAM,0);
    if(serverfd==-1){
        error("Errore creazione socket\n\0");
    }
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=inet_addr(ADDR);
    server_address.sin_port=htons(PORT);
    server_len=(socklen_t)sizeof(server_address);
    if(bind(serverfd,(struct sockaddr*)&server_address,server_len)==-1){
        error("Impossibile fare la bind()\n\0");
    }
    if(listen(serverfd,N_CLIENT)==-1){
        error("Impossibile impostare il numero di client\n\0");
    }

    while(flag){
        client_len=(socklen_t)sizeof(client_address);
        if((clientfd=accept(serverfd,(struct sockaddr*)&client_address,&client_len)) == -1){
            error("Errore accept() client\n\0");
        }
        threadfd=(int*)malloc(sizeof(int));
        *threadfd=clientfd; //passo il fd al thread, altrimenti viene sovrascritto
        if(pthread_create(&tid,NULL,connection_Handler,(void*)threadfd)==-1){
            error("Errore creazione thread\n\0");
        }
        count++;
        fprintf(stdout,"Collegamento %d\n",count);
        pthread_detach(tid);
    }
    close(serverfd);
}