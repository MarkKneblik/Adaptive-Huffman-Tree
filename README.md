# Adaptive Huffman Tree Encoder/Decoder

## General info
* command line program that implements a Huffman Tree to encode/decode a message
* encodes a .txt file, producing a string of 0's and 1's in a new .txt file
* after encoding, is able to decode the new .txt file containing 0's and 1's, producing the original message

## Setup
* download the adaptivehuffman.h header file and the driver.cpp file
* compile with your choice of C++ compiler
* create a .txt file in the same directory that will hold the alphabet that the program will use to encode/decode. Do not enter duplicate characters
* create a .txt file in the same directory that will hold the mssage that the program will encode

## How to use
* to encode the message, enter arguments in this format: **./driver.exe encode [name of alphabet file] [name of message file]**
* to decode the message, enter arguments in this format: **./driver.exe decode [name of alphabet file] [name of message file with ".encoded.txt" appended to it]**

## Notes
* This program works for messages containing alphanumeric characters and characters such as 'space' and 'tab' but does not work for messages containing newline characters
