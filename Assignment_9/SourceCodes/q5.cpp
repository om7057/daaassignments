#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Tower {
    int x, y;
};

bool canDestroy(const vector<Tower>& towers, int d, int k) {
    vector<bool> destroyed(towers.size(), false);
    int count = 0;

    for (int i = 0; i < towers.size(); i++) {
        if (destroyed[i]) continue;
        count++;
        for (int j = i + 1; j < towers.size(); j++) {
            if (destroyed[j]) continue;
            int dx = towers[i].x - towers[j].x;
            int dy = towers[i].y - towers[j].y;
            if (dx * dx + dy * dy == d * d) {
                destroyed[j] = true;
            }
        }
    }

    return towers.size() - count <= k;
}

int minTowersToDestroy(const vector<Tower>& towers, int d) {
    int left = 0, right = towers.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canDestroy(towers, d, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    int n, d;
    cout << "Enter the number of towers (n) and the interference distance (d): ";
    cin >> n >> d;

    vector<Tower> towers(n);
    cout << "Enter the coordinates of each tower (x y):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Tower " << i + 1 << ": ";
        cin >> towers[i].x >> towers[i].y;
    }

    int result = minTowersToDestroy(towers, d);
    cout << "Minimum number of towers to destroy: " << result << endl;

    return 0;
}