# Gerenciador de Cartelas de Bingo

O **Bingo** é um jogo que envolve a marcação de números em uma cartela, conforme eles são sorteados aleatoriamente por um chamador. O objetivo é preencher uma linha, coluna, ou um padrão específico de números antes dos outros jogadores e anunciar "Bingo!" para sinalizar a vitória.

Com o advento da tecnologia, o Bingo também ganhou versões digitais, onde jogadores podem participar remotamente, com números sendo chamados automaticamente e cartelas virtuais sendo preenchidas automaticamente. 

Neste projeto, você irá desenvolver um **gerenciador de cartelas de Bingo**.

## Funcionalidades

1. **Menu Interativo**  
   O programa deve criar um menu interativo na função `main` que permita ao usuário interagir com o programa. As opções incluem:
   - Cadastrar a cartela.
   - Marcar um número.
   - Outras funcionalidades conforme o desenvolvimento.

2. **Estrutura de Dados para Cartelas**  
   O programa deve permitir ao jogador gerenciar uma ou mais cartelas. O jogador pode informar quantas cartelas deseja, e o programa gerará as cartelas automaticamente.

   - Cada cartela é organizada em uma grade de 5x5 com 25 quadrados, sendo o quadrado central (geralmente chamado de "FREE") livre e automaticamente preenchido.
   - Cada coluna é rotulada com uma das letras da palavra "BINGO" e possui um intervalo específico de números:
     - Coluna **B**: contém números de 1 a 15.
     - Coluna **I**: contém números de 16 a 30.
     - Coluna **N**: contém números de 31 a 45 (com o quadrado central como "FREE").
     - Coluna **G**: contém números de 46 a 60.
     - Coluna **O**: contém números de 61 a 75.
   - Cada número nas colunas deve ser selecionado aleatoriamente dentro de seu intervalo, garantindo que não haja repetição de números na mesma cartela.

3. **Visualização das Cartelas**  
   O programa deve permitir que o jogador visualize a(s) cartela(s) com as quais está jogando.

4. **Inserção do Número Chamado**  
   O jogador poderá inserir o número chamado, e o programa deve "marcar" o número na cartela.

5. **Marcação das Cartelas**  
   - **COLUNA**: Caso todos os 5 quadrados de uma coluna estejam marcados, o programa deve alertar o jogador com a mensagem "COLUNA".
   - **LINHA**: Caso todos os 5 quadrados de uma linha estejam marcados, o programa deve alertar o jogador com a mensagem "LINHA".
   - **BINGO**: Caso todos os quadrados de uma cartela estejam marcados, o programa deve alertar o jogador com a mensagem "BINGO".
   - **Olha a boa!**: Caso os quadrados da cartela estejam preenchidos e falte apenas um número, o programa deve alertar o jogador com a mensagem "Olha a boa!".

6. **Relatório dos Números Chamados**  
   O programa deve informar quais números foram chamados. Por exemplo, se os números chamados forem:




Referencias de Materiais de estudo:


https://www.youtube.com/watch?v=_byMWMrwEdU&t=16s

https://www.youtube.com/watch?v=ucupombJuUM&list=PL3ZslI15yo2r-gHJtjORRMRKMSNRpf7u5

https://techdevguide.withgoogle.com/paths/data-structures-and-algorithms/

https://www.geeksforgeeks.org/data-structures/

https://sae.unb.br/cae/conteudo/unbfga/cb/new_alocacaodinamica.html#:~:text=A%20aloca%C3%A7%C3%A3o%20din%C3%A2mica%20permite%20ao,o%20programa%20est%C3%A1%20sendo%20executado.

https://www.youtube.com/watch?v=suCM0jnRl6k

https://stackoverflow.com/questions/74244578/how-can-i-reshape-a-2d-array-into-1d-in-python