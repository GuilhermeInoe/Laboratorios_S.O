#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LEN 100

void calcular(const char *expr) {
    int a, b;
    char op;

    sscanf(expr, "%d %c %d", &a, &op, &b);

    int result;
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) {
                printf("Erro: divisão por zero\n");
                return;
            }
            result = a / b; break;
        default:
            printf("Operação inválida\n");
            return;
    }

    printf("Resultado: %d\n", result);
}

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[MAX_LEN];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // filho - lê do pipe
        close(pipefd[1]); // fecha escrita

        read(pipefd[0], buffer, MAX_LEN);
        close(pipefd[0]);

        calcular(buffer);

        exit(EXIT_SUCCESS);
    } else { // pai - escreve no pipe
        close(pipefd[0]); // fecha leitura

        printf("Digite a expressão (ex: 3 + 4): ");
        fgets(buffer, MAX_LEN, stdin);

        write(pipefd[1], buffer, strlen(buffer)+1);
        close(pipefd[1]);

        wait(NULL);
    }

    return 0;
}

