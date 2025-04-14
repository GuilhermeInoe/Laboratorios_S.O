//  - Descrição:.......... Código responsável por criar uma interface shell simples para executar comandos shell do sistema.
//  - Autor:.............. André Felipe Baretta
//  - Data de criação:.... 10/04/2025
//  - Data de atualização: 13/04/2025

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAX_INPUT_SIZE 100
#define MAX_ARGUMENTS 5

int main(){
  char* input = malloc(MAX_INPUT_SIZE * sizeof(char)); // Para armazenar o input do usuário
  char* program = malloc(MAX_INPUT_SIZE * sizeof(char)); // Para armazenar o nome do programa a ser executado
  
  while(1){
    printf(">>");
    
    // Lê a linha completa com espaços
    fgets(input, MAX_INPUT_SIZE, stdin);

    char* tokens[MAX_ARGUMENTS]; // Vetor de argumentos
    int background = 0; // Variável que guarda se o processo deve ser executado em segundo plano
    int i = 0;

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

    // Se não houver nenhum token, continua o loop e espera pelo próximo comando
    if(i == 0)
      continue;
    if(i > 1 && strcmp(tokens[i-1], "&") == 0){
      tokens[i-1] = NULL;
      background = 1;
    } else 
      tokens[i] = NULL; // Finaliza o vetor de argumentos com NULL (necessário para o execvp())
  
    // Copia o nome do programa a ser executado para "program"
    strcpy(program, tokens[0]);

    // Cria um processo filho
    pid_t pid = fork();
    if(!pid){
      // Processo filho executa o programa
      execvp(program, (char**) tokens);
      exit(0);
    }
    if(pid && !background){
      // Processo pai espera o processo filho terminar de executar se não for segundo plano
      wait(NULL);
    } else if(background) {
      // Processo pai informa o PID do filho e espera o proximo comando se for segundo plano
      printf("Processo iniciado em segundo plano: %i\n", pid);
    }
  }

  free(input);
  free(program);
}