# Jogo PIF

## Membros do grupo
- Arthur Orange (Arthur1734)
- Guilherme Chaves Sena (guiiichaves)
- Yuri França (yuricsg)

## Matéria 
Programação Imperativa e Funcional

## Instituição 
Cesar School

## Descrição do Jogo

O jogo da cobrinha é aquele clássico onde você controla uma pequena cobra dentro de um campo, e o objetivo é fazer com que ela coma frutas espalhadas pelo mapa. Cada vez que a cobra come uma fruta, ela cresce um pouco e o desafio aumenta, já que, quanto maior a cobra, mais difícil fica desviar dela mesma! O jogador precisa guiar a cobrinha para que ela não colida com as bordas do campo nem com o próprio corpo, porque, se isso acontecer, o jogo acaba. A graça é ver até onde você consegue ir sem bater!

## Implementação no GitHub

Para construir o jogo, podemos dividir o código em partes simples para facilitar o desenvolvimento e o entendimento:

1. Movimentação da Cobra: Vamos programar a cobra para que ela se mova no campo, mudando de direção com as teclas (normalmente, setas ou WASD). Toda vez que o jogador pressiona uma tecla de direção, a cobra segue nesse sentido.


2. Frutas: As frutas vão aparecer em posições aleatórias no campo, e o desafio é fazer a cobrinha chegar até elas. Quando a cobra come uma fruta, ela aumenta de tamanho (adicionamos um novo "segmento" ao corpo) e a fruta desaparece, surgindo em outro lugar.


3. Colisão: Precisamos garantir que, se a cobra bater em uma parede ou em uma parte dela mesma, o jogo termina. A detecção de colisão vai servir para verificar quando o jogo acabou.


4. Pontuação e Crescimento: Toda vez que a cobra come uma fruta, somamos pontos e aumentamos o comprimento dela. No fim, a pontuação mostra o quão longe o jogador conseguiu chegar.

<br>
Para baixar do repositorio e compilar siga os seguintes passos: </br>

1. Crie uma pasta local em seu computador com o nome JogoPIF conforme exemplo abaixo:
   ```bash
   mkdir JogoPIF
   cd JogoPIF
   ```
2. Faça um clone deste repositório com o seguinte comando:

   git clone https://github.com/yuricsg/JogoPIF.git .

3. Compile o jogo usnado este comando:

   gcc source/*.c -I include/ -o jogo

4. Execute o programa executando o comando:

   ./jogo

   
