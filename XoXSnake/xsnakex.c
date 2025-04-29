#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

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
void gotoxy(int x, int y); //remove mouse
void printBoard(bool x[9],bool o[9]); //display snake,map and xox
void BoardSpace(bool x[9],bool o[9]); //kill on x
void computer(bool x[9],bool o[9],bool* turn, int* movesCounter); //put o on empty space
bool checkLine(bool array[9]); //tictactoe completed
void move(); //snake movement and also body growth
void generateFood();//increase score 
int checkCollision();//check snake out of boundry
int checkGameState();// game ended or not
void displayDefeatScreen();
void displayVictoryScreen();


//---------------------------------------------------------------------------------------------
int main() {
    //setup
    snake.size = 3;
    snake.position[0].X = HIGH / 2;
    snake.position[0].Y = WIDE / 2;
    snake.direction = 3;
    
    bool x[9] = {false, false, false, false, false, false, false, false, false};
    bool o[9] = {false, false, false, false, false, false, false, false, false};
    bool turn = true;
    int movesCounter = 0;//to tell if thebgame have draw

    // Game start Logo and tips
    printf("======================================\n");
    printf("||      Welcome to XSnakeX!      ||\n");
    printf("======================================\n");
    printf("\n");
    printf("Score 100 to win\n ");
    printf("Food=$\n");
    printf("\nSnake:\n'w' to move up\n's' to move down\n'a' to move left\n'd' to move right.\n");
    printf("\nTictacToe:\nComplete a >line to spawn food< while AVOID 'X' which is you\n\nThe controls:");
    printf("\n 7 | 8 | 9 ");
    printf("\n___|___|___");
    printf("\n 4 | 5 | 6 ");
    printf("\n___|___|___");
    printf("\n 1 | 2 | 3 ");
    printf("\n   |   |   ");
    printf("\n\nPress any key to start the game...\n");
    getch();  // Wait for a key press

    system("cls");  //clear the logo after game start

    srand((unsigned int)time(NULL)); // randomness with seeds <time.h>
    
    //stop exist so the if the player die to xox they can see themself
    while (checkGameState() && !stop ) { //while loop runs when 1 
        
        if (_kbhit()) {
			char key = _getch();
            switch (key) {
                //tictactoe
                case '7': if(!o[0] && !x[0] && turn ) {//check for turn & each array is filled or not first 
                    turn = false, x[0] = true, movesCounter++;} 
                    break;
                case '8': if(!o[1] && !x[1] && turn) {
                    turn = false, x[1] = true, movesCounter++;} 
                    break;
                case '9': if(!o[2] && !x[2] && turn) {
                    turn = false, x[2] = true, movesCounter++;} 
                break;
                case '4': if(!o[3] && !x[3] && turn) {
                    turn = false, x[3] = true, movesCounter++;} 
                    break;
                case '5': if(!o[4] && !x[4] && turn) {
                    turn = false, x[4] = true, movesCounter++;} 
                    break;
                case '6': if(!o[5] && !x[5] && turn) {
                    turn = false, x[5] = true, movesCounter++;} 
                    break;
                case '1': if(!o[6] && !x[6] && turn) {
                    turn = false, x[6] = true, movesCounter++;} 
                    break;
                case '2': if(!o[7] && !x[7] && turn) {
                   turn = false, x[7] = true, movesCounter++;} 
                    break;
                case '3': if(!o[8] && !x[8] && turn) {
                    turn = false, x[8] = true, movesCounter++;} 
                    break;
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

        //check each array to find a a line is formed
        if (checkLine(x)) {
            printf("Player X wins!\n");
            generateFood();
            for (int i = 0; i < 9; i++) {
                x[i] = false;
                o[i] = false;
            }
        } else if (checkLine(o)) {
            printf("Player O wins!\n");
            for (int i = 0; i < 9; i++) {
                x[i] = false;
                o[i] = false;
            }
        } else if(movesCounter ==9){
            printf("Draw!\n");
            for (int i = 0; i < 9; i++) {
                x[i] = false;
                o[i] = false;
            }
        }

        move();
        BoardSpace(x,o);
        computer(x,o,&turn,&movesCounter);
        printBoard(x,o);
        Sleep(200);
    }

    system("pause"); //to prevent the game from running
    return 0;
}



//cursor position
void gotoxy(int x, int y) {
    COORD pos; //struct from windows.h library
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //prevent display lag
}

void printBoard(bool x[9],bool o[9]) {
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

        // Print Everything in heirarchy
        if (isSnakeBody) {
            if (row == snake.position[0].X && col == snake.position[0].Y) {
                printf("0");  // Head of the snake
            } else {
                printf("o");  // Body of the snake
            }
        }else if (row == food.X && col == food.Y) {
            printf("$");  // Food
        } else if ((col % (WIDE / 3) == 0) && (col != 0 && col < WIDE - 1)) {
            printf("|");  // Vertical line for the grid
        } else if ((row % (HIGH / 3) == 0) && (row != 0 && row < HIGH - 1) && (col > 0 && col < WIDE - 1)) {
            printf("-");  // Horizontal line for the grid
        }
        else if(row == 2 && col == 5 && x[0] && !o[0]){ //using for loop here would make the game laggy for low-end pc
            printf("X");
        }else if(row == 2 && col == 5 && o[0] && !x[0]){
            printf("O");
        }
        else if (row == 2 && col == 15 && x[1] && !o[1]){
            printf("X");
        }
        else if (row == 2 && col == 15 && o[1] && !x[1]){
            printf("O");
        }       
        else if (row == 2 && col == 25 && x[2] && !o[2]){
            printf("X");
        }else if(row == 2 && col == 25 && o[2] && !x[2]){
            printf("O");
        }        
        else if(row == 8 && col == 5 && x[3] && !o[3]){
            printf("X");
        }else if(row == 8 && col == 5 && o[3] && !x[3]){
            printf("O");
        }       
        else if (row == 8 && col == 15 && x[4] && !o[4]){
            printf("X");
        }else if(row == 8 && col == 15 && o[4] && !x[4]){
            printf("O");
        }       
        else if (row == 8 && col == 25 && x[5] && !o[5]){
            printf("X");
        }else if(row == 8 && col == 25 && o[5] && !x[5]){
            printf("O");
        }     
        else if (row == 13 && col == 5 && x[6] && !o[6]){
            printf("X");
        }else if(row == 13 && col == 5 && o[6] && !x[6]){
            printf("O");
        }        
        else if (row == 13 && col == 15 && x[7] && !o[7]){
            printf("X");
        }else if(row == 13 && col == 15 &&o[7] && !x[7]){
            printf("O");
        }        
        else if (row == 13 && col == 25 && x[8] && !o[8]){
            printf("X");
        }else if(row == 13 && col == 25 &&o[8] && !x[8]){ //still not gonna put for loop
            printf("O");
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
    printf("\n");
    printf("Score: %d\n", score);
    printf("Snake Position: Y=%d, X=%d\n",  snake.position[0].X, snake.position[0].Y);
    printf("\nGet a line of 'X' to spwan food\n");
    printf("\nControls: UP:'w'  DOWN:'S'\n         LEFT:'a'  RIGHT:'d");
    printf("\nInsert X:\n 7 | 8 | 9 \n 4 | 5 | 6 \n 1 | 2 | 3 ");
    printf("\nesc to exit");
   

}

void move() {
    struct POSITION nextPos = snake.position[0]; //nextpos only execute once

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

void BoardSpace(bool x[9],bool o[9]){  
    int topRow = 5; 
    int bottomRow = 10; 
    int leftCol = 10; 
	int rightCol = 20; 

    //top
    if (!o[0] && x[0] && (snake.position[0].Y <= leftCol) && (snake.position[0].X <= topRow)) {
        stop = true;
        displayDefeatScreen();
    }
    if (!o[1] && x[1] && (snake.position[0].Y >= leftCol) && (snake.position[0].Y <= rightCol) && (snake.position[0].X <= topRow)) {//
        stop = true;
        displayDefeatScreen();
    }
    if (!o[2] && x[2] && (snake.position[0].Y >= rightCol) && (snake.position[0].X <= topRow)) {
        stop = true;
        displayDefeatScreen();
    }//mid
    if (!o[3] && x[3] && (snake.position[0].Y <= leftCol) && (snake.position[0].X >= topRow) && (snake.position[0].X <= bottomRow)) {
        stop = true;
        displayDefeatScreen();
    }
    if (!o[4] && x[4] && (snake.position[0].Y >= leftCol) && (snake.position[0].Y <= rightCol) && (snake.position[0].X >= topRow) && (snake.position[0].X <= bottomRow)) {//
        stop = true;
        displayDefeatScreen();
    }
    if (!o[5] && x[5] && (snake.position[0].Y >= rightCol) && (snake.position[0].X >= topRow) && (snake.position[0].X <= bottomRow)) {
        stop = true;
        displayDefeatScreen();
    }
    // bot
    if (!o[6] && x[6] && (snake.position[0].Y <= leftCol) && (snake.position[0].X >= bottomRow)) {
        stop = true;
        displayDefeatScreen();
    }
    if (!o[7] && x[7] && (snake.position[0].Y >= leftCol) && (snake.position[0].X <= rightCol) && (snake.position[0].X > bottomRow)) {
        stop = true;
        displayDefeatScreen();
    }
    if (!o[8] && x[8] && (snake.position[0].Y >= rightCol) && (snake.position[0].X >= bottomRow)) {
        stop = true;
        displayDefeatScreen();
    }
}

void computer(bool x[9],bool o[9],bool* turn, int *movesCounter){
    //randomise the array it's going to be picking first then check wheter it's free
    int choice = rand() % 9;
        if(*turn == false && !x[choice] && !o[choice]){
            o[choice] = true;
            *movesCounter++;
            *turn = true;
        }

}

bool checkLine(bool array[9]) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (array[i] && array[i + 1] && array[i + 2]) {
            return true;  // Row with three elements
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (array[i] && array[i + 3] && array[i + 6]) {
            return true;  // Column with three elements
        }
    }

    // Check diagonals
    if (array[0] && array[4] && array[8]) {
        return true;  // Diagonal from top-left to bottom-right
    }

    if (array[2] && array[4] && array[6]) {
        return true;  // Diagonal from top-right to bottom-left
    }

    return false;  // No winner
}

int checkCollision() {
    //boarder
    if (snake.position[0].X < 0 || snake.position[0].X > HIGH-1 || snake.position[0].Y < 0 || snake.position[0].Y > WIDE-1) {
        return 1;
    }
    //food
    if (snake.position[0].X == food.X && snake.position[0].Y == food.Y) {
        snake.size++;
        score += 5;
        food.X = -HIGH;
        food.Y = -WIDE;
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
