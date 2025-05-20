#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Person {
    int height;
    int weight;
};

bool compare(const Person& a, const Person& b) {
    if (a.height == b.height)
        return a.weight < b.weight;
    return a.height < b.height;
}


int longestIncreasingSubsequence(vector<Person>& people) {
    int n = people.size();
    vector<int> dp(n, 1);
    int maxLength = 1;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (people[i].weight > people[j].weight) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLength = max(maxLength, dp[i]);
    }
    return maxLength;
}

int main() {
    vector<Person> people = {{65, 100}, {70, 150}, {56, 90}, {75, 190}, {60, 95}, {68, 110}};
    
    sort(people.begin(), people.end(), compare);
    
    int maxTowerHeight = longestIncreasingSubsequence(people);
    
    cout << "The longest tower has length " << maxTowerHeight << " and includes the following people from top to bottom:" << endl;

     vector<Person> tower;
    int n = people.size();
    vector<int> dp(n, 1), parent(n, -1);
    int maxLength = 1, bestEnd = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (people[i].weight > people[j].weight && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            bestEnd = i;
        }
    }

    for (int i = bestEnd; i != -1; i = parent[i]) {
        tower.push_back(people[i]);
    }

    reverse(tower.begin(), tower.end());

    for (const auto& person : tower) {
        cout << "(" << person.height << ", " << person.weight << ")" << endl;
    }

    return 0;
}
