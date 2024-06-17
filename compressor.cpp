#include "BinaryTreeNode.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iterator>
using namespace std;

// Comparator for priority queue to build the Huffman tree
struct comp {
    bool operator()(BinaryTreeNode* a, BinaryTreeNode* b) {
        return a->getfrequency() > b->getfrequency();
    }
};

// Assigns codes to characters by traversing the Huffman tree
void assigncodes(BinaryTreeNode* root, string &temp, unordered_map<char, string>& charactercodes) {
    if (!root->left && !root->right) {
        charactercodes[root->getdata()] = temp;
        return;
    }
    if (root->left) {
        temp.push_back('0');
        assigncodes(root->left, temp, charactercodes);
        temp.pop_back();
    }
    if (root->right) {
        temp.push_back('1');
        assigncodes(root->right, temp, charactercodes);
        temp.pop_back();
    }
}

// Serializes the Huffman tree to the output file
void serializeTree(BinaryTreeNode* root, ofstream& outfile) {
    if (!root) {
        outfile.put('#');  // Use '#' as a marker for null pointers
        return;
    }
    if (root->getdata() == '\0') {
        outfile.put('$');  // Use '$' as a marker for internal nodes
    } else {
        outfile.put(root->getdata());
    }
    serializeTree(root->left, outfile);
    serializeTree(root->right, outfile);
}


// Converts the bit string to a byte array
std::vector<uint8_t> convertToByteArray(const std::string &bitString) {
    std::vector<uint8_t> byteArray;
    int bitLength = bitString.length();
    for (int i = 0; i < bitLength; i += 8) {
        std::string byteString = bitString.substr(i, 8);
        while (byteString.size() < 8) {
            byteString.push_back('0');
        }
        std::bitset<8> bits(byteString);
        byteArray.push_back(static_cast<uint8_t>(bits.to_ulong()));
    }
    return byteArray;
}

// Reads input file and returns its content as a string
string readInputFile(const string& input_filename) {
    ifstream input_file(input_filename);
    if (!input_file) {
        throw runtime_error("Error opening input file");
    }
    string inputfile((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
    input_file.close();
    return inputfile;
}

// Calculates the frequency of each character in the input string
vector<int> calculateFrequencies(const string& inputfile) {
    vector<int> frequency_array(128, 0);
    for (char c : inputfile) {
        frequency_array[c - '\0']++;
    }
    return frequency_array;
}

// Builds the Huffman tree from the frequency array
BinaryTreeNode* buildHuffmanTree(const vector<int>& frequency_array) {
    priority_queue<BinaryTreeNode*, vector<BinaryTreeNode*>, comp> min_pq;
    for (int i = 0; i < 128; i++) {
        if (frequency_array[i] > 0) {
            min_pq.push(new BinaryTreeNode(i + '\0', frequency_array[i]));
        }
    }
    while (min_pq.size() > 1) {
        BinaryTreeNode* childnode1 = min_pq.top();
        min_pq.pop();
        BinaryTreeNode* childnode2 = min_pq.top();
        min_pq.pop();
        BinaryTreeNode* parentnode = new BinaryTreeNode('\0', childnode1->getfrequency() + childnode2->getfrequency());
        parentnode->left = childnode1;
        parentnode->right = childnode2;
        min_pq.push(parentnode);
    }
    return min_pq.top();
}


// Writes the compressed data and Huffman tree to the output file
void writeCompressedFile(const string& output_filename, const string& compressed_string, BinaryTreeNode* root) {
    ofstream outfile(output_filename, ios::binary);
    if (!outfile) {
        throw runtime_error("Error opening output file for writing");
    }

    int original_bit_length = compressed_string.length();
    outfile.write(reinterpret_cast<const char*>(&original_bit_length), sizeof(original_bit_length));
    serializeTree(root, outfile);
    vector<uint8_t> final_compressed_bitstring = convertToByteArray(compressed_string);
    for (uint8_t byte : final_compressed_bitstring) {
        outfile.put(byte);
    }
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

        string inputfile = readInputFile(input_filename);
        vector<int> frequency_array = calculateFrequencies(inputfile);
        BinaryTreeNode* root = buildHuffmanTree(frequency_array);

        unordered_map<char, string> character_codes;
        string temp;
        assigncodes(root, temp, character_codes);

        string compressed_string;
        for (char c : inputfile) {
            compressed_string.append(character_codes[c]);
        }

        writeCompressedFile(output_filename, compressed_string, root);
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
