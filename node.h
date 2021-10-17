#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class Node {
    public:
        char data;
        unsigned int freq;
        Node *left;
        Node *right;

        Node(char data, unsigned int freq) {
            this->data = data;
            this->freq = freq;
            left = nullptr;
            right = nullptr;
        }
        
        string toString() const {
            stringstream ss;
            ss << "{" << data << ": " << freq;
            return ss.str();
        }

        bool operator < (Node other) {
            return (this->data < other.data);
        } 
}

ostream& operator<<(ostream& out, const Node& Node) {
	out << node.toString();
	return out;
}