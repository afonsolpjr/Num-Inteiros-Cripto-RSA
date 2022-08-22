# Num-Inteiros-Cripto-RSA

Este repositório contém alguns algoritmos  (em C) do livro "Números Inteiros e Criptografia RSA", de Severino Collier Coutinho, assim como um gerador de chaves RSA - para fins de estudo-, e um pequeno teste para as chaves.

## Arquivos

Todos os arquivos fontes estão em C, necessitando compilação para a executação.

Excetuando o "cripto_win.c", todos os outros arquivos utilizam a biblioteca gmp.h (GNU Multi-Precision Library) para manusear números inteiros grandes.


  ### - cripto.c e cripto_win.c
  
  O arquivo "cripto.c" contém os algoritmos/testes abaixo:
  
  ![Menu dos algoritmos](/menu_cripto.png)
  
  O arquivo "cripto_win.c" contém somente os 7 primeiros testes/algoritmos, que não necessitam da biblioteca GMP.
  
  
  ### Keygen
 
 Ao final dos exercícios eu fiz um gerador de chaves RSA bem amador, somente para entender o funcionamento da criptografia.
 
 O fonte "keygen.c" gera um arquivo txt com:
 - o número a ser o módulo
 - chave de encriptação "e"
 - chave de decriptação "d"
  Tudo em base decimal.

 E ao final possui um simples teste das chaves, permitindo criptografar números. Este teste é o mesmo em "teste_chaves.c", que lê as chaves do arquivo txt e permite testá-las.
 
 
 
 ## Referência

 S. C. Coutinho, Números Inteiros e Criptografia RSA, 2.Ed, Rio de Janeiro,IMPA,2005.
