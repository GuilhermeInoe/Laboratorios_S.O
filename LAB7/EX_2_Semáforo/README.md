# Jantar dos Filósofos (Versão com Monitor Encapsulado)

Este projeto é uma implementação do clássico problema da computação concorrente: **O Jantar dos Filósofos**, usando um **monitor encapsulado** em linguagem C com POSIX Threads (`pthread`).

## 🧠 Sobre o Problema

Cinco filósofos sentam-se ao redor de uma mesa com um garfo entre cada par. Cada filósofo alterna entre pensar e comer, mas para comer precisa pegar os dois garfos adjacentes. O objetivo é evitar condições de corrida e deadlocks, mantendo o sistema justo.

## 📁 Estrutura

- `Main.c`: Código-fonte principal da solução com encapsulamento completo do monitor.
- `Makefile`: Script para compilar e limpar o projeto.

## 🛠️ Compilação

Para compilar o projeto, basta executar no terminal:

```bash
make

