#include<iostream>
#include<vector>
#include<fstream>
#include<unordered_map>
#include"huffman.h"
using namespace std;

/*
Read the entire content of the file into the string data of Huffman class.
*/

void Huffman::readFile() {
    ifstream inputFile(source);
    if(inputFile.is_open()) {
        stringstream ss;
        ss << inputFile.rdbuf();
        data = ss.str();
        inputFile.close();
    }
}

/*
Build a frequency dictionary of all characters in the source file that maps each character to its frequency
*/
void Huffman::buildFrequencyDict() {
    for(char c : data) {
        // c hasn't been found in map (or dictionary)
        if(charFreq.find(c) == charFreq.end()) {
            charFreq[c] = 0;
        }
        charFreq[c]++;
    }
    charFreq[pseudoEOF] = 1;
}   

/*
Build a huffman tree of all characters in the source file.
*/
void Huffman::buildHuffmanTree() {
    // nodes is the list of Node instances of all characters in the source file
    vector<Node *> nodes;
    for(auto it = charFreq.begin(); it != charFreq.end(); it++) {
        nodes.push_back(new Node(it->first, it->second));
    }

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

    this->root = pq.extractMin();
}

/*
Build a dictionary that maps each character to its prefix code in the huffman tree.
*/
void Huffman::buildCharToCode(Node *node, string code) {
    // This is a leaf
    if(node->left == nullptr && node->right == nullptr) {
        charToCode[node->data] = code;
    }
    // Since huffman tree is a full binary tree, we always have valid left and right pointer
    else {
        buildCharToCode(node->left, code + "0");
        buildCharToCode(node->right, code + "1");
    }   
}

/*
Write the header containing frequency dictionary of all characters, which map each character to its frequency,
to the compresed file. The header is written to the file in normal ASCII characters, because its size is neligible 
comparing to the amount of saving by compressing the file content.
*/
void Huffman::writeHeaderToFile() {
    ofstream outputFile(dest);
    if(outputFile.is_open()) {
        outputFile << '{';
        for(auto it = charFreq.begin(); it != charFreq.end(); it++) {
            outputFile << it->first << it->second;
            if(it != charFreq.end()) {
                outputFile << ',';
            }
        }   
        outputFile << '}';
        outputFile.flush();
        outputFile.close();
    }
}   

/*
Write prefix codes corresponding to characters from source file to the destinaton file in bits.
*/
// void Huffman::writePrefixCodesToFile() {
//     int curBit = 0;
//     char byte = 0;
//     string encodedData = "";
//     for(char c: data) {
//         string code = charToCode[c];
//         encodedData += code;
//     }

//     for(char bit: encodedData) {
//         if(bit == '1') {
//             byte = byte | (1 << (8 - curBit - 1));
//         }
//         curBit++;
//         if(curBit == 8) {

//         }
//     }
// }

void Huffman::compress() {
    readFile();
    buildFrequencyDict();
    buildHuffmanTree();
    buildCharToCode(root, "");

    writeHeaderToFile();
    // writePrefixCodesToFile();
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
        Huffman *huffman = new Huffman(source, dest);
        huffman->compress();
    }
}