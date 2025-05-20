#include <iostream>
using namespace std;

int main() {
    int n, m, p;
    
    // Input dimensions of matrices A and B
    cout << "Enter dimensions of matrix A (n x m): ";
    cin >> n >> m;
    cout << "Enter dimensions of matrix B (m x p): ";
    cin >> m >> p;
    
    int A[n][m], B[m][p], C[n][p];

    // Input matrix A
    cout << "Enter matrix A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }

    // Input matrix B
    cout << "Enter matrix B:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            cin >> B[i][j];
        }
    }

    // Initialize matrix C to zero
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
        }
    }

    // Naive matrix multiplication
    for (int i = 0; i < n; i++) {           
        for (int j = 0; j < p; j++) {       
            for (int k = 0; k < m; k++) {   
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Output the result matrix C
    cout << "Resultant matrix C:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
