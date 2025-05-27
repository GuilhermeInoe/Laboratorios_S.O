//  - Descrição:...........Implementação do problema dos leitores/escritores utilizando semáforos
//  - Autor:...............Guilherme Inoe Araujo
//  - Data de criação:.....27/05/2025
//  - Data de atualização:.27/05/2025

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#include <unistd.h>

//todos podem ler
//somente um por vez pode alterar
//enquanto um altera, ninguém pode ler

int numLeitores = 0;  // contador de leitores
sem_t mutex;          // semáforo para acesso ao numero de leitores
sem_t semEscritor;    // semáforo para controlar acesso de escritores

int valorEscrito;     // foi adicionada para exibir no terminal o valor escrito.

void *Escritor(void *arg) {
  int id = *(int *)arg;
  int contador = 0;
  while (contador < 5) {
    // acessa a seção crítica
    sem_wait(&semEscritor);

    //fazer o escritor escrever um valor qualquer 
    valorEscrito = rand() % 100;
    printf("Escritor %d está escrevendo o valor: %d\n", id, valorEscrito);

    // libera a seção crítica
    sem_post(&semEscritor);

    contador++;
    sleep(2);
  }

  printf("Escritor %d parou de escrever\n", id);
  pthread_exit(0);
}

void *Leitor(void *arg) {
  int id = *(int *)arg;

  int contador = 0;
  while (contador < 5) {
    // entrada na seção crítica
    sem_wait(&mutex);
    numLeitores++;
    if (numLeitores == 1) //verifica se é o primeiro leitor.
      sem_wait(&semEscritor); // bloqueia escritores. Eles não podem escrever durante uma leitura
    sem_post(&mutex);

  
    printf("Leitor %d está lendo o valor %d\n", id, valorEscrito);

    // saída da seção crítica
    sem_wait(&mutex);
    numLeitores--;
    if (numLeitores == 0) // desbloquear os escritores. Último leitor terminou de ler
      sem_post(&semEscritor); 
    sem_post(&mutex);

    sleep(1);
    contador++;
  }

  printf("Leitor %d parou de ler\n", id);
  pthread_exit(0);
}

int main() {
  int num_readers = 5;
  int num_semEscritors = 2;
  pthread_t readers[num_readers], semEscritors[num_semEscritors];
  int id_readers[num_readers], id_semEscritors[num_semEscritors];

  // inicializa os semáforos
  sem_init(&mutex, 0, 1);
  sem_init(&semEscritor, 0, 1);

  // cria as threads escritores
  for (int i = 0; i < num_semEscritors; i++) {
    id_semEscritors[i] = i + 1;
    pthread_create(&semEscritors[i], NULL, Escritor, &id_semEscritors[i]);
  }

  // cria as threads leitores
  for (int i = 0; i < num_readers; i++) {
    id_readers[i] = i + 1;
    pthread_create(&readers[i], NULL, Leitor, &id_readers[i]);
  }

  // espera as threads terminarem
  for (int i = 0; i < num_readers; i++) {
    pthread_join(readers[i], NULL);
  }

  for (int i = 0; i < num_semEscritors; i++) {
    pthread_join(semEscritors[i], NULL);
  }

  // destrói os semáforos
  sem_destroy(&mutex);
  sem_destroy(&semEscritor);

  return 0;
}