// consumidor.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

struct Livro {
    char titulo[40];
    char autor[30];
    int num_paginas;
};

int main() {
    const char *name = "/livro_shm";
    const int SIZE = sizeof(struct Livro);

    int shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("Erro ao abrir memória compartilhada");
        exit(1);
    }

    void *ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Erro ao mapear memória");
        exit(1);
    }

    struct Livro *livro = (struct Livro *) ptr;

    printf("LIVRO LIDO DA MEMÓRIA COMPARTILHADA:\n");
    printf("Título: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Páginas: %d\n", livro->num_paginas);

    munmap(ptr, SIZE);
    close(shm_fd);

    // Remove a memória compartilhada após leitura (se for o último processo)
    shm_unlink(name);

    return 0;
}

