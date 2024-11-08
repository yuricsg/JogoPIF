#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cli_lib.h"

#define WIDTH 20
#define HEIGHT 20

typedef struct{
    int x;
    int y;
} Posicao;

typedef struct{
    Posicao posicao[100];
    int taanho;
    int direcao;
} Snake;

typedef struct{
    Posicao posicao;
} Food;

int score = 0;

void iniciarJogo(Snake *snake,Food *food){
    snake -> tamanho = 1;
    snake -> posicao[0].x = WIDTH /2;
    snake -> posicao[0].y = HEIGHT / 2;
    snake -> direcao = 'R';
    srand(time(0));
    food -> posicao.x = rand() % WIDTH;
    food -> posicao.y = rand() % HEIGHT;
    score = 0; //Reseta a pontuação ao iniciar o jogo
    cli_init();
}

void tabela(Snake *snake, Food *food){
    cli_clear();

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                cli_print_char('#'); 
            } else if (i == snake->posicao[0].y && j == snake->posicao[0].x) {
                cli_print_char('O'); 
            } else if (i == food->posicao.y && j == food->posicao.x) {
                cli_print_char('F'); 
            } else {
                int isBody = 0;
                for (int k = 1; k < snake->size; k++) {
                    if (i == snake->posicao[k].y && j == snake->posicao[k].x) {
                        cli_print_char('o'); 
                        isBody = 1;
                        break;
                    }
                }
                if (!isBody) cli_print_char(' ');
            }
        }
        cli_print_char('\n');
        }
    }


void moverCobra(Snake *snake){

}



int main() {
    Snake snake;
    Food food;
    iniciarJogo(&snake, &food);

    
    return 0;
}
