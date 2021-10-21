#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include"pq.h"
#include"node.h"
using namespace std;

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
        /*
        The pseudo end of file character is used to terminate reading prefix codes when decompress. Because the smallest unit that we can write to a
        file is byte, we will need padding when our compressed data doesn't fill the whole last byte. To avoid reading meaningless padding bits, we
        use the pseudo character to signal the end of our data.
        */
        char pseudoEOF = '\0';

        map<char, unsigned int> charFreq;  // charFreq is a dictionary that maps each character to its frequency
        map<char, string> charToCode; // charToCode is a dictionary that maps a character to its prefix code in the huffman tree.

        /*
        We use map as our dictionary for convenience and efficiency. Although the time complexity of accessing an element in the map is log(n),
        the type char can only represents a maximum of 2^8 values, therefore it's log(2^8) in the worst case, which is a constant time O(1). Therefore,
        the time complexity of accessing an element in our map is O(1).
        */

        void readFile();
        void buildFrequencyDict();
        void buildHuffmanTree();
        void buildCharToCode(Node *node, string code);
        void writeHeaderToFile();
        void writePrefixCodesToFile();

        void parseHeader();
        void writeDecodedCharacters();
};