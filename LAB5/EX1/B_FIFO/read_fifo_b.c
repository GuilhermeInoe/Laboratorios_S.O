// fifo_reader.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open fifo para leitura");
        exit(1);
    }

    char buf[100];
    int n = read(fd, buf, sizeof(buf));
    if (n <= 0) {
        printf("Erro na leitura do fifo\n");
        close(fd);
        exit(1);
    }

    int a, b;
    char op;
    sscanf(buf, "%d %c %d", &a, &op, &b);

    int result;
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) {
                printf("Erro: divisão por zero\n");
                close(fd);
                return 1;
            }
            result = a / b; break;
        default:
            printf("Operação inválida\n");
            close(fd);
            return 1;
    }

    printf("Resultado: %d\n", result);

    close(fd);
    return 0;
}
