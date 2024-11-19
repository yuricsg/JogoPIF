#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <keyboard.h>
#include <screen.h>
#include <timer.h>

#define WIDTH 20
#define HEIGHT 20

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position position[100]; 
    int size;
    char direction;
} Snake;

typedef struct {
    Position position;
} Food;

void initGame(Snake *snake, Food *food) {
    snake->size = 1;  
    snake->position[0].x = WIDTH / 2;
    snake->position[0].y = HEIGHT / 2;
    snake->direction = 'R'; 

    srand(time(0));
    do {
        food->position.x = rand() % (WIDTH - 2) + 1; 
        food->position.y = rand() % (HEIGHT - 2) + 1;
    } while (food->position.x == snake->position[0].x && 
             food->position.y == snake->position[0].y);
}

void printBoard(Snake *snake, Food *food) {
    screenClear(); 
    printf("Score: %d\n", snake->size - 1);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                printf("#"); 
            } else if (i == snake->position[0].y && j == snake->position[0].x) {
                printf("O"); 
            } else if (i == food->position.y && j == food->position.x) {
                printf("F"); 
            } else {
                int isBody = 0;
                for (int k = 1; k < snake->size; k++) {
                    if (i == snake->position[k].y && j == snake->position[k].x) {
                        printf("o");
                        isBody = 1;
                        break;
                    }
                }
                if (!isBody) printf(" ");
            }
        }
        printf("\n");
    }
}

void updatePosition(Snake *snake) {
    for (int i = snake->size - 1; i > 0; i--) {
        snake->position[i] = snake->position[i - 1];
    }

    switch (snake->direction) {
        case 'U': snake->position[0].y--; break; 
        case 'D': snake->position[0].y++; break; 
        case 'L': snake->position[0].x--; break; 
        case 'R': snake->position[0].x++; break; 
    }
}

int checkCollision(Snake *snake, Food *food) {
    if (snake->position[0].x == 0 || snake->position[0].x == WIDTH - 1 ||
        snake->position[0].y == 0 || snake->position[0].y == HEIGHT - 1) {
        return 1; 
    }
    for (int i = 1; i < snake->size; i++) {
        if (snake->position[0].x == snake->position[i].x &&
            snake->position[0].y == snake->position[i].y) {
            return 1; 
        }
    }
    if (snake->position[0].x == food->position.x && snake->position[0].y == food->position.y) {
        snake->size++;
        food->position.x = rand() % WIDTH;
        food->position.y = rand() % HEIGHT;
    }
    return 0;
}

int main() {
    Snake snake;
    Food food;
    int gameOver = 0;
    char tecla = 0;

    keyboardInit();
    screenInit(1);
    printf("Bem-vindo ao Snake!\nUse W/A/S/D para mover.\nPressione 'f' para sair.\nPressione qualquer tecla para começar...\n");
    getchar(); 

    initGame(&snake, &food);

    while (!gameOver) {
        printBoard(&snake, &food);
        updatePosition(&snake);
        gameOver = checkCollision(&snake, &food);

        if (keyhit()) {
            tecla = readch();
            if ((tecla == 'w' && snake.direction != 'D') ||
                (tecla == 's' && snake.direction != 'U') ||
                (tecla == 'a' && snake.direction != 'R') ||
                (tecla == 'd' && snake.direction != 'L')) {
                snake.direction = tecla;
            } else if (tecla == 'f') {
                break; 
            }
        }

        timerInit(600 - (snake.size * 10 > 400 ? 400 : snake.size * 10));
        while (timerTimeOver() != 1);
    } 

    printf("Game Over!\nFinal Score: %d\n", snake.size - 1);

    screenDestroy();
    keyboardDestroy();
    timerDestroy();

    return 0;
}

