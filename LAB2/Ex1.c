//  - Descrição:...........Código responsável por criar uma hierarquia de processos e permitir a visualização dos mesmos via pstree
//  - Autor:...............Guilherme Inoe Araujo
//  - Data de criação:.....13/04/2025
//  - Data de atualização:.13/04/2025
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>

int main(){
    int niveis;
    pid_t pidInicial = getpid();

    printf("Digite o valor N: \n");
    scanf("%d", &niveis);

    for (int i = 1; i < niveis;)
    {
        pid_t pid1 = 0;
        pid_t pid2 = 0;

        pid1 = fork();
        if(pid1) {
            pid2 = fork();
            pid1 = 0;
        }
        if(pid2){
            break;
        } 
        i++;
    }

    pid_t pidProc = getpid();


    if(pidProc == pidInicial) {
        sleep(1);
        printf("Árvore de processos:\n");
        char pidStr[10];
        sprintf(pidStr, "%d", pidInicial);
        char *args[] = {"pstree", "-c", pidStr, NULL};
        execvp("pstree", args);
        perror("execvp FALHOU!");
    } else {
        sleep(2);
    }

    return 0;
}
