# Algorithmic Text File Compressor



## Brief Functionality

- There are two fuctions that can be performed- Compression and Decompression.

- Note: I have included a file named BinaryTreeNode.h which contains the class definition of a Binary Tree Node.

### Compression
- Done by compressor.cpp file.
- Takes in two arguments- the text(.txt) file you want to compress and the name you want to give to the compressed binary(.bin) file.

- *readInputFile* : Reads each character present in the input file using input stream buffer iterators and converts it into a string, and then returns it.Throws an error if the input file does not exist. 

- _calculateFrequencies_: Calculates the frequency of each character in the input file and returns a vector containing the frequencies.

- _buildHuffmanTree_: Builds the Huffman Tree using frequency vector. The following lines give it's brief working:
- Uses a min_priority queue to store the elements of the frequency arrays as Binary Tree Nodes in the non-decreasing order of frequencies.
- Then, it builds a binary tree using Huffman Algorithm and returns the last element present to assign it as the root.
- Uses the null character as a placeholder so as to handle all the characters entered using a keyboard.

- _assigncodes_: Assigns the binary codes to each character depending upon their position in the Huffman Tree. The following lines give it's brief working:
- Traverses to each leaf node( where the characters are present) and assigns a binary string to it. On traversing to the left child, '0' is added to the character code and '1' is added when traversing to the right child.
- The character codes are then stored in an unordered_map passed by reference.

- Then, in the main function, all the character codes of the characters occuring in input file is appended to a string named "compressed_string".

- _writeCompressedFile_ : Creates an output binary file to store the compressed form. Serialises the Huffman Tree to store it and use in Decompressor file. The following lines give it's brief working:
- First, the function opens the output file in binary mode and throws an error if the file can't be opened.
- Stores the original length of the compressed binary string and calls the serializeTree function.
- _serializeTree_: 
- It checks for a null node- marks an '#' to the file and returns. This marks the endd of a branch in the Huffman Tree.
- Then, it checks for placeholder('\0') nodes and marks a '$' to the file to indicate the placeholder node.
- If the node is not a placeholder and null node, it must be a leaf node. Thus, it it writes the character stored in the node to the file.
- It recursively calls itself to serialize the left and right children of the current node, following the same three steps mentioned above.
- Since '$' and '#' symbols are used to serialise and deserealise a Binary Tree, the input text file should not contain these characters.
- _convertToByteArray_: 
- This function converts a string of bits into a vector of bytes (uint8_t).
- _Detailed working_:
- Takes in the binary string(bitstring) as an argument.
- Takes 8 characters substring of the bitstring at a time, converts it to a 8 digit unsigned long number. Then, it converts the unsigned long number to a byte (uint8_t) by typecasting.
- The typecasted bytes are appended and returned as a vector of bytes.
- Zero padding: If the length of the byteString is less than 8 (this happens only for the last chunk if the bit string length is not a multiple of 8), it pads the byteString with '0's to make it 8 bits long.

- By breaking down the bit string into bytes and storing the Huffman tree structure, these functions ensure that the compressed data can be accurately written to a file and later decompressed correctly.

### Decompression
- Done by decompressor.cpp file.
- Takes in two arguments- the compressed binary(.bin) file you want to decompress and the name you want to give to the decompressed  output text(.txt) file.

- _readAndDecompressFile_ : This function reads the compressed file and returns the decompressed string.
- _Detailed Working_: 
- Reads in the input binary file and original bitstring length. If the binary file does not exist, it throws an error.
- _deserializeTree_ :
- Reads in one character at a time.
- If the character is '#', it returns nullptr, indicating the end of a branch.
- If the character is '$', it represents placholder. Therefore, it creates an internal(non leaf and non root) node with it's data as '\0'.
- If the character is neither '#' nor '$', it creates a new leaf node with the read character as its data.
- It recursively calls itself to deserialize the left and right children of the current node.
- It returns the deserialized node which is in fact, the root of the tree itself.
- _readBitString_ : 
- It initializes an empty string 'bitString' and reserves space for 'bitLength' characters.
- It reads each byte from the file one by one.
- For each byte, it converts it to a bitset of 8 bits.
- Then each bit of the bitset is extracted and appended to the bitstring until the length of the bitstring reaches 'bitLength'.
- The constructed bitstring is then returned.
(The test function checks if the bit at a specific position is set (i.e., if it is 1).
7 - i calculates the position of the bit to be checked. Eg: i=0-> 7th bit is checked... i=7->0th bit is checked)
- _decompressString_ :
- It initializes an empty string 'decompressedString' and sets 'currentNode' to the root of the Huffman tree
- For each bit in the bitString:
- If the bit is '0', it moves to the left child of currentNode.
- If the bit is '1', it moves to the right child of currentNode.

- If currentNode is a leaf node (i.e., it has no left or right children):
- It appends the data of currentNode to decompressedString.
- It resets currentNode to the root of the Huffman tree.

- Then, the decompressed string is returned.

- _writeOutputFile_:
- Takes in the name you want to give to the output text(.txt) file as an argument.
- Then, it writes the contents of the decompressed string to the output file.
- Then the output file is closed.

Now, if we compile and run the files using appropriate command line prompts(given in readme file), two files other than the input file are generated- the compressed binary file and the output file.


## Achieved Compression without any loss of data:

| Input and Output File Size    | Compressed File Size |
| -------- | ------- |
| 1,152 KB | 617 KB    |
| 3,454 KB | 1,849 KB    |
| 10,360 KB    | 5,547 KB    |
| 31.079 MB | 16.640 MB    |
| 93.237 MB | 49.919 MB    |
| 186.474 MB    | 99837 MB  |

Note: I assumed 1MB=1000KB for simplicity. Beyond these sizes, the runtime exceeds 30 seconds.





