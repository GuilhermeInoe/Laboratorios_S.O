/**
 * Escreve N mensagens para o FIFO
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SERVER_FIFO "/tmp/serverfifo"
#define BUF_SIZE 512

int main (int argc, char **argv)
{
    int fd_server;  // descritor para o FIFO
    char buf[BUF_SIZE];

    printf("Digite sua frase:\n");
    fgets(buf, BUF_SIZE, stdin);

    if ((fd_server = open (SERVER_FIFO, O_WRONLY)) == -1) {
        perror ("open error: server fifo");
        return 1;
    }

    //Escreve no FIFO
    write(fd_server, buf, strlen(buf));
        
    if (close (fd_server) == -1) {
        perror ("close error:server fifo");
        return 2;
    }
          
    return 0;
}

