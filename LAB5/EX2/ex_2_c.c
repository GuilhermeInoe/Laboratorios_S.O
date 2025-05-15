// countdown_on_sigint.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t countdown_triggered = 0;

void handle_sigint(int signum) {
    countdown_triggered = 1;
    alarm(10);
}

void handle_alarm(int signum) {
    printf("\nTempo esgotado. Encerrando.\n");
    exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);
    signal(SIGALRM, handle_alarm);

    printf("Programa rodando. Pressione Ctrl+C para iniciar contagem regressiva.\n");

    while (1) {
        if (countdown_triggered) {
            for (int i = 10; i > 0; --i) {
                printf("Encerrando em %d segundos...\n", i);
                sleep(1);
            }
        } else {
            pause(); // espera por sinal
        }
    }

    return 0;
}
