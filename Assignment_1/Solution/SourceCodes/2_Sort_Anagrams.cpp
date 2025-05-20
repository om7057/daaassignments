#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<string> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> anagramGroups;

        for (string str : strs)
        {
            string sortedStr = str;
            sort(sortedStr.begin(), sortedStr.end());
            anagramGroups[sortedStr].push_back(str);
        }

        vector<string> result;
        for (auto &group : anagramGroups)
        {
            for (string &anagram : group.second)
            {
                result.push_back(anagram);
            }
        }

        return result;
    }
};

int main()
{
    int n;
    cout << "Enter the number of strings: ";
    cin >> n;

    vector<string> strs(n);
    cout << "Enter the strings:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cin >> strs[i];
    }

    Solution solution;
    vector<string> sortedAnagrams = solution.groupAnagrams(strs);

    cout << "Anagrams grouped together:" << endl;
    for (string &str : sortedAnagrams)
    {
        cout << str << " ";
    }
    cout << endl;

    return 0;
}
