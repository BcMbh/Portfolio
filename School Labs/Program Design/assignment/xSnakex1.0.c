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
void printBoard(int board[],int insertX, int insertY);
void move();
void generateFood();
int checkCollision();
int checkGameState(); 
void displayDefeatScreen();
void displayVictoryScreen();
void xMark(int board[],int insertX, int insertY);


//---------------------------------------------------------------------------------------------
int main() {
    //setup
    snake.size = 3;
    snake.position[0].X = HIGH / 2;
    snake.position[0].Y = WIDE / 2;
    snake.direction = 3;
    int insertX = 0;  
    int insertY = 0;  
    int board[9] = {0};

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
        // Input for snake controls
        
        if (_kbhit()) {
			char key = _getch();
        switch (key) {
            //tictactoe
            case '7': board[0] = 1;break;
            case '8': board[1] = 2;break;
            case '9': board[2] = 3; break;
            case '4': board[3] = 4;break;
            case '5': board[4] = 5;break;
            case '6': board[5] = 6;break;
            case '1': board[6] = 7; break;
            case '2': board[7] = 8;break;
            case '3': board[8] = 9; break;
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

        if(insertX==1){
            displayVictoryScreen();
        }

        move();
        xMark(board, insertX, insertY);
        printBoard(board, insertX, insertY);
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

void printBoard(int board[],int insertX,int insertY) {
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
        } else if (row == food.X && col == food.Y) {
            printf("$");  // Food
        } else if (row == topRow && col == leftCol) {
            printf("0");  // centre corner
        } else if (row == topRow && col == rightCol) {
            printf("1");  // centre corner
        } else if (row == bottomRow && col == leftCol) {
            printf("2");  // centre corner
        } else if (row == bottomRow && col == rightCol) {
            printf("3");  // centre corner
        } else if ((col % (WIDE / 3) == 0) && (col != 0 && col < WIDE - 1)) {
            printf("|");  // Vertical line for the grid
        } else if ((row % (HIGH / 3) == 0) && (row != 0 && row < HIGH - 1) && (col > 0 && col < WIDE - 1)) {
            printf("-");  // Horizontal line for the grid
        } else if(insertX==1 && row == HIGH /2 && col == WIDE / 2){
            printf("x");
        }
        else {
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
    for (int i = 0; i < sizeof(board) / sizeof(board[0]); i++) {
        printf("Your damb array:%d ", board[i]);
    }
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

void xMark(int board[], int insertX, int InsertY){ // doesn't work
    float central[4][2]; //[amount][y&x]
    
    central[0][0] = HIGH / 3;//1
    central[0][1] = WIDE / 3;
    central[1][0] = HIGH / 3;//2
    central[1][1] = WIDE / 1.5;
    central[2][0] = HIGH / 1.5;//3
    central[2][1] = WIDE / 3;
    central[3][0] = HIGH / 1.5;//4
    central[3][1] = WIDE / 1.5;
    
    for (int i = 0; i < sizeof(board) / sizeof(board[0]); i++) {
        if(board[i]==1 && central[0][0] < snake.position[0].Y && central[0][1] > snake.position[0].X ){
            //displayDefeatScreen();
            insertX = 1;
        }
        if( board[i]==2 && central[0][0] < snake.position[0].Y && central[0][1] < snake.position[0].X){
            insertX = 2;
        }
        if( board[i]==3 && central[1][0] < snake.position[0].Y && central[1][1] < snake.position[0].X){
            insertX = 3;
        }
        if( board[i]==4 && central[2][0] < snake.position[0].Y && central[2][1] > snake.position[0].X){
            insertX = 4;
        }
        if( board[i]==5 && central[2][0] < snake.position[0].Y && central[2][1] < snake.position[0].X){
            insertX = 5;
        }
        if( board[i]==6 && central[3][0] < snake.position[0].Y && central[3][1] < snake.position[0].X){
            insertX = 6;
        }//down
        if( board[i]==7 && central[2][0] > snake.position[0].Y && central[2][1] > snake.position[0].X){
            insertX = 7;
        }
        if( board[i]==8 && central[2][0] > snake.position[0].Y && central[2][1] > snake.position[0].X){
            insertX = 8;
        }
        if( board[i]==9 && central[3][0] > snake.position[0].Y && central[3][1] < snake.position[0].X){
            insertX = 9;
        }
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
        return 0;  // Return 0 to indicate the game should end
    }

    if (score > WINNING_SCORE) {
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
