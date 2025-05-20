#include <iostream>
#include <vector>
using namespace std;

// Function to check if a position (row, col) is attacked by any queen
bool isAttacked(vector<vector<char>>& board, int row, int col, int N, int M) {
    // Check the current row and column for any queen
    for (int i = 0; i < N; i++) {
        if (board[i][col] == 'Q') return true;
    }
    for (int j = 0; j < M; j++) {
        if (board[row][j] == 'Q') return true;
    }
    
    // Check diagonals
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return true;
    }
    for (int i = row, j = col; i >= 0 && j < M; i--, j++) {
        if (board[i][j] == 'Q') return true;
    }
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j] == 'Q') return true;
    }
    for (int i = row, j = col; i < N && j < M; i++, j++) {
        if (board[i][j] == 'Q') return true;
    }
    
    return false;
}

// Function to place the minimum number of queens on the board
void placeQueens(vector<vector<char>>& board, int N, int M) {
    int queensPlaced = 0;
    
    // Try placing queens in an alternating pattern
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!isAttacked(board, i, j, N, M)) {
                board[i][j] = 'Q';
                queensPlaced++;
            }
        }
    }
    
    // Output the board
    cout << "Minimum number of queens required: " << queensPlaced << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int N, M;
    cout << "Enter dimensions of the chessboard (N M): ";
    cin >> N >> M;
    
    vector<vector<char>> board(N, vector<char>(M, 'X'));
    
    // Place queens and print the layout
    placeQueens(board, N, M);

    return 0;
}
