#include <iostream>
using namespace std;

void hanoi(int n, char from, char to, char temp) {
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }
    hanoi(n - 1, from, temp, to);
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    hanoi(n - 1, temp, to, from);
}

int main() {
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;

    cout << "Steps to solve the Tower of Hanoi problem with " << n << " disks:\n";
    hanoi(n, 'A', 'C', 'B'); 
    return 0;
}
