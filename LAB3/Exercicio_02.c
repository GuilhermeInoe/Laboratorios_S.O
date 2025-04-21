#include "matriz/matriz.h" // Biblioteca fornecida
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <string.h>

// Valores padrão
#define THREADS 4
#define LINHAS 10
#define COLUNAS 10
#define ENTRADA "nenhum arquivo selecionado"
#define SAIDA "nenhum nome fornecido"

// Struct para passar argumentos para as threads
struct thread_args {
    int thread_id;
    int pos_inicial;
    int pos_final;
    int n_linha;
    int n_coluna;
    int **matriz;
    FILE *output;
};

// Função para calcular a média aritmética das linhas:
void *media_aritmetica_linha(void *arg);

// Função para calcular a média geométrica das colunas:
void *media_geometrica_coluna (void *arg);

int main(int argc, char *argv[]) {
    // Variáveis
    int n_de_threads = THREADS;
    int n_linhas = LINHAS;
    int n_colunas = COLUNAS;
    char *arquivo_de_entrada = ENTRADA;
    char *arquivo_de_saida = SAIDA;

    // Cria um arquivo com os resultados das médias
    FILE *output = fopen("saida.txt", "w");
    if (!output) {
        perror("Erro ao abrir 'saida.txt'");
        exit(EXIT_FAILURE);
    }
    
    // Valores definidos via linha de comando
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "-t") && i + 1 < argc) {
                n_de_threads = atoi(argv[i+1]);
                i++;
            } else if (!strcmp(argv[i], "-l") && i + 1 < argc) {
                n_linhas = atoi(argv[i+1]);
                i++;
            } else if (!strcmp(argv[i], "-c") && i + 1 < argc) {
                n_colunas = atoi(argv[i+1]);
                i++;
            } else if (!strcmp(argv[i], "-e") && i + 1 < argc) {
                arquivo_de_entrada = argv[i+1];
                i++;
            } else if (!strcmp(argv[i], "-s") && i + 1 < argc) {
                arquivo_de_saida = argv[i+1];
                i++;
            } else {
                printf("Argumento desconhecido na posição %i\n", i);
            }
        }
    }

    // Mostrar os valores obtidos
    printf("Threads       : %d\n", n_de_threads);
    printf("Linhas        : %d\n", n_linhas);
    printf("Colunas       : %d\n", n_colunas);
    printf("Arquivo entrada: %s\n", arquivo_de_entrada);
    printf("Arquivo saída  : %s\n", arquivo_de_saida);

    struct thread_args dados[n_de_threads];

    // Cria uma matriz e preenche com valores aleatórios
    int **matriz_exemplo = create_matrix(n_linhas, n_colunas);
    srand(time(NULL));   // inicializa o gerador com uma semente.
    generate_elements(matriz_exemplo, n_linhas, n_colunas, 99);

    // Le a matriz de um arquivo externo
    if (strcmp(arquivo_de_entrada,ENTRADA))
    {
      matriz_exemplo = read_matrix_from_file(arquivo_de_entrada, &n_linhas, &n_colunas);
    } 

    // Criação das threads para a média aritmética das linhas
    pthread_t t_linhas[n_de_threads];
    int parcela_da_thread = n_linhas / n_de_threads;
    int inicio = 0, fim = parcela_da_thread;

    for (int i = 0; i < n_de_threads; i++) {
        dados[i].thread_id = i;
        dados[i].pos_inicial = inicio;
        dados[i].pos_final = fim;
        dados[i].n_linha = n_linhas;
        dados[i].n_coluna = n_colunas;
        dados[i].matriz = matriz_exemplo;
        dados[i].output = output;
        
        inicio = fim + 1;
        fim += parcela_da_thread;
    }
    dados[n_de_threads - 1].pos_final = n_linhas; // Ajuste final para a última thread

    // Criar threads para média aritmética das linhas
    for (int i = 0; i < n_de_threads; i++) {
        pthread_create(&t_linhas[i], NULL, media_aritmetica_linha, &dados[i]);
    }

    // Aguardar as threads para média aritmética das linhas
    for (int i = 0; i < n_de_threads; i++) {
        pthread_join(t_linhas[i], NULL);
    }

    // Criação das threads para a média geométrica das colunas
    pthread_t t_colunas[n_de_threads];
    parcela_da_thread = n_colunas / n_de_threads;
    inicio = 0, fim = parcela_da_thread;

    for (int i = 0; i < n_de_threads; i++) {
        dados[i].thread_id = i;
        dados[i].pos_inicial = inicio;
        dados[i].pos_final = fim;
        dados[i].n_linha = n_linhas;
        dados[i].n_coluna = n_colunas;
        dados[i].matriz = matriz_exemplo;
        dados[i].output = output;

        inicio = fim + 1;
        fim += parcela_da_thread;
    }
    dados[n_de_threads - 1].pos_final = n_colunas; // Ajuste final para a última thread

    // Criar threads para média geométrica das colunas
    for (int i = 0; i < n_de_threads; i++) {
        pthread_create(&t_colunas[i], NULL, media_geometrica_coluna, &dados[i]);
    }

    // Aguardar as threads para média geométrica das colunas
    for (int i = 0; i < n_de_threads; i++) {
        pthread_join(t_colunas[i], NULL);
    } 
    
    // Gerar um arquivo com a matriz
    if (strcmp(arquivo_de_saida, SAIDA)) {
      write_matrix_to_file(arquivo_de_saida, matriz_exemplo, n_linhas, n_colunas);
    }    
    return 0;
}

// Função para calcular a média aritmética das linhas
void *media_aritmetica_linha(void *arg) {
    struct thread_args *args = (struct thread_args *) arg;

    for (int i = args->pos_inicial; i < args->pos_final; i++) {
        double soma = 0.0;
        for (int j = 0; j < args->n_coluna; j++) {
            soma += args->matriz[i][j];
        }
        double media = soma / args->n_coluna;
        fprintf(args->output, "[Thread %d] Média aritmética da linha %d = %.2f\n", args->thread_id, i, media);
      }

    pthread_exit(NULL);
}

// Função para calcular a média geométrica das colunas
void *media_geometrica_coluna(void *arg) {
    struct thread_args *args = (struct thread_args *) arg;

    for (int j = args->pos_inicial; j < args->pos_final; j++) {
        double produto = 1.0;
        for (int i = 0; i < args->n_linha; i++) {
            // Evitar multiplicar por zero
            if (args->matriz[i][j] == 0)
                continue;
            produto *= args->matriz[i][j];
        }
        double media = pow(produto, 1.0 / args->n_linha);
        fprintf(args->output, "[Thread %d] Média geométrica da coluna %d = %.2f\n", args->thread_id, j, media);
      }

    pthread_exit(NULL);
}
