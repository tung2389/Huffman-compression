/*
Class: CS 271, Fall 2021
Professor: Jessen Havill
Name: Tung Luu, Uyen Le
Date: October 21, 2021
Purpose: Answers to project 4
*/

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
            return (this->freq < other.freq);
        } 

        bool operator > (Node other) {
            return (this->freq > other.freq);
        } 
};

ostream& operator<<(ostream& out, const Node& node) {
	out << node.toString();
	return out;
}