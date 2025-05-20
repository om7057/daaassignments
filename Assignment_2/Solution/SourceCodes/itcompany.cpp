#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cout << "Enter the number of working days: ";
    cin >> N;

    vector<int> workload(N);
    cout << "Enter the workload (hours worked each day): ";
    for (int i = 0; i < N; ++i) {
        cin >> workload[i];
    }

    int max_consecutive_days = 0;
    int current_consecutive_days = 0;

    for (int i = 0; i < N; ++i) {
        if (workload[i] > 6) {
            current_consecutive_days += 1;
        } else {
            if (current_consecutive_days > max_consecutive_days) {
                max_consecutive_days = current_consecutive_days;
            }
            current_consecutive_days = 0;
        }
    }

    if (current_consecutive_days > max_consecutive_days) {
        max_consecutive_days = current_consecutive_days;
    }

    cout << "Employee rating: " << max_consecutive_days << endl;

    return 0;
}
