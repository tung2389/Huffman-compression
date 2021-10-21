#include<iostream>
#include<vector>
#include<fstream>
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
        // Append pseudoEOF character to our string data to handle padding
        data += pseudoEOF;
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
    if(node == nullptr) return;
    
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
            // A temp pointer to check if we have reach the last entry of the dictionary.
            auto tempIt = it;
            if((++tempIt) != charFreq.end()) {
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
void Huffman::writePrefixCodesToFile() {
    int curBit = 0;
    unsigned char byte = 0;
    string encodedData = "";

    for(char c: data) {
        string code = charToCode[c];
        encodedData += code;
    }

    ofstream outputFile(dest, ios::app);

    for(char bit: encodedData) {
        if(bit == '1') {
            byte = byte | (1 << (8 - curBit - 1));
        }
        curBit++;
        if(curBit == 8) {
            curBit = 0;
            outputFile << byte;
            byte = 0;
        }
    }

    // Padding last bits in the last byte with 0 and write the last byte
    if(curBit < 8) {
        outputFile << byte;
    }

    outputFile.flush();
    outputFile.close();
}

/*
Compress the source file and write the compressed data to the destination file
*/
void Huffman::compress() {
    readFile();
    buildFrequencyDict();
    buildHuffmanTree();
    buildCharToCode(root, "");
    writeHeaderToFile();
    writePrefixCodesToFile();
}

/*
Extract the header of a compressed file from string data of Huffman class, and parse this header to create charFreq dictionary.
*/
void Huffman::parseHeader() {
    int idx = 1;
    // Iterate until we reach the end of the header
    while(!(data[idx] == '}' && data[idx - 1] != ',')) {
        char c = data[idx];
        string freq = "";
        idx++;
        while(data[idx] != ',' && data[idx] != '}') {
            freq.push_back(data[idx]);
            idx++;
        }
        charFreq[c] = (unsigned int)stoul(freq);
        if(data[idx] == ',') {
            idx++;
        }
    }
    // Remove the header from the string data of Huffman class, leaving only real data
    data = data.substr(idx + 1, string::npos);
}

/*
Traverse over the string data (which is the content of the source file) 
and write the character that corresponds to each prefix code in the source file to the destination file.
*/
void Huffman::writeDecodedCharacters() {
    ofstream outputFile(dest);
    Node *curNode = root;

    for(char c : data) {
        int curBit = 0;

        for(int curBit = 0; curBit < 8; curBit++) {
            // We have reach a leave and successfully decode a character
            if(curNode->left == nullptr && curNode->right == nullptr) {
                if(curNode->data != pseudoEOF) {
                    outputFile << curNode->data;
                } 
                // We have reach the pseudoEOF character, stop reading
                else {
                    break;
                }
                curNode = root;
            }

            bool bit = c & (1 << (8 - curBit - 1));
            if(bit) {
                curNode = curNode->right;
            }
            else {
                curNode = curNode->left;
            }
        }
    }

    outputFile.flush();
    outputFile.close();
}

void Huffman::decompress() {
    readFile();
    parseHeader();
    buildHuffmanTree();
    buildCharToCode(root, "");
    writeDecodedCharacters();
}

int main(int argc, char *argv[]) {
    if(argc != 4) {
        cout << "Incorrect command's format" << endl;
        return 0;
    }

    string flag = argv[1];
    string source = argv[2], dest = argv[3];

    if(flag == "-c") {
        Huffman *huffman = new Huffman(source, dest);
        huffman->compress();
    }
    else if(flag == "-d") {
        Huffman *huffman = new Huffman(source, dest);
        huffman->decompress();
    }
    else {
        cout << "Incorrect command's format" << endl;
        return 0;
    }
}