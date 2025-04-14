//  - Descrição:.......... Código que recebe como entrada um comando via terminal e o executa como seu filho.
//  - Autor:.............. André Felipe Baretta
//  - Data de criação:.... 10/04/2025
//  - Data de atualização: 11/04/2025

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAX_INPUT_SIZE 100
#define MAX_ARGUMENTS 5

int main(){
  printf(">>");
  
  char* input = malloc(MAX_INPUT_SIZE * sizeof(char)); // Para armazenar o input do usuário
  char* program = malloc(MAX_INPUT_SIZE * sizeof(char)); // Para armazenar o nome do programa a ser executado
  char* tokens[MAX_ARGUMENTS]; // Vetor de argumentos
  int i = 0;

  // Lê o input do usuário
  fgets(input, MAX_INPUT_SIZE, stdin);

  // Lê a primeira palavra (que é o o comando)
  char* token = strtok(input, " ");

  // Divide o input em tokens (palavras) e remove palavras vazias e caracteres indesejados
  while(token != NULL && i < 5) {
    token[strcspn(token, "\n\r")] = 0;
    if(strlen(token)){
      tokens[i] = token;
      i++;
    }
    token = strtok(NULL, " ");
  }

  // Se não houver nenhum token, exibe mensagem de erro e finaliza o programa
  if(i == 0){
    printf("Nenhum comando foi recebido.\n");
    return 0;
  }

  // Finaliza o vetor de argumentos com NULL (necessário para o execvp())
  tokens[i] = NULL;

  // Copia o nome do programa a ser executado para "program"
  strcpy(program, tokens[0]);

  // Cria um processo filho
  pid_t pid = fork();

  // Se for o processo filho, executa o programa com os argumentos
  if(!pid){
    execvp(program, (char**) tokens);
    exit(0);
  }
  // Se for o pai, espera o filho terminar sua execução
  if(pid){
    wait(NULL);
  }

  // Libera a memória alocada
  free(input);
  free(program);
}