#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <keyboard.h>
#include <screen.h>
#include <timer.h>

#define WIDTH 30
#define HEIGHT 15
#define SNAKE_CHAR 'O'
#define FOOD_CHAR '&'
#define WALL_CHAR '#'

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position *body;  // Agora, um ponteiro para uma posição dinâmica
    int size;
    char direction;
} Snake;

typedef struct {
    Position position;
} Food;

void initialize(Snake *snake, Food *food) {
    snake->size = 1;
    snake->body = (Position *)malloc(sizeof(Position));  // Alocando memória para a cabeça da cobra
    snake->body[0].x = WIDTH / 2;
    snake->body[0].y = HEIGHT / 2;
    snake->direction = 'R';

    srand(time(0));
    food->position.x = 1 + rand() % (WIDTH - 2);
    food->position.y = 1 + rand() % (HEIGHT - 2);
}


// Desenha a tela com bordas, cobra e comida
void renderGame(const Snake *snake, const Food *food) {
    screenClear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                printf("%c", WALL_CHAR); // Bordas
            } else if (x == snake->body[0].x && y == snake->body[0].y) {
                printf("%c", SNAKE_CHAR); // Cabeça da cobra
            } else if (x == food->position.x && y == food->position.y) {
                printf("%c", FOOD_CHAR); // Comida
            } else {
                int isBody = 0;
                for (int i = 1; i < snake->size; i++) {
                    if (x == snake->body[i].x && y == snake->body[i].y) {
                        printf("%c", SNAKE_CHAR); // Corpo da cobra
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

// Atualiza a posição da cobra com base na direção
void moveSnake(Snake *snake) {
    for (int i = snake->size - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    switch (snake->direction) {
        case 'U': snake->body[0].y--; break;
        case 'D': snake->body[0].y++; break;
        case 'L': snake->body[0].x--; break;
        case 'R': snake->body[0].x++; break;
    }
}

// Verifica colisões com paredes, corpo e comida
int checkGameState(Snake *snake, Food *food) {
    // Colisão com paredes
    if (snake->body[0].x == 0 || snake->body[0].x == WIDTH - 1 ||
        snake->body[0].y == 0 || snake->body[0].y == HEIGHT - 1) {
        return 1; // Game Over
    }

    // Colisão com o próprio corpo
    for (int i = 1; i < snake->size; i++) {
        if (snake->body[0].x == snake->body[i].x &&
            snake->body[0].y == snake->body[i].y) {
            return 1; // Game Over
        }
    }

    // Comer comida
    if (snake->body[0].x == food->position.x && snake->body[0].y == food->position.y) {
        snake->size++;
        food->position.x = rand() % (WIDTH - 2) + 1;
        food->position.y = rand() % (HEIGHT - 2) + 1;
    }

    return 0; // Jogo continua
}

// Atualiza a direção da cobra com base na entrada do jogador
void updateDirection(Snake *snake, char input) {
    if ((input == 'w' && snake->direction != 'D') ||
        (input == 's' && snake->direction != 'U') ||
        (input == 'a' && snake->direction != 'R') ||
        (input == 'd' && snake->direction != 'L')) {
        snake->direction = (input == 'w') ? 'U' :
                           (input == 's') ? 'D' :
                           (input == 'a') ? 'L' : 'R';
    }
}

int main() {
    Snake snake;
    Food food;
    char ch = 0;
    int gameOver = 0;

    keyboardInit();
    screenInit(1);
    timerInit(200);

    printf("=== Bem-vindo ao Snake Game! ===\n");
    printf("Use W/A/S/D para mover a cobra.\nPressione ENTER para começar.\n");
    getchar();

    initialize(&snake, &food);

    while (!gameOver && ch != 10) {
        if (keyhit()) {
            ch = readch();
            updateDirection(&snake, ch);
        }

        if (timerTimeOver() == 1) {
            moveSnake(&snake);
            gameOver = checkGameState(&snake, &food);
            renderGame(&snake, &food);
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
