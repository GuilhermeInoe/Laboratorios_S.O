// produtor.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

struct Livro {
    char titulo[40];
    char autor[30];
    int num_paginas;
};

int main() {
    const char *name = "/livro_shm";
    const int SIZE = sizeof(struct Livro);

    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Erro ao criar memória compartilhada");
        exit(1);
    }

    ftruncate(shm_fd, SIZE);

    void *ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Erro ao mapear memória");
        exit(1);
    }

    struct Livro *livro = (struct Livro *) ptr;

    printf("Digite o título do livro: ");
    fgets(livro->titulo, sizeof(livro->titulo), stdin);
    livro->titulo[strcspn(livro->titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets(livro->autor, sizeof(livro->autor), stdin);
    livro->autor[strcspn(livro->autor, "\n")] = '\0';

    printf("Digite o número de páginas: ");
    scanf("%d", &livro->num_paginas);

    printf("Livro escrito na memória compartilhada!\n");

    munmap(ptr, SIZE);
    close(shm_fd);
    return 0;
}

