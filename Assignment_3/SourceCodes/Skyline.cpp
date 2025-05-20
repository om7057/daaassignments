#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Building {
    int left, height, right;
};

struct Strip {
    int left, height;
    Strip(int l, int h) : left(l), height(h) {}-
};

class Skyline {
public:
    vector<Strip> strips;

void addStrip(Strip s) {
        if (!strips.empty() && strips.back().height == s.height)
            return; 

        if (!strips.empty() && strips.back().left == s.left) {
            strips.back().height = max(strips.back().height, s.height);
            return;
        }

        strips.push_back(s);
    }

   Skyline merge(Skyline &other) {
        Skyline result;
        int h1 = 0, h2 = 0;
        size_t i = 0, j = 0;

        while (i < strips.size() && j < other.strips.size()) {
            if (strips[i].left < other.strips[j].left) {
                int x = strips[i].left;
                h1 = strips[i].height;
                int maxHeight = max(h1, h2);
                result.addStrip(Strip(x, maxHeight));
                i++;
            } else if (other.strips[j].left < strips[i].left) {
                int x = other.strips[j].left;
                h2 = other.strips[j].height;
                int maxHeight = max(h1, h2);
                result.addStrip(Strip(x, maxHeight));
                j++;
            } else {
                int x = strips[i].left;
                h1 = strips[i].height;
                h2 = other.strips[j].height;
                int maxHeight = max(h1, h2);
                result.addStrip(Strip(x, maxHeight));
                i++;
                j++;
            }
        }

        while (i < strips.size()) {
            result.addStrip(strips[i]);
            i++;
        }

        while (j < other.strips.size()) {
            result.addStrip(other.strips[j]);
            j++;
        }

        return result;
    }
};

Skyline getSkyline(vector<Building> &buildings, int low, int high) {
    if (low == high) {
        Skyline skyline;
        skyline.addStrip(Strip(buildings[low].left, buildings[low].height));
        skyline.addStrip(Strip(buildings[low].right, 0));
        return skyline;
    }

    int mid = (low + high) / 2;
    Skyline leftSkyline = getSkyline(buildings, low, mid);
    Skyline rightSkyline = getSkyline(buildings, mid + 1, high);

    return leftSkyline.merge(rightSkyline);
}

int main() {
    vector<Building> buildings = {
        {1, 11, 5},
        {2, 6, 7},
        {3, 13, 9},
        {12, 7, 16},
        {14, 3, 25},
        {19, 18, 22},
        {23, 13, 29},
        {24, 4, 28}
    };

    int n = buildings.size();
    Skyline skyline = getSkyline(buildings, 0, n - 1);

    cout << "Skyline (left, height):\n";
    for (const Strip &s : skyline.strips) {
        cout << "(" << s.left << ", " << s.height << ")\n";
    }

    return 0;
}
