// config_reload.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define CONFIG_FILE "config.txt"

char default_dir[100] = "";
char owner[100] = "";

void load_config() {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo de configuração");
        return;
    }

    fscanf(file, "default_dir=%s\n", default_dir);
    fscanf(file, "owner=%s\n", owner);

    fclose(file);
}

void handle_sighup(int signum) {
    printf("\n[SIGNAL] Recebido SIGHUP (%d), recarregando configurações...\n", signum);
    load_config();
}

void show_menu() {
    printf("\n--- Menu ---\n");
    printf("1. Mostrar configurações\n");
    printf("2. Sair\n");
}

int main() {
    signal(SIGHUP, handle_sighup);
    load_config();

    int choice;
    while (1) {
        show_menu();
        printf("Escolha: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Diretório padrão: %s\n", default_dir);
            printf("Dono: %s\n", owner);
        } else if (choice == 2) {
            break;
        }
    }

    return 0;
}
