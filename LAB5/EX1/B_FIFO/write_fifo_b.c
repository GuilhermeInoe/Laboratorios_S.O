// fifo_writer.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int a, b;
    char op;

    // Cria FIFO se não existir
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        // pode existir, então ignore erro
    }

    printf("Digite a expressão (ex: 3 + 4): ");
    scanf("%d %c %d", &a, &op, &b);

    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open fifo para escrita");
        exit(1);
    }

    // envia a expressão em formato string "3 + 4"
    char buf[100];
    snprintf(buf, sizeof(buf), "%d %c %d", a, op, b);
    write(fd, buf, strlen(buf) + 1);  // envia o '\0'

    close(fd);
    return 0;
}
