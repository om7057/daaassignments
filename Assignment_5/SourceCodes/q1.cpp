#include <iostream>
using namespace std;

// Function to calculate the number of connections for `n` houses
int connections(int n) {
    return (n * (n - 1)) / 2;
}

int main() {
    int A, B;
    cout << "Enter the number of houses (A) and the number of localities (B): ";
    cin >> A >> B;

    // Maximum number of connections: One large locality, rest with one house each
    int maxConnections = connections(A - B + 1);  // (A-B+1) houses in one large locality
    for (int i = 1; i < B; ++i) {
        maxConnections += connections(1);  // Each of the other (B-1) localities has 1 house
    }

    // Minimum number of connections: Distribute houses as evenly as possible
    int housesPerLocality = A / B;
    int remainder = A % B;
    int minConnections = 0;

    // Add connections for the localities with (housesPerLocality + 1) houses
    for (int i = 0; i < remainder; ++i) {
        minConnections += connections(housesPerLocality + 1);
    }

    // Add connections for the localities with housesPerLocality houses
    for (int i = 0; i < (B - remainder); ++i) {
        minConnections += connections(housesPerLocality);
    }

    // Output the results
    cout << "Minimum number of connections: " << minConnections << endl;
    cout << "Maximum number of connections: " << maxConnections << endl;

    return 0;
}
