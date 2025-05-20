#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cstdio>
#include <iterator>

using namespace std;

const size_t CHUNK_SIZE = 100 * 1024 * 1024; 

vector<string> readChunk(ifstream &file, size_t chunkSize) {
    vector<string> lines;
    lines.reserve(chunkSize / 100); 
    string line;
    size_t currentSize = 0;
    while (currentSize < chunkSize && getline(file, line)) {
        lines.push_back(line);
        currentSize += line.size() + 1;
    }
    return lines;
}

void writeChunk(const vector<string> &lines, const string &filename) {
    ofstream outFile(filename);
    for (const auto &line : lines) {
        outFile << line << '\n';
    }
}

void mergeChunks(const vector<string> &chunkFiles, const string &outputFile) {
    auto comp = [](const pair<string, ifstream*> &a, const pair<string, ifstream*> &b) {
        return a.first > b.first;
    };
    priority_queue<pair<string, ifstream*>, vector<pair<string, ifstream*>>, decltype(comp)> minHeap(comp);
    
    vector<ifstream*> chunkStreams;
    for (const auto &filename : chunkFiles) {
        ifstream *stream = new ifstream(filename);
        chunkStreams.push_back(stream);
        string line;
        if (getline(*stream, line)) {
            minHeap.push({line, stream});
        }
    }

    ofstream outFile(outputFile);
    while (!minHeap.empty()) {
        auto [line, stream] = minHeap.top();
        minHeap.pop();
        outFile << line << '\n';
        if (getline(*stream, line)) {
            minHeap.push({line, stream});
        }
    }

    for (auto stream : chunkStreams) {
        stream->close();
        delete stream;
    }

    for (const auto &filename : chunkFiles) {
        remove(filename.c_str());
    }
}

void externalSort(const string &inputFile, const string &outputFile, size_t chunkSize) {
    ifstream inFile(inputFile);
    vector<string> chunkFiles;
    int chunkCount = 0;

    while (true) {
        vector<string> lines = readChunk(inFile, chunkSize);
        if (lines.empty()) {
            break;
        }
        sort(lines.begin(), lines.end());
        string chunkFile = "chunk_" + to_string(chunkCount++) + ".txt";
        writeChunk(lines, chunkFile);
        chunkFiles.push_back(chunkFile);
    }

    mergeChunks(chunkFiles, outputFile);
}

int main() {
    string inputFile = "large_file.txt";
    string outputFile = "sorted_file.txt";
    externalSort(inputFile, outputFile, CHUNK_SIZE);
    return 0;
}
