#include <iostream>
using namespace std;

int main() {
    int n, k;
    cout << "Enter the number of boxes: ";
    cin >> n;
    cout << "Enter the number of candies: ";
    cin >> k;

    int box = 1;
    int step = 1;

    for (int i = 1; i < k; ++i) {
        if (step == 1) {
            if (box < n) {
                box += 1;
            } else {
                step = -1;
                box -= 1;
            }
        } else { 
            if (box > 1) {
                box -= 1;
            } else {
                step = 1;
                box += 1;
            }
        }
    }

    cout << "The " << k << "-th candy is placed in box number: " << box << endl;

    return 0;
}
