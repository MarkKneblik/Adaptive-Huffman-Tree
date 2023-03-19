#pragma once
#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

class node {
public:
	node* parent;
	node* prev;
	node* next;
	node* left;
	node* right;
	int count;
	char character;

	node() { //default constructor has 0 as count and no character
		this->parent = NULL;
		this->prev = NULL;
		this->next = NULL;
		this->left = NULL;
		this->right = NULL;
		this->character = NULL;
		this->count = 0;
	}

	node(char c) { //constructor that takes in c and assigns it to the character of the node
		this->parent = NULL;
		this->prev = NULL;
		this->next = NULL;
		this->left = NULL;
		this->right = NULL;
		this->character = c;
		this->count = 0;
	}
};

class adaptiveHuffman : public node {
public:
	node* root; //holds root of huffman tree
	node* nodes[256]; //array holds pointers to character nodes, indexed by their numeric ascii value
	string alphabet; //holds alphabet of message to be encoded/decoded

	adaptiveHuffman(string alpha) {//constructor sets alphabet
		this->alphabet = alpha;
	}

	void balance(node* nd) {
		node* leader_node; //this will hold the leader node
		node* leader_finder; //node that will be used to traverse to find leader node
		node* thread = nd; //thread initialized to character node. this will be used to iteratively balance the 
		node* curr = nd; //this will be used for incrementing parents iteratively in while loop
		int leader_value;

		while (curr->parent != NULL) { //while current node's parent is not NULL
			leader_node = root; //initialize leader node to root for each while loop iteration
			leader_finder = root; //initialize leader finder node to root for each while loop iteration

			if ((thread->parent != NULL) && ((thread->count < thread->next->count) || (thread->count > thread->prev->count))) {
				if (thread->count < thread->next->count) //check sibling property
					leader_value = thread->count; //if sibling property violated, get value of leader
				else if (thread->count > thread->prev->count)
					leader_value = thread->prev->count;

				while (leader_finder != NULL) { //follow thread of tree starting at root while temp != NULL
					if (leader_finder->count == leader_value) { //if current node's count matches leader value
						leader_node = leader_finder; //make current node the leader node
						break; //exit while loop
					}
					else
						leader_finder = leader_finder->next; //if current node is not leader, move to next node
				}

				if (leader_node != thread->parent) { //if leader is not parent
					node* thread_temp;
					node* temp_thread_next = thread->next;//temporary thread nodes for swap
					node* temp_thread_prev = thread->prev;
					node* temp_thread_left = thread->left;
					node* temp_thread_right = thread->right;
					node* temp_thread_parent = thread->parent;

					node* leader_temp;
					node* temp_leader_next = leader_node->next; //temporary leader nodes for swap
					node* temp_leader_prev = leader_node->prev;
					node* temp_leader_left = leader_node->left;
					node* temp_leader_right = leader_node->right;
					node* temp_leader_parent = leader_node->parent;

					if (leader_node == thread) { //if leader is sibling
						thread = thread->next;

						temp_thread_next = thread->next;//temporary thread nodes for swap
						temp_thread_prev = thread->prev;
						temp_thread_left = thread->left;
						temp_thread_right = thread->right;
						temp_thread_parent = thread->parent;

						temp_leader_next = leader_node->next; //temporary leader nodes for swap
						temp_leader_prev = leader_node->prev;
						temp_leader_left = leader_node->left;
						temp_leader_right = leader_node->right;
						temp_leader_parent = leader_node->parent;

						leader_temp = leader_node;  //
						leader_node = thread;		//	swap nodes				
						thread = leader_temp;		//

						leader_node->next = thread;						//
						leader_node->prev = temp_leader_prev;			//
						leader_node->parent = temp_leader_parent;		//
						leader_node->prev->next = leader_node;			//
						leader_node->next->prev = leader_node;			//
																		// update links
						thread->next = temp_thread_next;				//
						thread->prev = leader_node;						//
						thread->parent = temp_thread_parent;			//
						thread->prev->next = thread;					//
						thread->next->prev = thread;					//

						thread->parent->left = thread;			//update parent's right and left children
						thread->parent->right = leader_node;	//

						curr = leader_node;
						curr->parent->count = curr->parent->count + 1; //increment parent count
						curr = curr->parent; //move to next parent

						if ((curr->parent != NULL) && (thread->prev != thread->parent)) //if thread's parent's left is thread
							thread = thread->prev; //move thread to right child for sibling property evaluation
					}
					else { //if leader is not sibling
						if (thread == thread->parent->right) { //this case is for swapping a right child
							if (thread->next->count > thread->count)
								thread = thread->next;

							temp_thread_next = thread->next;
							temp_thread_prev = thread->prev;
							temp_thread_parent = thread->parent;

							if (leader_node->next == thread) {
								temp_leader_next = leader_node;
								temp_thread_prev = thread;
							}
								
							thread_temp = thread;
							leader_temp = leader_node;  //
							leader_node = thread;		//	swap nodes				
							thread = leader_temp;		//

							leader_node->next = temp_leader_next;			//
							leader_node->prev = temp_leader_prev;			//
							leader_node->parent = temp_leader_parent;		//
							leader_node->prev->next = leader_node;			//
							leader_node->next->prev = leader_node;			//
																			// update links
							thread->next = temp_thread_next;				//
							thread->prev = temp_thread_prev;				//
							thread->parent = temp_thread_parent;			//
							thread->prev->next = thread;					//
							thread->next->prev = thread;					//

							if (temp_leader_parent->right == leader_temp)
								leader_node->parent->right = leader_node;
							else
								leader_node->parent->left = leader_node;
							if (temp_thread_parent->right == thread_temp)
								thread->parent->right = thread;
							else
								thread->parent->left = thread;

							curr = leader_node;
							curr->parent->count = curr->parent->count + 1; //increment parent count
							curr = curr->parent; //move to next parent
							thread = curr;

							if ((curr->parent != NULL) && (thread == thread->parent->left)) //if thread is a left child
								thread = thread->prev; //move thread to right child for sibling property evaluation
						}
						else { //case for swapping left child
							if (thread->parent->left != thread)
								thread = thread->next; //move thread to left child

							temp_thread_next = thread->next;//temporary thread nodes for swap
							temp_thread_prev = thread->prev;
							temp_thread_left = thread->left;
							temp_thread_right = thread->right;
							temp_thread_parent = thread->parent;

							temp_leader_next = leader_node->next; //temporary leader nodes for swap
							temp_leader_prev = leader_node->prev;
							temp_leader_left = leader_node->left;
							temp_leader_right = leader_node->right;
							temp_leader_parent = leader_node->parent;

							leader_temp = leader_node;  //
							leader_node = thread;		//	swap nodes				
							thread = leader_temp;		//

							leader_node->next = temp_leader_next;			//
							leader_node->prev = temp_leader_prev;			//
							leader_node->parent = temp_leader_parent;		//
							leader_node->prev->next = leader_node;			//
							leader_node->next->prev = leader_node;			//
																			// update links
							thread->next = temp_thread_next;				//
							thread->prev = temp_thread_prev;				//
							thread->parent = temp_thread_parent;			//
							thread->prev->next = thread;					//
							thread->next->prev = thread;					//

							if (temp_leader_parent->right == leader_temp)
								leader_node->parent->right = leader_node;
							else
								leader_node->parent->left = leader_node;
							thread->parent->left = thread;

							curr = leader_node;
							curr->parent->count = curr->parent->count + 1; //increment parent count
							curr = curr->parent; //move to next parent
							thread = curr;
							//update new thread for sibling property check

							if ((curr->parent != NULL) && (thread->prev != thread->parent)) //if thread's parent's left is thread
								thread = thread->prev; //move thread to right child for sibling property evaluation
							if (thread->parent->left == thread)
								thread = thread->prev;
						}
					}
				}
				else { //leader is parent
					curr->parent->count = curr->parent->count + 1; //increment parent count
					curr = curr->parent; //move to next parent
					thread = curr; //update new thread for sibling property check
					if ((curr->parent != NULL) && (thread->prev != thread->parent)) //if thread's parent's left is thread
						thread = thread->prev; //move thread to right child for sibling property evaluation
					if ((thread->parent != NULL) && (thread->parent->left == thread))
						thread = thread->prev;
				}
			} //if sibling property violated brace
			else { //if sibling property not violated
				curr->parent->count = curr->parent->count + 1; //increment parent count
				curr = curr->parent; //move to next parent
				thread = curr; //update new thread for sibling property check
				if ((curr->parent != NULL) && (thread->parent->left == thread)) //if thread's parent's left is thread
					thread = thread->prev; //move thread to right child for sibling property evaluation
			}
		} //end while loop
	}

