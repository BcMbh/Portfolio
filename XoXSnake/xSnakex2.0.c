#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#define HIGH 16
#define WIDE 30
#define WINNING_SCORE 100

int score=0;
bool stop = false;

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
void printBoard(bool board[9],bool x[9],bool o[9]);
void move();
void BoardSpace(bool board[9],bool x[9],bool o[9]);
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
    bool board[9] = {false, false, false, false, false, false, false, false, false};
    bool x[9] = {false, false, false, false, false, false, false, false, false};
    bool o[9] = {false, false, false, false, false, false, false, false, false};

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
    
    while (!stop && checkGameState()) { //while loop runs when 1
        // Input for snake controls
        
        if (_kbhit()) {
			char key = _getch();
        switch (key) {
            //tictactoe
            case '7': board[0] = true,x[0] = true;break;
            case '8': board[1] = true,x[1] = true;break;
            case '9': board[2] = true,x[2] = true;break;
            case '4': board[3] = true,x[3] = true;break;
            case '5': board[4] = true,x[4] = true;break;
            case '6': board[5] = true,x[5] = true;break;
            case '1': board[6] = true,x[6] = true;break;
            case '2': board[7] = true,x[7] = true;break;
            case '3': board[8] = true,x[8] = true;break;
            //snake
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
                exit(0);
            default:
            break;
    }
		}
        move();
        BoardSpace(board,x,o);
        printBoard(board,x,o);
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

void printBoard(bool board[9],bool x[9],bool o[9]) {
    gotoxy(0, 0);

    for (int i = 0; i < HIGH * WIDE; i++) { //this method doesnt need nested loop with j cause basic math duh 
        int col = i %WIDE;//WIDE
        int row = i / WIDE;//HIGH

        // Check if the current position is occupied by the snake
        int isSnakeBody = 0;
        for (int k = 0; k < snake.size; k++) {
            if (row == snake.position[k].X && col == snake.position[k].Y) {
                isSnakeBody = 1;
                break;
            }
        }
        //central
        int topRow = HIGH / 3;
        int bottomRow = HIGH / 1.5;
		int rightCol = WIDE / 1.5;
        int leftCol = WIDE / 3;

        // Print Everything in heirarchy
        if (isSnakeBody) {
            if (row == snake.position[0].X && col == snake.position[0].Y) {
                printf("0");  // Head of the snake
            } else {
                printf("o");  // Body of the snake
            }
        } else if (row == topRow && col == leftCol) {
            printf("0");  // centre corner
        } else if (row == topRow && col == rightCol) {
            printf("1");  // centre corner
        } else if (row == bottomRow && col == leftCol) {
            printf("2");  // centre corner
        } else if (row == bottomRow && col == rightCol) {
            printf("3");  // centre corner
        } else if (row == food.X && col == food.Y) {
            printf("$");  // Food
        } else if ((col % (WIDE / 3) == 0) && (col != 0 && col < WIDE - 1)) {
            printf("|");  // Vertical line for the grid
        } else if ((row % (HIGH / 3) == 0) && (row != 0 && row < HIGH - 1) && (col > 0 && col < WIDE - 1)) {
            printf("-");  // Horizontal line for the grid
        }else {
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

void BoardSpace(bool board[9],bool x[9],bool o[9]){  
    int central[4][2]; //[amount][x&y] 
    
    central[0][0] = HIGH / 3;
    central[0][1] = WIDE / 3;//1
    central[1][0] = HIGH / 1.5;
    central[1][1] = WIDE / 3;//2
    central[2][0] = HIGH / 3;
    central[2][1] = WIDE / 1.5;//3
    central[3][0] = HIGH / 1.5;
    central[3][1] = WIDE / 1.5;//4
    
    //top
    if (!o[0] && x[0] && (snake.position[0].X < central[0][0]) && (snake.position[0].Y < central[0][1])) {
        stop = true;
    }
    if (!o[1] && x[1] && (snake.position[0].X > central[0][0]) && (snake.position[0].X < central[1][0]) && (snake.position[0].Y < central[0][1])) {//
        stop = true;
    }
    if (!o[2] && x[2] && (snake.position[0].X > central[1][0]) && (snake.position[0].Y < central[1][1])) {
        stop = true;
    }//mid
    if (!o[3] && x[3] && (snake.position[0].X < central[2][0]) && (snake.position[0].Y > central[1][1]) && (snake.position[0].Y < central[2][1])) {
        stop = true;
    }
    if (!o[4] && x[4] && (snake.position[0].X > central[2][0]) && (snake.position[0].X < central[3][0]) && (snake.position[0].Y > central[1][1]) && (snake.position[0].Y < central[2][1])) {//
        stop = true;
    }
    if (!o[5] && x[5] && (snake.position[0].X > central[3][0]) && (snake.position[0].Y > central[1][1]) && (snake.position[0].Y < central[2][1])) {
        stop = true;
    }
    // bot
    if (!o[6] && x[6] && (snake.position[0].X < central[2][0]) && (snake.position[0].Y > central[2][1])) {
        stop = true;
    }
    if (!o[7] && x[7] && (snake.position[0].X > central[2][0]) && (snake.position[0].X < central[3][0]) && (snake.position[0].Y > central[2][1])) {
        stop = true;
    }
    if (!o[8] && x[8] && (snake.position[0].X > central[3][0]) && (snake.position[0].Y > central[3][1])) {
        stop = true;
    }


}

int checkCollision() {
    //boarder
    if (snake.position[0].X < 0 || snake.position[0].X > HIGH || snake.position[0].Y < 0 || snake.position[0].Y > WIDE) {
        return 1;
    }
    //food
    if (snake.position[0].X == food.X && snake.position[0].Y == food.Y) {
        snake.size++;
        score += 5;
        generateFood();
    }
    //touch itself
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
        stop = true;  
    }

    if (score > WINNING_SCORE) {
        displayVictoryScreen();
        stop = true;  
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
