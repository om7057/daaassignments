#include <iostream>
#define N 32 

int tileNum = 1; 
int board[N][N]; 

void tileBoard(int topRow, int topCol, int defectRow, int defectCol, int size) {
    if (size == 2) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (topRow + i != defectRow || topCol + j != defectCol) {
                    board[topRow + i][topCol + j] = tileNum;
                }
            }
        }
        tileNum++;
        return;
    }

    int halfSize = size / 2;

    int centerRow = topRow + halfSize;
    int centerCol = topCol + halfSize;

    if (defectRow < centerRow && defectCol < centerCol) {
        tileBoard(topRow, topCol, defectRow, defectCol, halfSize);
        tileBoard(topRow, centerCol, centerRow - 1, centerCol, halfSize);
        tileBoard(centerRow, topCol, centerRow, centerCol - 1, halfSize);
        tileBoard(centerRow, centerCol, centerRow, centerCol, halfSize);
    } else if (defectRow < centerRow && defectCol >= centerCol) {
        tileBoard(topRow, topCol, centerRow - 1, centerCol - 1, halfSize);
        tileBoard(topRow, centerCol, defectRow, defectCol, halfSize);
        tileBoard(centerRow, topCol, centerRow, centerCol - 1, halfSize);
        tileBoard(centerRow, centerCol, centerRow, centerCol, halfSize);
    } else if (defectRow >= centerRow && defectCol < centerCol) {
        tileBoard(topRow, topCol, centerRow - 1, centerCol - 1, halfSize);
        tileBoard(topRow, centerCol, centerRow - 1, centerCol, halfSize);
        tileBoard(centerRow, topCol, defectRow, defectCol, halfSize);
        tileBoard(centerRow, centerCol, centerRow, centerCol, halfSize);
    } else {
        tileBoard(topRow, topCol, centerRow - 1, centerCol - 1, halfSize);
        tileBoard(topRow, centerCol, centerRow - 1, centerCol, halfSize);
        tileBoard(centerRow, topCol, centerRow, centerCol - 1, halfSize);
        tileBoard(centerRow, centerCol, defectRow, defectCol, halfSize);
    }
}

int main() {
    int n;
    std::cout << "Enter the size of the board (n x n where n is a power of 2): ";
    std::cin >> n;

    int defectRow, defectCol;
    std::cout << "Ente-r the position of the missing cell (row and column): ";
    std::cin >> defectRow >> defectCol;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }

    tileBoard(0, 0, defectRow, defectCol, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << board[i][j] << "\t";
        }
        std::cout << "\n";
    }

    return 0;
}
