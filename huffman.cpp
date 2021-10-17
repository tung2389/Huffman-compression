#include<iostream>
#include<fstream>
#include<unordered_map>
#include"pq.h"
#include"node.h"
using namespace std;

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

void compress(const vector<Node *>& nodes) {
    Node *root = huffman(nodes);
    // unordered_map
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
        ifstream inputFile(source);
        unordered_map<char, unsigned int> charFreq;

        if(inputFile.is_open()) {
            char c;
            while(inputFile.get(c)) {
                // c hasn't been found in map (or dictionary)
                if(charFreq.find(c) == charFreq.end()) {
                    charFreq[c] = 0;
                }
                charFreq[c]++;
            }

            vector<Node *> nodes;
            for(auto it = charFreq.begin(); it != charFreq.end(); it++) {
                nodes.push_back(new Node(it->first, it->second));
            }
        }
    }
}