	string encode(string msg) {
		string encoded_msg; //holds encoded message
		node* zero_node = new node(); //create zero node
		root = zero_node; //make zero node the root

		for (int i = 0; i < 256; i++) {
			nodes[i] = zero_node; //initialize every index in array to point to the zero node
		}

		try {
			for (int i = 0; i < msg.length(); i++) { //iterate over each character of message
				int ct = 0;
				for (int j = 0; j < alphabet.length(); j++) { //iterate over each character in alphabet
					if (msg[i] == alphabet[j])
						ct++; //if symbol at index i in message == symbol at index j of alphabet, increment count
				}
				if (ct == 0)
					throw ct; //if symbol at index i in message is not the same as any symbols in alphabet, throw count
			}

			for (int i = 0; i < msg.length(); i++) { //iterate over every character in message
				int x = msg[i]; //x will be index of character node

				if (nodes[x] == zero_node) { //if msg[i] character does not have a node in the tree	
					node* character_node = new node(msg[i]); //create new node with symbol at current index as its character
					node* path_finder = zero_node; //path finder is used to find path from root to zero node
					nodes[x] = character_node; //assign index to character node
					character_node->count = 1; //set character node's count to 1

					node* parent_node = new node(); //new parent of zero node and character node
					//parent_node->count = 1; //set parent node's count to 1

					node* temp = zero_node; //temp holds zero node

					if (root != parent_node) { //if root is not parent node then it has a path to the character node
						string path, reversed_path;

						while (path_finder->parent != NULL) {
							if (path_finder->parent->right == path_finder) //if path finder is a right child
								path = path + "1"; //append 1 to path
							else if (path_finder->parent->left == path_finder)
								path = path + "0"; //else it is a left child, append 0 to path
							path_finder = path_finder->parent; //move up the tree
						}
						for (int i = path.length() - 1; i >= 0; i--) { //iterate over path
							reversed_path = reversed_path + path[i]; //reverse string by iterating backwards and appending to reversed path
						}
						encoded_msg = encoded_msg + reversed_path; //after reversing path string, append to encoded message
					}

					parent_node->prev = temp->prev; //parent node's prev will be zero node's prev
					parent_node->parent = temp->parent; //parent node's parent will be zero node's parent
					parent_node->next = character_node; //make parent node's next its the character leaf node
					parent_node->left = temp; //make zero node the left child of new parent node
					parent_node->right = character_node; //	make right child of parent node the character leaf node
					if (parent_node->parent != NULL)
						parent_node->parent->left = parent_node;

					if (parent_node->prev != NULL)
						parent_node->prev->next = parent_node; //update thread
					if (root == zero_node) //if root is zero node
						root = parent_node; //make new parent node the root

					character_node->next = temp; //make character node's next the zero node
					character_node->prev = parent_node; //make character node's prev the parent node
					character_node->parent = parent_node; //make character node's parent the parent node

					zero_node->prev = character_node; //make prev of zero node the node with msg[i] as its character
					zero_node->parent = parent_node; //make parent node parent of zero node

					nodes[x] = character_node; //set index of character node in array

					bitset<8> binary(x); //get 8 bit representation of ascii value
					string bin = binary.to_string(); //convert 8 bit representation to a string

					encoded_msg = encoded_msg + bin; //append 8 bit value of character that was inserted into the tree to encoded message

					balance(character_node); //balance tree

				} //end if not in tree

				else { //the character msg[i] is in the tree
					node* character_node = nodes[x]; //set character leaf node to node within tree that has numeric ascii value of x
					node* leader_node; //this will hold the leader node
					node* leader_finder; //node that will be used to traverse to find leader node
					node* thread = character_node; //thread initialized to character node. this will be used to iteratively balance the tree upward
					node* curr = character_node; //this will be used for incrementing parents iteratively in while loop
					node* path_finder = character_node;
					int leader_value; //holds value of leader when balancing

					character_node->count = character_node->count + 1; //increment count of character node

					string path, reversed_path;

					while (path_finder->parent != NULL) { //move up tree until parent is null
						if (path_finder->parent->right == path_finder) //if path finder is a right child
							path = path + "1"; //append 1 to path
						else if (path_finder->parent->left == path_finder)
							path = path + "0"; //else it is a left child, append 0 to path
						path_finder = path_finder->parent; //move up tree
					}
					for (int i = path.length() - 1; i >= 0; i--) {
						reversed_path = reversed_path + path[i]; //reverse string by placing character at index i in index j
					}
					encoded_msg = encoded_msg + reversed_path; //after reversing path string, append to encoded message

					balance(character_node); //balance tree
				}	//end of else msg[i] is in tree 
			}
		}
		catch (int ct) {
			cout << "Message contains a symbol not contained in the alphabet." << endl;
			exit(1);
		}
		return encoded_msg;
	}

