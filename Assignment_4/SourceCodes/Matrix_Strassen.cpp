#include <iostream>
#include <vector>

using namespace std;

// Function to add two matrices
void add(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void subtract(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen's Algorithm function
void strassen(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize)), A12(newSize, vector<int>(newSize)),
        A21(newSize, vector<int>(newSize)), A22(newSize, vector<int>(newSize)),
        B11(newSize, vector<int>(newSize)), B12(newSize, vector<int>(newSize)),
        B21(newSize, vector<int>(newSize)), B22(newSize, vector<int>(newSize)),
        C11(newSize, vector<int>(newSize)), C12(newSize, vector<int>(newSize)),
        C21(newSize, vector<int>(newSize)), C22(newSize, vector<int>(newSize)),
        M1(newSize, vector<int>(newSize)), M2(newSize, vector<int>(newSize)),
        M3(newSize, vector<int>(newSize)), M4(newSize, vector<int>(newSize)),
        M5(newSize, vector<int>(newSize)), M6(newSize, vector<int>(newSize)),
        M7(newSize, vector<int>(newSize)),
        tempA(newSize, vector<int>(newSize)), tempB(newSize, vector<int>(newSize));

    // Divide the matrices into 4 submatrices:
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Strassen's formula:
    add(A11, A22, tempA, newSize);
    add(B11, B22, tempB, newSize);
    strassen(tempA, tempB, M1, newSize);  // M1 = (A11 + A22) * (B11 + B22)

    add(A21, A22, tempA, newSize);        // M2 = (A21 + A22) * B11
    strassen(tempA, B11, M2, newSize);

    subtract(B12, B22, tempB, newSize);   // M3 = A11 * (B12 - B22)
    strassen(A11, tempB, M3, newSize);

    subtract(B21, B11, tempB, newSize);   // M4 = A22 * (B21 - B11)
    strassen(A22, tempB, M4, newSize);

    add(A11, A12, tempA, newSize);        // M5 = (A11 + A12) * B22
    strassen(tempA, B22, M5, newSize);

    subtract(A21, A11, tempA, newSize);
    add(B11, B12, tempB, newSize);        // M6 = (A21 - A11) * (B11 + B12)
    strassen(tempA, tempB, M6, newSize);

    subtract(A12, A22, tempA, newSize);
    add(B21, B22, tempB, newSize);        // M7 = (A12 - A22) * (B21 + B22)
    strassen(tempA, tempB, M7, newSize);

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, tempA, newSize);
    subtract(tempA, M5, tempB, newSize);
    add(tempB, M7, C11, newSize);

    // C12 = M3 + M5
    add(M3, M5, C12, newSize);

    // C21 = M2 + M4
    add(M2, M4, C21, newSize);

    // C22 = M1 - M2 + M3 + M6
    subtract(M1, M2, tempA, newSize);
    add(tempA, M3, tempB, newSize);
    add(tempB, M6, C22, newSize);

    // Combine the 4 submatrices into a single matrix by assigning the values:
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

int main() {
    int n = 3; // For a 3x3 matrix
    vector<vector<int>> A(3, vector<int>(3));
    vector<vector<int>> B(3, vector<int>(3));
    vector<vector<int>> C(4, vector<int>(4, 0)); // Result matrix after padding

    // Input matrix A
    cout << "Enter the elements of 3x3 matrix A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    // Input matrix B
    cout << "Enter the elements of 3x3 matrix B:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> B[i][j];
        }
    }

    // Pad A and B to 4x4 matrices
    vector<vector<int>> paddedA(4, vector<int>(4, 0)), paddedB(4, vector<int>(4, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            paddedA[i][j] = A[i][j];
            paddedB[i][j] = B[i][j];
        }
    }

    // Apply Strassen's algorithm on the padded matrices
    strassen(paddedA, paddedB, C, 4);

    // Output the result (3x3 part)
    cout << "Resultant Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
