#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<unordered_map>
#include"pq.h"
#include"node.h"
using namespace std;

/*
The pseudo end of file character is used to terminate reading prefix codes when decompress. Because the smallest unit that we can write to a
file is byte, we will need padding when our compressed data doesn't fill the whole last byte. To avoid reading meaningless padding bits, we
use the pseudo character to signal the end of our data.
*/
char pseudoEOF = '\0';

class Huffman {
    public:
        Huffman(string source, string dest) {
            this->source = source;
            this->dest = dest;
        }

        void compress();
        void decompress();

    private:
        string source, dest;  // The source and destination files
        string data;  // The data in the source file
        Node *root;  // The root of the huffman tree

        unordered_map<char, unsigned int> charFreq;  // charFreq is a dictionary that maps each character to its frequency
        unordered_map<char, string> charToCode; // charToCode is a dictionary that maps a character to its prefix code in the huffman tree.

        void readFile();
        void buildFrequencyDict();
        void buildHuffmanTree();
        void buildCharToCode(Node *node, string code);
        void writeHeaderToFile();
        void writePrefixCodesToFile();

        void writeDecodedCharacters();
};