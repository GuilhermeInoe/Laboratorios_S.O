// graceful_shutdown.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

FILE *log_file;

void finaliza(int signum) {
    printf("\n[SIGNAL] Recebido sinal %d, finalizando de forma segura...\n", signum);
    if (log_file) {
        fprintf(log_file, "Finalização segura (signal %d)\n", signum);
        fclose(log_file);
    }
    exit(0);
}

int main() {
    signal(SIGINT, finaliza);
    signal(SIGTERM, finaliza);

    log_file = fopen("log.txt", "a");
    if (!log_file) {
        perror("Erro ao abrir log.txt");
        return 1;
    }

    char buffer[256];
    while (1) {
        printf("Digite uma mensagem (Ctrl+C para sair): ");
        if (fgets(buffer, sizeof(buffer), stdin)) {
            fprintf(log_file, "Log: %s", buffer);
            fflush(log_file);
        }
    }

    return 0;
}
