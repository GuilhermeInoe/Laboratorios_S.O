//  - Descrição:...........Código responsável por  processar um vetor e dividir para N filhos partes iguais de processamento para localizar um item.
//  - Autor:...............João Pedro Inoe Araujo
//  - Data de criação:.....15/04/2025
//  - Data de atualização:.15/04/2025

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <tamanho> <num_filhos> <valor_procurado>\n", argv[0]);
        exit(1);
    }

    int tamanho = atoi(argv[1]);
    int num_filhos = atoi(argv[2]);
    int valor_procurado = atoi(argv[3]);

    if (tamanho <= 0 || num_filhos <= 0) {
        fprintf(stderr, "Erro: tamanho e número de filhos devem ser maiores que 0.\n");
        exit(1);
    }
    int *vetor = malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        perror("Erro ao alocar memória");
        exit(1);
    }

    srand(time(NULL));
    printf("Vetor gerado: ");
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 10;
        printf("%d ", vetor[i]);
    }
    printf("\n");

    for (int i = 0; i < num_filhos; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro no fork");
            exit(1);
        } else if (pid == 0) {
            int inicio = i * (tamanho / num_filhos);
            int fim = (i == num_filhos - 1) ? tamanho : inicio + (tamanho / num_filhos);

            for (int j = inicio; j < fim; j++) {
                if (vetor[j] == valor_procurado) {
                    printf("Filho PID %d encontrou o valor na posição %d\n", getpid(), j);
                }
            }

            exit(0);
        }
    }

    for (int i = 0; i < num_filhos; i++) {
        wait(NULL);
    }

    printf("Busca finalizada.\n");
    free(vetor);
    return 0;
}
