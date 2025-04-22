//  - Descrição:.......... Código que cria N threads para localizar um valor em um vetor de M inteiros gerados aleatoriamente
//  - Autor:.............. André Felipe Baretta
//  - Data de criação:.... 21/04/2025
//  - Data de atualização: 21/04/2025

#include "lib/matriz.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct {
  int** matrix;       // matriz
  double* average_rows;  // vetor de media de linhas
  int row;            // linha a ser calculada
  int cols;           // quantidade de colunas
} average_row_params;

typedef struct {
  int** matrix;       // matriz
  double* average_cols;  // vetor de media de colunas
  int col;            // coluna a ser calculada
  int rows;           // quantidade de linhas
} average_col_params;

void* calculate_average_rows(void*);  // função para calcular a media das linhas
void* calculate_average_cols(void*);  // função para calcular a media das colunas 

int main(int argc, char* argv[]){
  // define os parâmetros

  // valores padrão
  int rows = 6;
  int columns = 8;
  int limit = 20;
  int read_only = 0; // false
  int rows_file_arg = 0;
  int cols_file_arg = 0;
  char file[100];
  char rows_file[100];
  char cols_file[100];
  strcpy(rows_file, "./media_linhas.out");
  strcpy(cols_file, "./media_colunas.out");
  int** matrix;
  
  // valores definidos pelo usuário
  if(argc > 1){
    for(int i = 1; i < argc; i++){
      if(!strcmp(argv[i], "-r") && i + 1 < argc){
        rows = atoi(argv[i+1]);
        i++;
      } else if(!strcmp(argv[i], "-c") && i + 1 < argc){
        columns = atoi(argv[i+1]);
        i++;
      } else if(!strcmp(argv[i], "-l") && i + 1 < argc){
        limit = atoi(argv[i+1]);
        i++;
      } else if(!strcmp(argv[i], "-f") && i + 1 < argc){
        read_only = 1;
        strcpy(file, argv[i+1]);
        i++;
      } else if(!strcmp(argv[i], "-rf") && i + 1 < argc){
        rows_file_arg = 1;
        strcpy(rows_file, argv[i+1]);
        i++;
      } else if(!strcmp(argv[i], "-cf") && i + 1 < argc){
        cols_file_arg = 1;
        strcpy(cols_file, argv[i+1]);
        i++;
      } else {
        printf("Argumento desconhecido na posição %i\n", i);
      }
    }
  }
  
  if(!read_only){   // se um caminho tiver sido passado para ler, o programa não cria o arquivo com os valores aleatórios 
    snprintf(file, sizeof(file), "matrizes/data_matriz_%i_%i.in", rows, columns);
    if(!rows_file_arg)
      snprintf(rows_file, sizeof(rows_file), "output/media_linhas_%i_%i.out", rows, columns);
    if(!cols_file_arg)
      snprintf(cols_file, sizeof(cols_file), "output/media_colunas_%i_%i.out", rows, columns);
    
    // cria e salva a matriz em um arquivo
    matrix = create_matrix(rows, columns);
    
    srand(time(NULL));
    
    generate_elements(matrix, rows, columns, limit);

    write_matrix_to_file(file, matrix, rows, columns);
    
    free_matrix(matrix, rows, columns);
  }

  // lê a matriz do arquivo
  
  int read_row;
  int read_col;
  matrix = read_matrix_from_file(file, &read_row, &read_col);

  double* average_cols = malloc(read_col * sizeof(double));
  double* average_rows = malloc(read_row * sizeof(double));

  pthread_t* rows_threads = malloc(read_row * sizeof(pthread_t));
  pthread_t* cols_threads = malloc(read_col * sizeof(pthread_t));
  average_row_params* rows_params = malloc(read_row * sizeof(average_row_params));
  average_col_params* cols_params = malloc(read_col * sizeof(average_col_params));

  // parametros para a leitura de colunas
  for(int i = 0; i < read_col; i++){
    cols_params[i].matrix = matrix;
    cols_params[i].average_cols = average_cols;
    cols_params[i].rows = read_row;
    cols_params[i].col = i;

    pthread_create(&(cols_threads[i]), NULL, calculate_average_cols, &(cols_params[i])); // cria a thread
  }
  
  // parametros para a leitura de linhas
  for(int i = 0; i < read_row; i++){
    rows_params[i].matrix = matrix;
    rows_params[i].average_rows = average_rows;
    rows_params[i].cols = read_col;
    rows_params[i].row = i;

    pthread_create(&(rows_threads[i]), NULL, calculate_average_rows, &(rows_params[i])); // cria a thread
  }

  for(int i = 0; i < read_col; i++){
    pthread_join(cols_threads[i], NULL);    // espera todas as threads acabarem os calculos
  }

  for(int i = 0; i < read_row; i++){
    pthread_join(rows_threads[i], NULL);    // espera todas as threads acabarem os calculos
  }

  write_average_to_file(rows_file, average_rows, read_row);
  write_average_to_file(cols_file, average_cols, read_col);

  free(average_cols);
  free(cols_threads);
  free(cols_params);
  free(average_rows);
  free(rows_threads);
  free(rows_params);
  free_matrix(matrix, read_row, read_col);

  return 0;
}


void* calculate_average_cols(void* data){
  average_col_params* params = data;
  double product = 1;
  
  for(int i = 0; i < params->rows; i++){
    product = product * params->matrix[i][params->col];
  }

  double divisor = 1.0 / params->rows;

  double avg = pow(product, divisor);
  params->average_cols[params->col] = avg;
  printf("media da coluna %i: %f\n", params->col, avg);
  
  return NULL;
}

void* calculate_average_rows(void* data){
  average_row_params* params = data;
  double sum = 0;
  
  for(int i = 0; i < params->cols; i++){
    sum += params->matrix[params->row][i];
  }

  double avg = sum / params->cols;
  params->average_rows[params->row] = avg;
  // printf("media da linha %i: %i\n", params->row, avg);
  
  return NULL;
}
