# Notas sobre a implementação

## Escolha da linguagem

Foi optado a utilizaçào de C (versão C99) devido a familiariedade de uso da
mesmma.  O C99 possui features que foram utilizadas nesta implementação, como
por exemplo as macros de argumentos variávies.

Inicialmente usou-se vetores de tamanaho variável em tempo de execução.  Porém
era atingido o limite da stack rapidamente (com strings de 1280 caracteres).
Com isso alterou-se o código para usar ponteiros e memória dinamica.

## programas

o resultado esta implementação gera os executáveis `trabalho2`, `tarefa2a` e
`tarefa2b`.  Todos são o mesmo arquivo, porém com nomes diferentes.

Para implementação da segunda tarefa, foram implementados 2 códigos, cada um
para atender uma parte.

### tarefa2a

Implementar a primeira parte da tarefa2 é utilizado este programa , que faz a
comparação entre os dois métodos.

#### Parametros

* -i <val>
  Valor de i para executar, por padrão executa de i=1...14

* -v
  Imprime as strings geradas

* -p
  Imprime os "caminhos" dos alinhamentos

* -b <val>
  Valor de j inicial (begin)

* -e <val>
  Valor de j final (end)

* -h
  imprime um help


### tarefa2a

Implementar a segunda parte da tarefa2 é utilizado este programa

#### Parametros

* -b
  executa ambos métodos em cada etapa de i

* -l
  executa somente o algoritmo linear
  
* -q
  executa somente o algoritmo quadratico

* -s <val>
  Novo valor de timeout, em segundos. o default é 900s.

* -m <val>
  Novo valor de timeout, em minutos. o default é 15m.

* -h
  imprime um help

### trabalho2_ut

Esta implementaçào contém um programa de auto-teste (`trabalho2_ut`) que
realiza testes unitários entre vários métodos.

## uso da pthread

Para implementar a tarefa2b, usou-se a pthread para criar um timeout de
execuçào da função em questão.




