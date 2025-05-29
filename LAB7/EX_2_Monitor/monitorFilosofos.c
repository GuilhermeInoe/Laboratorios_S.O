// - Descrição:............ Jantar dos filósofs implementado usando monitor
// // - Autor:................ Henry Meneguini Farias 
// - Data de Criação:...... 29/05/2025
// - Data de Atualização:.. 29/05/2025

#include <stdio.h>
#include <pthread.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2



typedef struct {
   int state[N];
   pthread_mutex_t mutex;
   pthread_cond_t cond[N];

} Monitor;

Monitor m;
void think(int i){
   printf("Philosopher %d is thinking...\n", i);
}

void eat(int i){
   printf("Philosopher %d is eating...\n", i);
}

void init_monitor(Monitor* m){
   pthread_mutex_init(&m->mutex, NULL);
   for(int i = 0; i < N; i++){
      m->state[i] = THINKING;
      pthread_cond_init(&m->cond[i], NULL);
   }
}

void test(Monitor* m, int i){
   if(m->state[i] == HUNGRY &&
      m->state[LEFT] != EATING &&
      m->state[RIGHT] != EATING){
      m->state[i] = EATING;
      pthread_cond_signal(&m->cond[i]);
   }
}

void put_forks(Monitor* m, int i){
   pthread_mutex_lock(&m->mutex);
   m->state[i] = THINKING;
   test(m, LEFT);
   test(m, RIGHT);
   pthread_mutex_unlock(&m->mutex);
}

void take_forks(Monitor* m, int i){
   pthread_mutex_lock(&m->mutex);
   m->state[i] = HUNGRY;
   test(m, i);
   while(m->state[i] != EATING){
      pthread_cond_wait(&m->cond[i], &m->mutex);
   }
   pthread_mutex_unlock(&m->mutex);
}

void* philosopher(void* philo){
   int i = *(int*)philo;
   while(1){
      think(i);
      take_forks(&m, i);
      eat(i);
      put_forks(&m, i);
   }
}

int main(){
   pthread_t threads[N];
   int ids[N];

   init_monitor(&m);

   for(int i = 0; i < N; i++){
      ids[i] = i;
      pthread_create(&threads[i], NULL, &philosopher, &ids[i]);
   }

   for(int i = 0; i < N; i++){
      pthread_join(threads[i], NULL);
   }
}
