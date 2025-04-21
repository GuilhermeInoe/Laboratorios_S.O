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
$ make ex2
```
###### Para geração do arquivo
```
$ ./bin/ex2 -r <número de linhas> -c <número de colunas> -l <limite dos numeros gerados>
```
###### Para usar em um arquivo
```
$ ./bin/ex2 -f <caminho para o arquivo> -rf <caminho para o arquivo de médias de linhas> -rf <caminho para o arquivo de médias de colunas>
```

#### Flags:

##### Número de linhas
###### Padrão: 6
`-r <número de linhas>` 

##### Número de colunas
###### Padrão: 8
`-r <número de linhas>` 

##### Número máximo gerado aleatóriamente
###### Padrão: 20
`-l <número limite>`

##### Arquivo de entrada
###### Padrão: gerado aleatóriamente
`-f <caminho do arquivo>`

##### Arquivo de saída para a média de linhas
###### Padrão: output/media_linhas_[`linhas`]_[`colunas`].out 
`-rf <caminho>`

##### Arquivo de saída para a média de linhas
###### Padrão: output/media_colunas_[`linhas`]_[`colunas`].out 
`-cf <caminho>`
