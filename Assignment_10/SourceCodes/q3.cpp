#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to calculate the number of cells the Queen can move
int countQueenMoves(int N, int Qx, int Qy, vector<pair<int, int>>& obstacles) {
    // Directions: up, down, left, right, top-left, top-right, bottom-left, bottom-right
    int up = N - Qx;
    int down = Qx - 1;
    int left = Qy - 1;
    int right = N - Qy;
    int topLeft = min(N - Qx, Qy - 1);
    int topRight = min(N - Qx, N - Qy);
    int bottomLeft = min(Qx - 1, Qy - 1);
    int bottomRight = min(Qx - 1, N - Qy);

    // Adjust boundaries based on obstacles
    for (auto& obs : obstacles) {
        int ox = obs.first, oy = obs.second;

        // Same column (vertical movement)
        if (oy == Qy) {
            if (ox > Qx) {
                up = min(up, ox - Qx - 1); 
            } else {
                down = min(down, Qx - ox - 1); 
            }
        }

        // Same row (horizontal movement)
        if (ox == Qx) {
            if (oy > Qy) {
                right = min(right, oy - Qy - 1); 
            } else {
                left = min(left, Qy - oy - 1); 
            }
        }

        // Diagonal movements
        if (abs(ox - Qx) == abs(oy - Qy)) {
            if (ox > Qx && oy > Qy) {
                topRight = min(topRight, ox - Qx - 1); 
            } else if (ox > Qx && oy < Qy) {
                topLeft = min(topLeft, ox - Qx - 1); 
            } else if (ox < Qx && oy > Qy) {
                bottomRight = min(bottomRight, Qx - ox - 1); 
            } else if (ox < Qx && oy < Qy) {
                bottomLeft = min(bottomLeft, Qx - ox - 1); 
            }
        }
    }

    // Total possible moves
    return up + down + left + right + topLeft + topRight + bottomLeft + bottomRight;
}

int main() {
    int N, K, Qx, Qy;
    
    // Inputs
    cout << "Enter the size of the board (N): ";
    cin >> N;

    cout << "Enter the Queen's position (Qx, Qy): ";
    cin >> Qx >> Qy;

    cout << "Enter the number of obstacles (K): ";
    cin >> K;

    vector<pair<int, int>> obstacles(K);
    if (K > 0) {
        cout << "Enter the positions of obstacles (ox oy): " << endl;
        for (int i = 0; i < K; i++) {
            cin >> obstacles[i].first >> obstacles[i].second;
        }
    }

    int result = countQueenMoves(N, Qx, Qy, obstacles);
    cout << "The number of cells the Queen can move to: " << result << endl;

    return 0;
}
