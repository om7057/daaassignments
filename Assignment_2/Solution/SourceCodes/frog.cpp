#include <iostream>
using namespace std;

int main() {
    int X, Y, s, T;
    cin >> X >> Y >> s >> T;

    int count = 0;

    for (int x = X; x <= X + s; ++x) {
        int y = T - x; 
        if (y >= Y && y <= Y + s) {
            count++;
        }
    }

    cout << count << endl;
    return 0;
}
