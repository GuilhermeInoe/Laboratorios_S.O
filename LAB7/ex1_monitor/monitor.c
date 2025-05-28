#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "monitor.h"

sem_t mutex_counter;    //controla o acesso ao contador de leitores
sem_t mutex_area;       //controla o acesso a região critica

// Recurso compartilhado:
int recurso = 0;

// Contador de Leitores:
int counter_leitores = 0;

//função para iniciar o monitor
void init_monitor(){
    sem_init(&mutex_counter,0,1);
    sem_init(&mutex_area,0,1);
}

//função para liberar memória alocada para o monitor
void destroy_monitor(){
    sem_destroy(&mutex_area);
    sem_destroy(&mutex_counter);
}

//função para que as threads escritor irão executar
void monitor_write(void* index){
    while (1)
    {
        sem_wait(&mutex_area);  //lock da região crítica
        recurso++;              //escreve no recurso (incrementa)
        printf("[Escritor:%d] recurso vale: %d\n",*(int*)index,recurso);
        sem_post(&mutex_area);  //unlock da região crítica
        sleep(1);
    }
    free(index);
}

//função para que as threads leitor irão executar
void monitor_read(void* index){
    while (1)
    {
        sem_wait(&mutex_counter);   //lock do contador de leitores
        counter_leitores++;         //incrementa o contador de leitores
        if (counter_leitores==1)    //se for o primeiro leitor 
        {
            sem_wait(&mutex_area);  //bloqueia o acesso dos escritores 
        }
        sem_post(&mutex_counter);   //unlock do contador de leitores
        
        printf("[Leitor:%d] recurso vale: %d \n",*(int*)index,recurso);//faz a leitura do recurso
        
        sem_wait(&mutex_counter);   //lock do contador de leitores
        counter_leitores--;         //decrementa 
        if (counter_leitores==0)    //se for o último leitor 
        {
            sem_post(&mutex_area);  //libera o acesso para os escritores 
        }
        sem_post(&mutex_counter);   //unlock contador de leitores
        sleep(1);
    }
    free(index);
}