#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

// Function to check if a word is present in the dictionary
bool dictionaryContains(string word, unordered_set<string>& dictionary) {
    return dictionary.find(word) != dictionary.end();
}

// Helper function to perform backtracking and find all word breaks
void wordBreakUtil(string s, unordered_set<string>& dictionary, string result, vector<string>& output) {
    // If we've reached the end of the string, add the result to the output
    if (s.size() == 0) {
        output.push_back(result);
        return;
    }

    // Try every prefix of the string
    for (int i = 1; i <= s.size(); i++) {
        string prefix = s.substr(0, i);

        // If the prefix is a valid word, proceed to check the remaining substring
        if (dictionaryContains(prefix, dictionary)) {
            string newResult = result + (result.empty() ? "" : " ") + prefix;
            wordBreakUtil(s.substr(i), dictionary, newResult, output);
        }
    }
}

// Main function to find all word breaks
vector<string> wordBreak(string s, unordered_set<string>& dictionary) {
    vector<string> output;
    wordBreakUtil(s, dictionary, "", output);
    return output;
}

int main() {
    // Create a dictionary of valid words
    unordered_set<string> dictionary = { "i", "like", "sam", "sung", "samsung", "mobile", "ice", "and", "cream", "icecream", "man", "go", "mango" };

    // Input sentence without spaces
    string input1 = "ilikesamsungmobile";
    string input2 = "ilikeicecreamandmango";

    // Get all possible word breaks for the first input
    vector<string> result1 = wordBreak(input1, dictionary);
    cout << "Possible segmentations for input \"" << input1 << "\":" << endl;
    for (string& sentence : result1) {
        cout << sentence << endl;
    }

    // Get all possible word breaks for the second input
    vector<string> result2 = wordBreak(input2, dictionary);
    cout << "\nPossible segmentations for input \"" << input2 << "\":" << endl;
    for (string& sentence : result2) {
        cout << sentence << endl;
    }

    return 0;
}