	string decode(string msg) {
		string decoded_msg, first_character;
		char converted_character; //holds actual char that we get from converting from 8 bits of string first_character
		const int EIGHT_BIT_CHARACTER = 8; //the first 8 bits of the message are guaranteed to be a character

		//clearHuffmanTree(root); //delete the Huffman tree so we can start anew

		node* zero_node = new node(); //create zero node
		root = zero_node; //make zero node the root

		for (int i = 0; i < EIGHT_BIT_CHARACTER; i++) {
			first_character = first_character + msg[i]; //make string for first 8 bits of the encoded message
		}

		int exponent = 0; //will be used to find the integer ascii value
		int ascii_value = 0; //ascii value starts at 0 before adding to it
		for (int i = first_character.length() - 1; i >= 0; i--) { //iterate backwards over 8 bit character
			if (first_character[i] == '1') //if given index in first_character is a 1
				ascii_value = ascii_value + pow(2, exponent); //add exponential value at current index to ascii value
			exponent++; //increment the exponent as we move left
		}
		converted_character = ascii_value; //the converted 8 bit character will be of given ascii value

		decoded_msg = decoded_msg + converted_character; //append character to decoded message

		node* character_node = new node(converted_character); //create new node with symbol at current index as its character
		character_node->count = 1; //set character node's count to 1

		node* parent_node = new node(); //new parent of zero node and character node
		//parent_node->count = 1; //set parent node's count to 1

		node* temp = zero_node; //temp holds zero node

		parent_node->prev = temp->prev; //parent node's prev will be zero node's prev
		parent_node->parent = temp->parent; //parent node's parent will be zero node's parent
		parent_node->next = character_node; //make parent node's next its the character leaf node
		parent_node->left = temp; //make zero node the left child of new parent node
		parent_node->right = character_node; //	make right child of parent node the character leaf node
		parent_node->count = parent_node->count + 1;

		if (parent_node->parent != NULL)
			parent_node->parent->left = parent_node; //set new parent as its new parent's left
		if (parent_node->prev != NULL)
			parent_node->prev->next = parent_node; //update thread
		if (root == zero_node) //if root is zero node
			root = parent_node; //make new parent node the root

		character_node->next = temp; //make character node's next the zero node
		character_node->prev = parent_node; //make character node's prev the parent node
		character_node->parent = parent_node; //make character node's parent the parent node

		zero_node->prev = character_node; //make prev of zero node the node with msg[i] as its character
		zero_node->parent = parent_node; //make parent node parent of zero node

		nodes[ascii_value] = character_node; //assign index to character node

		int j = 8;
		for (int i = 8; i < msg.length() - 1; i = j) {
			node* node_finder = root;

			while ((node_finder->left != NULL) && (node_finder->right != NULL)) { //while node finder is not leaf node
				if (msg[j] == '0') {
					node_finder = node_finder->left; //if current character is 0, traverse to the left child
					j++;
				}
				else if (msg[j] == '1') {
					node_finder = node_finder->right; //else if current character is 1, traverse to the right child
					j++;
				}
			}

			if (node_finder != zero_node) { //if leaf node is not zero node (character is in tree)
				decoded_msg = decoded_msg + node_finder->character; //append character to decoded message
				node_finder->count = node_finder->count + 1;

				node* leader_node; //this will hold the leader node
				node* leader_finder; //node that will be used to traverse to find leader node
				node* thread = node_finder; //thread initialized to character node. this will be used to iteratively balance the tree upward
				node* curr = node_finder; //this will be used for incrementing parents iteratively in while loop
				int leader_value; //holds value of leader when balancing

				balance(node_finder);
			}
			else { //else character is not in tree
				int eight_bit = j;
				string character;
				char converted_character;

				for (j; j < eight_bit + 8; j++) { //we need to get string of 8 bits starting at j
					character = character + msg[j]; //append in order to form 8 bit string
				}

				int exponent = 0; //will be used to find the integer ascii value
				int ascii_value = 0; //ascii value starts at 0 before adding to it
				for (int i = character.length() - 1; i >= 0; i--) { //iterate backwards over 8 bit character
					if (character[i] == '1') //if given index in first_character is a 1
						ascii_value = ascii_value + pow(2, exponent); //add exponential value at current index to ascii value
					exponent++; //increment the exponent as we move left
				}
				converted_character = ascii_value; //convert integer ascii value to ascii character
				decoded_msg = decoded_msg + converted_character; //append character to decoded message

				node* node_finder = new node(converted_character); //create new node with symbol at current index as its character
				node* path_finder = zero_node; //path finder is used to find path from root to zero node
				node_finder->count = 1; //set character node's count to 1

				node* parent_node = new node(); //new parent of zero node and character node
				//parent_node->count = 1; //set parent node's count to 1

				node* temp = zero_node; //temp holds zero node

				parent_node->prev = temp->prev; //parent node's prev will be zero node's prev
				parent_node->parent = temp->parent; //parent node's parent will be zero node's parent
				parent_node->next = node_finder; //make parent node's next its the character leaf node
				parent_node->left = temp; //make zero node the left child of new parent node
				parent_node->right = node_finder; //	make right child of parent node the character leaf node

				if (parent_node->parent != NULL)
					parent_node->parent->left = parent_node;

				if (parent_node->prev != NULL)
					parent_node->prev->next = parent_node; //update thread

				node_finder->next = temp; //make character node's next the zero node
				node_finder->prev = parent_node; //make character node's prev the parent node
				node_finder->parent = parent_node; //make character node's parent the parent node

				zero_node->prev = node_finder; //make prev of zero node the node with msg[i] as its character
				zero_node->parent = parent_node; //make parent node parent of zero node

				node* leader_node; //this will hold the leader node
				node* leader_finder; //node that will be used to traverse to find leader node
				node* thread = node_finder; //thread initialized to character node. this will be used to iteratively balance the tree upward
				node* curr = node_finder; //this will be used for incrementing parents iteratively in while loop
				int leader_value; //holds value of leader when balancing

				balance(node_finder); //balance tree
			} //end else character is not in tree
		} //end for loop for message	

		try {
			for (int i = 0; i < decoded_msg.length(); i++) { //iterate over each character of message
				int ct = 0;
				for (int j = 0; j < alphabet.length(); j++) { //iterate over each character in alphabet
					if (decoded_msg[i] == alphabet[j])
						ct++; //if symbol at index i in message == symbol at index j of alphabet, increment count
				}
				if (ct == 0)
					throw ct; //if symbol at index i in message is not the same as any symbols in alphabet, throw count
			}
		}
		catch (int ct) {
			cout << "Message contains a symbol not contained in the alphabet." << endl;
			exit(1);
		}
		return decoded_msg;
	}
};
