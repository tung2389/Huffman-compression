#include<iostream>
#include<vector>
#include<fstream>
#include<unordered_map>
#include"pq.h"
#include"node.h"
using namespace std;

char pseudoEOF = '\0';

// Build a frequency dictionary of all characters in srcFile that maps each character to its frequency
void buildFrequencyDict(string srcFile, unordered_map<char, unsigned int>& charFreq) {
    ifstream inputFile(srcFile);
    if(inputFile.is_open()) {
        char c;
        while(inputFile.get(c)) {
            // c hasn't been found in map (or dictionary)
            if(charFreq.find(c) == charFreq.end()) {
                charFreq[c] = 0;
            }
            charFreq[c]++;
        }

        charFreq[pseudoEOF] = 1;
        inputFile.close();
    }
}   

Node * huffman(const vector<Node *>& nodes) {
    MinPriorityQueue<Node> pq;
    for(Node *node : nodes) {
        pq.insert(node);
    }

    for(int i = 0; i < nodes.size() - 1; i++) {
        Node *left = pq.extractMin();
        Node *right = pq.extractMin();

        Node *newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.insert(newNode);
    }

    return pq.extractMin();
}

// Build a dictionary that maps a character to its prefix code in the huffman tree.
void buildCharToCode(Node *node, string code, unordered_map<char, string>& charToCode) {
    // This is a leaf
    if(node->left == nullptr && node->right == nullptr) {
        charToCode[node->data] = code;
    }
    // Since huffman tree is a full binary tree, we always have valid left and right pointer
    else {
        buildCharToCode(node->left, code + "0", charToCode);
        buildCharToCode(node->right, code + "1", charToCode);
    }   
}

/*
Write the header containing frequency dictionary of all characters, which map each character to its frequency,
to the compresed file. The header is written to the file in normal ASCII characters, because its size is neligible 
comparing to the amount of saving by compressing the file content.
*/
void writeHeader(string destFile, const unordered_map<char, unsigned int>& charFreq) {
    ofstream outputFile(destFile);
    if(outputFile.is_open()) {
        outputFile << '{';
        for(auto it = charFreq.begin(); it != charFreq.end(); it++) {
            outputFile << it->first << it->second;
            if(it != charFreq.end()) {
                outputFile << ',';
            }
        }   
        outputFile << '}';
        outputFile.close();
    }
}   

void compress(string source, string dest) {
    // charFreq is a dictionary that maps each character to its frequency
    unordered_map<char, unsigned int> charFreq;
    buildFrequencyDict(source, charFreq);

    // nodes is the list of Node instances of all characters in the source file
    vector<Node *> nodes;
    for(auto it = charFreq.begin(); it != charFreq.end(); it++) {
        nodes.push_back(new Node(it->first, it->second));
    }
    Node *root = huffman(nodes);

    // charToCode is a dictionary that maps a character to its prefix code in the huffman tree.
    unordered_map<char, string> charToCode;
    buildCharToCode(root, "", charToCode);

    writeHeader(dest, charFreq);
}

void decompress() {

}

int main(int argc, char *argv[]) {
    if(argc != 4) {
        cout << "Incorrect format" << endl;
        return 0;
    }

    string flag = argv[1];
    
    if(flag == "-c") {
        string source = argv[2], dest = argv[3];
        compress(source, dest);
    }
}