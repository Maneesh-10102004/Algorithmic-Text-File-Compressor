#include "BinaryTreeNode.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iterator>
using namespace std;

// Deserializes the Huffman tree from the input file
BinaryTreeNode* deserializeTree(ifstream& infile) {
    char data = infile.get();
    if (data == '#') {
        return nullptr;
    }
    BinaryTreeNode* node;
    if (data == '$') {
        node = new BinaryTreeNode('\0', 0);
    } else {
        node = new BinaryTreeNode(data, 0);
    }
    node->left = deserializeTree(infile);
    node->right = deserializeTree(infile);
    return node;
}


// Reads the bit string from the input file
string readBitString(ifstream &infile, int bitLength) {
    string bitString;
    bitString.reserve(bitLength);
    char byte;
    while (infile.get(byte)) {
        bitset<8> bits(byte);
        for (int i = 0; i < 8 && bitString.size() < bitLength; ++i) {
            bitString.push_back(bits.test(7 - i) ? '1' : '0');
        }
    }
    return bitString;
}

// Decompresses the bit string using the Huffman tree
string decompressString(BinaryTreeNode* root, const string &bitString) {
    string decompressedString;
    BinaryTreeNode* currentNode = root;
    for (char bit : bitString) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
        if (!currentNode->left && !currentNode->right) {
            decompressedString.push_back(currentNode->getdata());
            currentNode = root;
        }
    }
    return decompressedString;
}

// Reads the compressed file and returns the decompressed string
string readAndDecompressFile(const string& input_filename) {
    ifstream infile(input_filename, ios::binary);
    if (!infile) {
        throw runtime_error("Error opening input file");
    }

    int original_bit_length;
    infile.read(reinterpret_cast<char*>(&original_bit_length), sizeof(original_bit_length));
    BinaryTreeNode* root = deserializeTree(infile);
    string bitString = readBitString(infile, original_bit_length);
    infile.close();

    return decompressString(root, bitString);
}

// Writes the decompressed string to the output file
void writeOutputFile(const string& output_filename, const string& decompressedString) {
    ofstream outfile(output_filename);
    if (!outfile) {
        throw runtime_error("Error opening output file for writing");
    }
    outfile << decompressedString;
    outfile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <inputfile> <outputfile>" << endl;
        return 1;
    }

    try {
        string input_filename = argv[1];
        string output_filename = argv[2];

        string decompressedString = readAndDecompressFile(input_filename);
        writeOutputFile(output_filename, decompressedString);
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}

