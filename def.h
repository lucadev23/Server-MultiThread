#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>

#define PORT 4587
#define ADDR "127.0.0.1"
#define N_CLIENT 5


void error(char *s){
    fprintf(stderr,s);
    fprintf(stderr, "errno --> %s\n",strerror(errno));
    exit(EXIT_FAILURE);
}

void error_thread(char *s){
    fprintf(stderr,s);
    fprintf(stderr, "errno --> %s\n",strerror(errno));
    pthread_exit(NULL);
}

void *connection_Handler(void* arg){
    int clientfd=(*(int*)arg);
    char req,res;
    
    if(read(clientfd,&req,1)==-1){
        error_thread("Errore lettura messaggio\n\0");
    }
    fprintf(stdout,"Ho ricevuto %c\n",req);
    res=req+1;
    if(write(clientfd,&res,1)==-1){
        error_thread("Errore invio messaggio\n\0");
    }
    fprintf(stdout,"Ho mandato %c\n",res);
    close(clientfd);
    free(arg);
    pthread_exit(NULL);
}