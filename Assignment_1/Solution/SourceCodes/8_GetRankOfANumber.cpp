#include <iostream>
using namespace std;

class RankNode {
public:
    int data;
    RankNode* left;
    RankNode* right;
    int leftSize;

    RankNode(int d) : data(d), left(nullptr), right(nullptr), leftSize(0) {}
};

class StreamRank {
private:
    RankNode* root;

    void insert(int x, RankNode* node) {
        if (x <= node->data) {
            if (node->left != nullptr) {
                insert(x, node->left);
            } else {
                node->left = new RankNode(x);
            }
            node->leftSize++;
        } else {
            if (node->right != nullptr) {
                insert(x, node->right);
            } else {
                node->right = new RankNode(x);
            }
        }
    }

    int getRank(int x, RankNode* node) {
        if (node == nullptr) return -1;

        if (x == node->data) {
            return node->leftSize;
        } else if (x < node->data) {
            return getRank(x, node->left);
        } else {
            int rightRank = getRank(x, node->right);
            if (rightRank == -1) return -1;
            return node->leftSize + 1 + rightRank;
        }
    }

public:
    StreamRank() : root(nullptr) {}

    void track(int x) {
        if (root == nullptr) {
            root = new RankNode(x);
        } else {
            insert(x, root);
        }
    }

    int getRankOfNumber(int x) {
        return getRank(x, root);
    }
};

int main() {
    StreamRank sr;
    int stream[] = {5, 1, 4, 4, 5, 9, 7, 13, 3};

    for (int x : stream) {
        sr.track(x);
    }

    cout << "getRankOfNumber(1) = " << sr.getRankOfNumber(1) << endl; 
    cout << "getRankOfNumber(3) = " << sr.getRankOfNumber(3) << endl; 
    cout << "getRankOfNumber(4) = " << sr.getRankOfNumber(4) << endl; 

    return 0;
}
