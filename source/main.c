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

    // srand(time(0));
    food->position.x = rand() % WIDTH;
    food->position.y = rand() % HEIGHT;
}

void printBoard(Snake *snake, Food *food) {
    screenClear(); 
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
    // Atualiza a posição dos segmentos de trás para frente
    for (int i = snake->size - 1; i > 0; i--) {
        snake->position[i] = snake->position[i - 1];
    }

    // Atualiza a direção da cabeça
    switch (snake->direction) {
        case 'U': snake->position[0].y--; break; // Up
        case 'D': snake->position[0].y++; break; // Down
        case 'L': snake->position[0].x--; break; // Left
        case 'R': snake->position[0].x++; break; // Right
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
    timerInit(50);

    initGame(&snake, &food);

    while (!gameOver) {
        printBoard(&snake, &food);
        updatePosition(&snake);
        gameOver = checkCollision(&snake, &food);


        if (keyhit()) {
            tecla = readch();
            printf("%c", tecla);
            if (tecla == 'w') snake.direction = 'U';
            else if (tecla == 's') snake.direction = 'D';
            else if (tecla == 'a') snake.direction = 'L';
            else if (tecla == 'd') snake.direction = 'R';
        }

        while(timerTimeOver() == 1);
    } 

    printf("Game Over!\n");

    screenDestroy();
    keyboardDestroy();
    timerDestroy();

    return 0;
}

