# Algorithmic-Text-File-Compressor
This project implements a Huffman coding-based file compression and decompression tool using C++. Huffman coding is a popular algorithm for lossless data compression. This repository contains the source code, example input and output files, and documentation on how to use the tool.

## Features
- Compression: Compresses a given text file using Huffman coding.
- Decompression: Decompresses a previously compressed file back to its original text form.
- Custom Huffman Tree: Builds a Huffman tree based on the frequency of characters in the input file.
- Serialization: Serializes and deserializes the Huffman tree for efficient storage and retrieval.
- Binary Conversion: Converts the compressed bit string into a byte array for compact storage.
## Files
- compressor.cpp: Contains the code to read the input file, build the Huffman tree, compress the data, and write the compressed output to a file.
- decompressor.cpp: Contains the code to read the compressed file, deserialize the Huffman tree, decompress the data, and write the decompressed output to a file.
- BinaryTreeNode.h: Header file defining the BinaryTreeNode class used in the Huffman tree.
- documentation.md: Contains detailed explanation and working of each function used in the code.
## Usage
### Prerequisites
- A C++ compiler (e.g., g++, clang++)
- Standard C++ library
### How to run this:
#### Compilation
- To compile the source code, run the following commands in your terminal:<br/>
g++ -o compressor compressor.cpp<br/>
g++ -o decompressor decompressor.cpp<br/>

#### Running the Compressor:
- To compress a file, use the following command:<br/>
./compressor < inputfile > < compressedfile >

- Eg: ./compressor input.txt compressed.bin<br/>

#### Running the Decompressor:
To decompress a file, use the following command:<br/>
.\decompressor.exe < compressedfile > < outputfile > 

- Eg: .\decompressor.exe compressed.bin output.txt <br/>

## Example files
- input: Contains sample text data for compression.
- output: Contains decompressed text data.
- compressed: Contains compressed binary data.

## Screenshots
- The screenshots- input properties, compressed properties and output properties have been provided for presenting the degree of compression that takes place.
## Result
- Around 45-50 % of compression is achieved even for text files as large as 180-190 MB without the loss of any data.
- Note: As '#' and '$' characters have been used as placeholders, the code works perfectly when these characters are not present in the input text file.

  
