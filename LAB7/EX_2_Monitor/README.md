# Jantar dos Filósofos com Monitor

Este projeto implementa o clássico problema do **Jantar dos Filósofos** usando **monitores** com `pthread_mutex_t` e `pthread_cond_t` para controle de concorrência em C.

## 🧠 Descrição

Cinco filósofos alternam entre pensar e comer. Para comer, cada filósofo precisa de dois garfos (um à sua esquerda e um à sua direita). O monitor garante que não haja deadlock ou condição de corrida entre os filósofos.

## 📁 Estrutura do Projeto

- `main.c`: implementação principal do problema.
- `Makefile`: automatiza a compilação do projeto.

## 🧵 Tecnologias e Bibliotecas

- Linguagem: C
- Bibliotecas: `pthread`, `stdio`

## ⚙️ Compilação

Para compilar o programa, basta executar:

```bash
make

