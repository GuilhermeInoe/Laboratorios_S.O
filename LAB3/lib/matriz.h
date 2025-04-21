/**
 * Header: matriz.h
 * Descrição: funções básicas para manipular matriz dinâmica
 * 
 * Autor: Rodrigo Campiolo
 * Data: 04/09/2019
 * Mudanças: André Felipe Baretta e João Pedro Inoe Araujo
 * Data de Atualização: 21/04/2025
 */

/** cria uma matriz de inteiros row x col **/
int** create_matrix(int row, int col);

/* gera elementos inteiros para uma matriz row x col existente */
void generate_elements(int** matrix, int row, int col, int limit);

/* lê uma matriz de um arquivo - row e col são configurados a partir do arquivo */
int** read_matrix_from_file(char* filename, int *row, int *col);

/* exibe uma matrix row x col */
void print_matrix(int** matrix, int row, int col);

/* adiciona matriz */
void write_matrix_to_file(char* filename, int** matrix, int row, int col);

/* libera a memoria alocada da matriz */
void free_matrix(int** matrix, int rows, int cols);

/* salva as medias em um arquivo */
void write_average_to_file(char* filename, int* average_array, int size);
