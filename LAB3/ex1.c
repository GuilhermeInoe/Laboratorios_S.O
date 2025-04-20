//  - Descrição:.......... Código que cria N threads para localizar um valor em um vetor de M inteiros gerados aleatoriamente
//  - Autor:.............. André Felipe Baretta
//  - Data de criação:.... 20/04/2025
//  - Data de atualização: 20/04/2025

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

// struct para passar os parâmetros da função
typedef struct {
  int* array;
  int initial_pos, final_pos, value;
  int thread_number;
} thread_data;

// funções
int* generate_array(int, int);  // função para a geração do vetor (recebe o tamanho e o valor maximo)
void* search_value(void*);      // função para procura do valor dentro do vetor


int main(int argc, char* argv[]){
  // define os parâmetros

  // valores padrão
  int value = 0;                  
  int thread_count = 10;        
  int array_size = 100000;      
  int max_array_value = 100;
  
  // valores definidos pelo usuário
  if(argc > 1){
    for(int i = 1; i < argc; i++){
      if(!strcmp(argv[i], "-v") && i + 1 < argc){
        value = atoi(argv[i+1]);
        i++;
      } else if(!strcmp(argv[i], "-t") && i + 1 < argc){
        thread_count = atoi(argv[i+1]);
        i++;
      } else if(!strcmp(argv[i], "-a") && i + 1 < argc){
        array_size = atoi(argv[i+1]);
        i++;
      } else if(!strcmp(argv[i], "-m") && i + 1 < argc){
        max_array_value = atoi(argv[i+1]);
        i++;
      } else{
        printf("Argumento desconhecido na posição %i\n", i);
      }
    }
  }

  pthread_t* threads = malloc(thread_count * sizeof(pthread_t));  // vetor com todas as threads
  thread_data* thread_params = malloc(thread_count * sizeof(thread_data));  // vetor com os parametros para cada thread
  
  int* array = generate_array(array_size, max_array_value);  // gera o array com numeros aleatorios

  int pos_per_thread = array_size / thread_count;     // calcula quantas posições cada uma das threads deve procurar

  for(int thread_number = 0; thread_number < thread_count; thread_number++){

    int initial_pos = pos_per_thread * thread_number;         // calcula a posição inicial da thread
    int final_pos = (pos_per_thread * (thread_number + 1));   // calcula a posição final da thread
    if(final_pos >= array_size)
      final_pos = array_size;

    thread_params[thread_number].array = array;
    thread_params[thread_number].initial_pos = initial_pos;
    thread_params[thread_number].final_pos = final_pos;
    thread_params[thread_number].value = value;
    thread_params[thread_number].thread_number = thread_number;

    pthread_create(&(threads[thread_number]), NULL, search_value, &(thread_params[thread_number])); // cria a thread
  }
  
  pthread_exit(NULL);

  free(threads);
  free(thread_params);
  
  return 0;
}


int* generate_array(int size, int max_value){ 
  srand(time(NULL));        // seed para a geração de números aleatórios
  int* array = malloc(size * sizeof(int));  
  for(int i = 0; i < size; i++){
    array[i] = rand() % (max_value+1);    // cria e coloca os valores aleatórios no vetor
  }

  printf("Vetor gerado:\n");      // mostra o vetor gerado
  for(int i = 0; i < size; i++){
    printf("%i, ", array[i]);
  }
  printf("\b\b  \n\n");

  return array;
}

void* search_value(void* data){
  thread_data* params = data;
  int counter = 0;
  for(int i = params->initial_pos; i < params->final_pos; i++){   // procura o valor na parte do vetor que foi escolhida para essa thread
    if(params->array[i] == params->value){
      printf("Valor encontrado na posição %i (Thread %i)\n", i, params->thread_number);
      counter++;
    }
  }
  printf("Thread %i finalizada. Número de valores encontrados: %i\n", params->thread_number, counter);  // mostra quantos valores foram encontradas
  return NULL;                                                                                          // quando a thread é finalizada
}