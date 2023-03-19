#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "adaptivehuffman.h"
using namespace std;
const int VALID_ARG_COUNT = 4;

int main(int argc, char* argv[]) {

	try {
		if (argc == VALID_ARG_COUNT) {
			string arg1, arg2, arg3;
			arg1 = argv[1]; //
			arg2 = argv[2]; //convert arguments to strings
			arg3 = argv[3]; //

			if (arg1 == "encode") { //if user asks to encode
				ifstream alphabet_file, msg_file;
				ofstream encoded_file;
				string alpha, msg, encoded_msg, alphabet_file_name, msg_file_name;
				stringstream buf; //buffer object

				alphabet_file_name = arg2;
				msg_file_name = arg3;

				alphabet_file.open(alphabet_file_name); //open alphabet file
				if (!alphabet_file)
					cout << "Alphabet file did not open." << endl;
				getline(alphabet_file, alpha); //get alphabet string from one line

				msg_file.open(msg_file_name); //open message file
				if (!msg_file)
					cout << "Message file did not open." << endl;

				adaptiveHuffman huffman(alpha); //pass alphabet into huffman object
				buf << msg_file.rdbuf(); //read buffer
				msg = buf.str(); //convert buffer to string
				encoded_msg = huffman.encode(msg); //assign encode return value to encoded_msg
				encoded_file.open(msg_file_name + ".encoded.txt"); //append .encode extension
				encoded_file << encoded_msg;

				alphabet_file.close();
				msg_file.close();
				encoded_file.close();

			}
			else if (arg1 == "decode") {
				ifstream alphabet_file, msg_file;
				ofstream decoded_file;
				string alpha, msg, decoded_msg, alphabet_file_name, msg_file_name;
				stringstream buf; //buffer object

				alphabet_file_name = arg2;
				msg_file_name = arg3;

				alphabet_file.open(alphabet_file_name); //open alphabet file
				if (!alphabet_file)
					cout << "Alphabet file did not open." << endl;
				getline(alphabet_file, alpha); //get alphabet string from one line

				msg_file.open(msg_file_name); //open message file
				if (!msg_file)
					cout << "Message file did not open." << endl;

				adaptiveHuffman huffman(alpha); //pass alphabet into huffman object
				buf << msg_file.rdbuf(); //read buffer
				msg = buf.str(); //convert buffer to string
				decoded_msg = huffman.decode(msg); //assign encode return value to encoded_msg
				decoded_file.open(msg_file_name + ".decoded.txt"); //append .encode extension
				decoded_file << decoded_msg;

				alphabet_file.close();
				msg_file.close();
				decoded_file.close();
			}
		}
		else
			throw argc;
	}
	catch (int argc) {
		cout << "Invalid argument count." << endl;
	}
	return 0;
}