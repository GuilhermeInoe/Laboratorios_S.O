#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 512

/* Função para contar vogais, consoantes e espaços */
void contar_caracteres(const char *str, int *vogais, int *consoantes, int *espacos) {
    *vogais = *consoantes = *espacos = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        char c = tolower(str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            (*vogais)++;
        } else if (isalpha(c)) {
            (*consoantes)++;
        } else if (c == ' ') {
            (*espacos)++;
        }
    }
}

/* Leitura no processo filho */
void read_from_pipe(int file) {
    FILE *stream = fdopen(file, "r");
    char buffer[MAX_LEN];

    if (fgets(buffer, MAX_LEN, stream) != NULL) {
        // Remover o '\n' do final, se houver
        buffer[strcspn(buffer, "\n")] = '\0';

        printf("Filho recebeu: \"%s\"\n", buffer);
        printf("Tamanho: %lu\n", strlen(buffer));

        int vogais, consoantes, espacos;
        contar_caracteres(buffer, &vogais, &consoantes, &espacos);

        printf("Vogais: %d | Consoantes: %d | Espaços: %d\n", vogais, consoantes, espacos);
    }

    fclose(stream);
}

/* Escrita no processo pai */
void write_to_pipe(int file) {
    FILE *stream = fdopen(file, "w");
    char buffer[MAX_LEN];

    printf("Pai: digite uma string: ");
    scanf(" %[^\n]", buffer);  // lê até o Enter (inclui espaços)

    fprintf(stream, "%s\n", buffer);  // envia a string com '\n' para facilitar fgets
    fclose(stream);
}

/* Programa principal */
int main(void) {
    pid_t pid;
    int mypipe[2];

    if (pipe(mypipe)) {
        fprintf(stderr, "Falha ao criar o Pipe.\n");
        return EXIT_FAILURE;
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Falha ao executar o Fork.\n");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // Processo filho
        close(mypipe[1]); // fecha escrita
        read_from_pipe(mypipe[0]);
        return EXIT_SUCCESS;
    } else {
        // Processo pai
        close(mypipe[0]); // fecha leitura
        write_to_pipe(mypipe[1]);
        return EXIT_SUCCESS;
    }
}

