#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Check if placing a queen at (row, col) is valid
bool is_valid(vector<int>& queens, int row, int col) {
    for (int i = 0; i < col; i++) {
        if (queens[i] == row || abs(queens[i] - row) == abs(i - col))
            return false;
    }
    return true;
}

// Backtracking to solve N-Queens
void place_queens(int col, vector<int>& queens, vector<vector<int>>& solutions, int n) {
    if (col == n) {
        solutions.push_back(queens);
        return;
    }
    for (int row = 0; row < n; row++) {
        if (is_valid(queens, row, col)) {
            queens[col] = row;
            place_queens(col + 1, queens, solutions, n);
        }
    }
}

// Solve N-Queens
vector<vector<int>> solveNQueens(int n) {
    vector<vector<int>> solutions;
    vector<int> queens(n, -1);
    place_queens(0, queens, solutions, n);
    return solutions;
}

// Print solutions in 1-based indexing
void print_solutions(vector<vector<int>>& solutions) {
    for (const auto& sol : solutions) {
        for (int q : sol)
            cout << q + 1 << " ";
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> solutions = solveNQueens(n);
    print_solutions(solutions);
    return 0;
}
