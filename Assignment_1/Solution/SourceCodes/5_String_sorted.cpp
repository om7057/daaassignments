#include <iostream>
#include <vector>
#include <string>
using namespace std;

int findString(vector<string>& arr, string target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        int midLeft = mid, midRight = mid;
        while (arr[midLeft] == "" && midLeft >= left) {
            midLeft--;
        }
        while (arr[midRight] == "" && midRight <= right) {
            midRight++;
        }

        if (midLeft >= left && arr[midLeft] != "") {
            mid = midLeft;
        } else if (midRight <= right && arr[midRight] != "") {
            mid = midRight;
        } else {
            return -1; 
        }

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    vector<string> arr = {"at", "", "", "ball", "", "", "car", "", "", "dad", "", ""};
    string target = "ball";
    int index = findString(arr, target);
    if (index != -1) {
        cout << "The string \"" << target << "\" is located at index " << index << "." << endl;
    } else {
        cout << "The string \"" << target << "\" was not found in the array." << endl;
    }
    return 0;
}
