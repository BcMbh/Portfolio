#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <conio.h>
#else
#include <cstdio>
#endif

using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char turn = 'X';
int row, column;
bool draw = false;

// Display the current state of the game board
void displayBoard() {
    system("cls");
    cout << "\n\tTIC TAC TOE\n";
    cout << "\tPlayer [X]  Computer [O]\n";
    cout << "\t\t     |     |     \n";
    cout << "\t\t  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  \n";
    cout << "\t\t  __||_\n";
    cout << "\t\t     |     |     \n";
    cout << "\t\t  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  \n";
    cout << "\t\t  __||_\n";
    cout << "\t\t     |     |     \n";
    cout << "\t\t  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  \n";
    cout << "\t\t     |     |     \n";
}

// Update the turn variable
void switchTurn() {
    turn = (turn == 'X') ? 'O' : 'X';
}

// Allow the current player to make a move
void playerTurn() {
    int choice;

    cout << "Player " << turn << ", enter your move (1-9): ";

#ifdef _WIN32
    choice = _getch() - '0';
#else
    choice = getchar() - '0';
#endif

    row = (choice - 1) / 3;
    column = (choice - 1) % 3;

    // Check if the selected position is valid and update the board
    if (board[row][column] != 'X' && board[row][column] != 'O') {
        board[row][column] = turn;
        switchTurn(); // Switch turns after a valid move
    } else {
        cout << "Invalid move! Please try again.\n";
        playerTurn(); // Loop until a valid move is made
    }

    displayBoard(); // Show the updated board
}

// Implement computer's turn (random move)
void computerTurn() {
    int choice;
    cout << "\n\tComputer's turn (Player [O]): ";
    choice = rand() % 9 + 1;

    row = (choice - 1) / 3;
    column = (choice - 1) % 3;

    // Check if the selected position is valid and update the board
    if (board[row][column] != 'X' && board[row][column] != 'O') {
        board[row][column] = turn;
        switchTurn(); // Switch turns after a valid move
    } else {
        // If the chosen position is already taken, try again
        computerTurn();
    }

    displayBoard(); // Show the updated board
}

// Check if the game is over
bool gameOver() {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return true;

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return true;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;

    draw = true;
    return true;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    do {
        displayBoard();
        playerTurn();
        // Uncomment the line below to implement computer's turn
        computerTurn();
    } while (!gameOver());

    if (turn == 'X' && draw == false) {
        cout << "\n\nYou have won the game";
    } else if (turn == 'O' && draw == false) {
        cout << "\n\nComputer has won the game";
    } else {
        cout << "\n\nGAME DRAW!!!\n";
    }

    return 0;
}
