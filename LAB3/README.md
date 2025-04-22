### sCaso não esteja no diretório correto:
```
$ cd LAB3
```

### Comandos para executar exercício 1:
```
$ make ex1
```
###### Se nenhum argumento for usado, os parâmetros terão os seguintes valores como padrão: -v 0 -t 10 -a 100000 -m 100
```
$ ./bin/ex1 -v <valor procurado> -t <número de threads> -a <tamanho do vetor> -m <maior valor permitido no vetor>
```

#### Flags:

##### Valor a ser procurado
###### Padrão: 0
`-v <valor procurado>` 

##### Número de threads
###### Padrão: 10
`-t <número de linhas>` 

##### Tamanho do vetor gerado
###### Padrão: 100000
`-a <tamanho do vetor>`

##### Número máximo gerado aleatóriamente
###### Padrão: 100
`-m <número limite>`



### Comandos para executar exercício 2:
```
$ make Exercicio_02
```
###### Para geração do arquivo
```
$ ./bin/ex2 -t <número de threads> -l <número de linhas> -c <número de colunas> -e <nome do arqivo de entrada com a matriz> -s <nome do arqivo de saída com a matrizz>
```
### Funcionamento:
#### O usuário opta por gerar uma matriz com valores aleatórios gerada pelo programa
#### ou usar uma matriz pronta em um arquivo externo

#### Flags:

##### Número de threads
###### Padrão: 4
`-t <número de threads>`

##### Número de linhas
###### Padrão: 10
`-l <número de linhas>` 

##### Número de colunas
###### Padrão: 10
`-c <número de colunas>` 

##### Nome do arqivo de entrada com a matriz (Opcional):
###### Padrão: mensagem informando que nada foi enviado
`-e <nome do arquivo>`
#### Descrição:
##### Caso o usuário prefira usar uma matriz pronta, deverá informar o nome do arquivo com a matriz com essa flag.
##### O número de linhas e colunas da matriz em arquivo externo também devem ser informados 

##### Nome do arqivo de saída com a matriz (Opcional)
###### Padrão: gmensagem informando que nada foi enviado
`-s <nome do arquivo>`
#### Descrição:
##### Caso o usuário queira um arquivo externo com a matriz gerada pelo programa deve informar o nome usando essa flag.



