# Leitores e Escritores com Prioridade para Leitores (Monitor com Semáforos)

## Descrição

Este projeto é uma implementação do clássico **problema dos Leitores e Escritores**, utilizando **semáforos** para sincronização. O objetivo é permitir que múltiplas threads leitoras acessem simultaneamente um recurso compartilhado, enquanto impede que escritores o modifiquem durante esse período. Escritores, por sua vez, exigem acesso exclusivo ao recurso.

A solução foi implementada em C, simulando um **monitor** usando semáforos POSIX (`sem_t`), com **prioridade para leitores**.

### Compilar:
**make**

### Executar:
**make run**

### Limpar o arquivo compilado:
**make clean**

