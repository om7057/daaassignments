#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1; 
        int j = n - 1; 
        int k = m + n - 1; 
        
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }
        
         while (j >= 0) {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
};

int main() {
    int n, m;
    cout << "Enter size of first array : ";
    cin >> m;
    cout << "Enter size of second array : ";
    cin >> n;

    vector<int> nums1(m + n);
    vector<int> nums2(n);

    cout << "Enter elements in the first array (valid elements only): \n";
    for (int i = 0; i < m; i++) {
        cin >> nums1[i];
    }

    cout << "Enter elements in the second array: \n";
    for (int i = 0; i < n; i++) {
        cin >> nums2[i];
    }

    Solution obj;
    obj.merge(nums1, m, nums2, n);

    cout << "Merged Array: \n";
    for (int i = 0; i < m + n; i++) {
        cout << nums1[i] << " ";
    }
    cout << endl;

    return 0;
}
