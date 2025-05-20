#include <iostream>
#include <vector>
using namespace std;

pair<int, int> searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return {-1, -1}; 
    }

    int rows = matrix.size();
    int cols = matrix[0].size();
    int row = 0;
    int col = cols - 1;

    while (row < rows && col >= 0) {
        if (matrix[row][col] == target) {
            return {row, col};
        } else if (matrix[row][col] > target) {
            col--; 
        } else {
            row++; 
        }
    }

    return {-1, -1}; 
}

int main() {
    int m, n, target;
    cout << "Enter the number of rows: ";
    cin >> m;
    cout << "Enter the number of columns: ";
    cin >> n;
    
    // Initialize matrix with m rows and n columns
    vector<vector<int>> matrix(m, vector<int>(n));
    
    cout << "Enter the elements of the matrix row by row: " << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
    
    cout << "Enter the target element: ";
    cin >> target;

    pair<int, int> result = searchMatrix(matrix, target);
    if (result.first != -1) {
        cout << "Element found at position: (" << result.first << ", " << result.second << ")" << endl;
    } else {
        cout << "Element not found in the matrix." << endl;
    }

    return 0;
}
