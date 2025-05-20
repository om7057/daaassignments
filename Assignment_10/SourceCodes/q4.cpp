#include <iostream>
#include <vector>
using namespace std;

class NQueens {
private:
    int N;
    vector<vector<string>> solutions;

    // Function to check if placing a queen at (row, col) is safe
    bool isSafe(vector<string>& board, int row, int col) {
        // Check this row on left side
        for (int i = 0; i < col; i++) {
            if (board[row][i] == 'Q')
                return false;
        }

        // Check upper diagonal on left side
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q')
                return false;
        }

        // Check lower diagonal on left side
        for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
            if (board[i][j] == 'Q')
                return false;
        }

        return true;
    }

    // Helper function to solve the problem using backtracking
    void solveNQueensUtil(vector<string>& board, int col) {
        // If all queens are placed
        if (col == N) {
            solutions.push_back(board);
            return;
        }

        // Try placing a queen in each row of this column
        for (int i = 0; i < N; i++) {
            if (isSafe(board, i, col)) {
                board[i][col] = 'Q';   
                solveNQueensUtil(board, col + 1); 
                board[i][col] = '.';               }
        }
    }

public:
    // Constructor to initialize board size
    NQueens(int n) : N(n) {}

    // Function to solve the N-Queens problem
    vector<vector<string>> solveNQueens() {
        vector<string> board(N, string(N, '.'));
        solveNQueensUtil(board, 0);
        return solutions;
    }
};

int main() {
    int N;
    cout << "Enter the value of N: ";
    cin >> N;

    NQueens solver(N);
    vector<vector<string>> result = solver.solveNQueens();

    if (result.empty()) {
        cout << "No solution exists for N = " << N << endl;
    } else {
        cout << "Number of solutions: " << result.size() << endl;
        for (const auto& solution : result) {
            for (const string& row : solution) {
                cout << row << endl;
            }
            cout << endl;
        }
    }

    return 0;
}
