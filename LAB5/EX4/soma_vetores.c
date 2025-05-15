#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

typedef struct {
    int start;
    int end;
} Intervalo;

int main() {
    int numElementos, numProcessos;

    printf("Digite o número de elementos do vetor: ");
    scanf("%d", &numElementos);

    printf("Digite o número de processos: ");
    scanf("%d", &numProcessos);

    if (numElementos <= 0 || numProcessos <= 0 || numProcessos > numElementos) {
        fprintf(stderr, "Número inválido de elementos ou processos.\n");
        return 1;
    }

    size_t size = numElementos * sizeof(int);
    size_t sinalizacao_size = numProcessos * sizeof(int);

    int shm_v1 = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666);
    int shm_v2 = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666);
    int shm_v3 = shmget(IPC_PRIVATE, size, IPC_CREAT | 0666);
    int shm_done = shmget(IPC_PRIVATE, sinalizacao_size, IPC_CREAT | 0666);

    if (shm_v1 < 0 || shm_v2 < 0 || shm_v3 < 0 || shm_done < 0) {
        perror("Erro ao criar memória compartilhada");
        exit(1);
    }

    int *v1 = shmat(shm_v1, NULL, 0);
    int *v2 = shmat(shm_v2, NULL, 0);
    int *v3 = shmat(shm_v3, NULL, 0);
    int *done = shmat(shm_done, NULL, 0);

    printf("Digite os %d elementos de V1:\n", numElementos);
    for (int i = 0; i < numElementos; i++) {
        scanf("%d", &v1[i]);
    }

    printf("Digite os %d elementos de V2:\n", numElementos);
    for (int i = 0; i < numElementos; i++) {
        scanf("%d", &v2[i]);
        v3[i] = 0;
    }

    for (int i = 0; i < numProcessos; i++) done[i] = 0;

    int pipes[numProcessos][2];
    for (int i = 0; i < numProcessos; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Erro ao criar pipe");
            exit(1);
        }
    }

    for (int i = 0; i < numProcessos; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            close(pipes[i][1]);
            Intervalo intervalo;
            read(pipes[i][0], &intervalo, sizeof(Intervalo));
            close(pipes[i][0]);

            int *v1_f = shmat(shm_v1, NULL, 0);
            int *v2_f = shmat(shm_v2, NULL, 0);
            int *v3_f = shmat(shm_v3, NULL, 0);
            int *done_f = shmat(shm_done, NULL, 0);

            for (int j = intervalo.start; j < intervalo.end; j++) {
                v3_f[j] = v1_f[j] + v2_f[j];
            }

            done_f[i] = 1;

            shmdt(v1_f);
            shmdt(v2_f);
            shmdt(v3_f);
            shmdt(done_f);
            exit(0);
        }
    }

    int elementosPorProcesso = numElementos / numProcessos;
    int resto = numElementos % numProcessos;
    int atual = 0;
    for (int i = 0; i < numProcessos; i++) {
        close(pipes[i][0]);
        Intervalo intervalo;
        intervalo.start = atual;
        intervalo.end = atual + elementosPorProcesso + (i < resto ? 1 : 0);
        atual = intervalo.end;
        write(pipes[i][1], &intervalo, sizeof(Intervalo));
        close(pipes[i][1]);
    }

    int filhos_terminaram = 0;
    while (filhos_terminaram < numProcessos) {
        filhos_terminaram = 0;
        for (int i = 0; i < numProcessos; i++) {
            if (done[i] == 1) filhos_terminaram++;
        }
        usleep(1000);
    }

    printf("V1 = [");
    for (int i = 0; i < numElementos; i++) {
        printf("%d", v1[i]);
        if (i < numElementos - 1) printf(", ");
    }
    printf("], ");

    printf("V2 = [");
    for (int i = 0; i < numElementos; i++) {
        printf("%d", v2[i]);
        if (i < numElementos - 1) printf(", ");
    }
    printf("], ");

    printf("V3 = V1 + V2 = [");
    for (int i = 0; i < numElementos; i++) {
        printf("%d", v3[i]);
        if (i < numElementos - 1) printf(", ");
    }
    printf("]\n");

    for (int i = 0; i < numProcessos; i++) {
        wait(NULL);
    }

    shmdt(v1); shmdt(v2); shmdt(v3); shmdt(done);
    shmctl(shm_v1, IPC_RMID, NULL);
    shmctl(shm_v2, IPC_RMID, NULL);
    shmctl(shm_v3, IPC_RMID, NULL);
    shmctl(shm_done, IPC_RMID, NULL);

    return 0;
}

