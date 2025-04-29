#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define HIGH 16
#define WIDE 30
#define WINNING_SCORE 100

int score=0;

//position holder
struct POSITION {
    int X;
    int Y;
};
//position segments
struct SNAKE {
    struct POSITION position[HIGH * WIDE];//maximum possible number
    int size;
    int direction;
} snake;
//food
struct FOOD {
    int X;
    int Y;
} food;

// Function declarations
void gotoxy(int x, int y);
void printBoard();
void move();
void generateFood();
int checkCollision();
int checkGameState(); 
void displayDefeatScreen();
void displayVictoryScreen();


//---------------------------------------------------------------------------------------------
int main() {
    //setup
    snake.size = 3;
    snake.position[0].X = HIGH / 2;
    snake.position[0].Y = WIDE / 2;
    snake.direction = 3;

    // Game start Logo and tips
    printf("======================================\n");
    printf("||      Welcome to Snake Game!      ||\n");
    printf("======================================\n");
    printf("\n");
    printf("Score 100 to win ");
    printf("\nControls:\n'w' to move up\n's' to move down\n'a' to move left\n'd' to move right.\n"); //show control before game
    printf("Press any key to start the game...\n");
    getch();  // Wait for a key press

    system("cls");  //clear the logo after game start

    generateFood();
    
    while (checkGameState()) { //while loop runs when 1
        //input
        if (_kbhit()) {  // for key stroke (conio.h)
            char key = _getch();
            switch (key) {
                case 'w': 
                    snake.direction = 0; 
                    break;
                case 's':
                    snake.direction = 1;
                    break;
                case 'a':
                    snake.direction = 2;
                    break;
                case 'd':
                    snake.direction = 3;
                    break;
                case 27:  // ASCII code for Esc
                    printf("Game Over! Your Score: %d\nGet better next time!!!\n", score);
                    system("pause");
                    return 0;
                default:
                    break;
            }
        }

        move();
        printBoard();
        Sleep(200);
    }

    system("pause");
    return 0;
}



//cursor position
void gotoxy(int x, int y) {
    COORD pos; //struct from windows.h library
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //prevent display lag
}

void printBoard() {
    gotoxy(0, 0);

    for (int i = 0; i < HIGH * WIDE; i++) { //this method doesnt need nested loop with j cause basic math duh 
        int row = i / WIDE;
        int col = i %WIDE;

        // Check if the current position is occupied by the snake
        int isSnakeBody = 0;
        for (int k = 0; k < snake.size; k++) {
            if (row == snake.position[k].X && col == snake.position[k].Y) {
                isSnakeBody = 1;
                break;
            }
        }

        // Print Everything
        if (isSnakeBody) {
            if (row == snake.position[0].X && col == snake.position[0].Y) {
                printf("0");  // Head of the snake
            } else {
                printf("o");  // Body of the snake
            }
        } else if (row == food.X && col == food.Y) {
            printf("$");  // Food
        } else {
            printf(" ");  // Empty space for the map
        }
        
        if (col == WIDE - 1) {//('|') around
            printf("|\n");
        }
    }
    //outside the boarder
    for (int j = 0; j < WIDE; j++) {//('-') after each row
        printf("-");
    }

    //scores & tips
    printf("\n");
    printf("Score: %d\n", score);
    printf("Controls: Use 'w' to move up\n's' to move down\n'a' to move left\n'd' to move right.\n");
    printf("'Esc' to quit\n");
}

void move() {
    struct POSITION nextPos = snake.position[0];

    switch (snake.direction) {
        case 0:  // up
            nextPos.X--;
            break;
        case 1:  // down
            nextPos.X++;
            break;
        case 2:  // left
            nextPos.Y--;
            break;
        case 3:  // right
            nextPos.Y++;
            break;
    } 

    //shifts each segment to the right by assigning the value of the segment before it
    for (int i = snake.size - 1; i > 0; i--) {
        snake.position[i] = snake.position[i - 1];
    }
    //head infront
    snake.position[0] = nextPos;
}


void generateFood() {
    food.X = rand() %HIGH;
    food.Y = rand() %WIDE;
}

int checkCollision() {
    if (snake.position[0].X < 0 || snake.position[0].X >= HIGH || snake.position[0].Y < 0 || snake.position[0].Y >= WIDE) {
        return 1;
    }

    if (snake.position[0].X == food.X && snake.position[0].Y == food.Y) {
        snake.size++;
        score += 5;
        generateFood();
    }

    for (int i = 1; i < snake.size; i++) {
        if (snake.position[0].X == snake.position[i].X && snake.position[0].Y == snake.position[i].Y) {
            return 1;
        }
    }

    return 0;
}

int checkGameState() {
    if (checkCollision()) {
        displayDefeatScreen();
        return 0;  // Return 0 to indicate the game should end
    }

    if (score >= WINNING_SCORE) {
        displayVictoryScreen();
        return 0;  // Return 0 to indicate the game should end
    }

    return 1;  // Return 1 to indicate the game should continue
}

void displayDefeatScreen() {
    system("cls");  // clear the game after game end
    printf("========================================\n");
    printf("||              You Lost!             ||\n");
    printf("========================================\n");
    printf("\n");
    printf("Your Score: %d\n", score);
    printf("Get better next time!!!\n");
    printf("\n");
    printf("Press any key to exit...\n");
    _getch();  // Wait for a key press to close
}

void displayVictoryScreen() {
    system("cls");
    printf("========================================\n");
    printf("||           You Won!!!         ||\n");
    printf("========================================\n");
    printf("\n");
    printf("You won! Your Score: %d\n", score);
    printf("well you are too good!\n");
    printf("\n");
    printf("Press any key to exit...\n");
    _getch();  // Wait for a key press to close
}
