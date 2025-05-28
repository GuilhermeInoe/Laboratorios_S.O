//  - Descrição:...........Implementação do problema dos leitores/escritores utilizando semáforos
//  - Autor:...............Joao Pedro Inoe Araujo
//  - Data de criação:.....27/05/2025
//  - Data de atualização:.27/05/2025

/*
Implementação do problema dos Leitores e Escritores com prioridade para leitores.
O problema é resolvido utilizando um monitor implementado em C, com semáforos em vez de
variáveis de condição e mutexes. Essa abordagem é funcional, embora menos alinhada ao 
conceito clássico de monitores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "monitor.h"

#define N_Leitores 10   //Número de leitores
#define N_Escritores 5  //Número de escritores

//Assinaturas das funções para threads:
void* Leitores_func();
void* Escritores_func();

int main(){
    init_monitor();//função definida em 'monitor.c'
    
    //declaração das threads:
    pthread_t Leitores[N_Leitores],Escritores[N_Escritores];
    
    //laços para criar as threads:
    for (int i = 0; i < N_Leitores; i++)
    {
        int *id = malloc(sizeof(int));//alocação dinâmica para enviar um identificador da thread como argumento
        *id = i;
        pthread_create(&Leitores[i],NULL,&Leitores_func,id);
    }
    for (int i = 0; i < N_Escritores; i++)
    {
        int *id = malloc(sizeof(int));//alocação dinâmica para enviar um identificador da thread como argumento
        *id = i;
        pthread_create(&Escritores[i],NULL,&Escritores_func,id);
    }
    
    // Aguarda a finalização das threads:
    for (int i = 0; i < N_Leitores; i++)
    {
        pthread_join(Leitores[i],NULL);
    }
    for (int i = 0; i < N_Escritores; i++)
    {
        pthread_join(Escritores[i],NULL);
    }

    destroy_monitor();//função definida em 'monitor.c'    
    return 0;
}

void* Escritores_func(void* args){
    monitor_write(args);
}

void* Leitores_func(void* args){
    monitor_read(args);
}
