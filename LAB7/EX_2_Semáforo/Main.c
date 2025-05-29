
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define LEFT(i) ((i + N - 1) % N)
#define RIGHT(i) ((i + 1) % N)

typedef enum { THINKING, HUNGRY, EATING } state_t;

typedef struct {
    state_t state[N];
    pthread_mutex_t mutex;
    pthread_cond_t cond[N];
} Monitor;

// Funções do monitor
Monitor monitor;

void monitor_init() {
    pthread_mutex_init(&monitor.mutex, NULL);
    for (int i = 0; i < N; i++) {
        monitor.state[i] = THINKING;
        pthread_cond_init(&monitor.cond[i], NULL);
    }
}

void test(int i) {
    if (monitor.state[i] == HUNGRY &&
        monitor.state[LEFT(i)] != EATING &&
        monitor.state[RIGHT(i)] != EATING) {
        monitor.state[i] = EATING;
        pthread_cond_signal(&monitor.cond[i]);
    }
}

void enter(int i) {
    pthread_mutex_lock(&monitor.mutex);
    monitor.state[i] = HUNGRY;
    test(i);
    while (monitor.state[i] != EATING) {
        pthread_cond_wait(&monitor.cond[i], &monitor.mutex);
    }
    pthread_mutex_unlock(&monitor.mutex);
}

void leave(int i) {
    pthread_mutex_lock(&monitor.mutex);
    monitor.state[i] = THINKING;
    test(LEFT(i));
    test(RIGHT(i));
    pthread_mutex_unlock(&monitor.mutex);
}

// Funções dos filósofos
void think(int i) {
    printf("Filósofo %d está pensando...\n", i);
    sleep(1);
}

void eat(int i) {
    printf("Filósofo %d está comendo!\n", i);
    sleep(1);
}

void* philosopher(void* arg) {
    int i = *(int*)arg;
    while (1) {
        think(i);
        enter(i);
        eat(i);
        leave(i);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    monitor_init();

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

