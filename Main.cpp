// Program to encode and decode Morse code.
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include "TreeNode.h"


using namespace std;

// Encodes a word into Morse code. Uses a mapping for convenience
void encode(string input, map<char, string> legend);
// The decode function proper. Turns Morse into letters. Uses a queue.
void decode(queue<char> &q, TreeNode *n);
// Helper function for decoding. Creates a queue of processed chars then passes to decode.
void decodeHelper(string code, TreeNode *node);
// External program to add a node to the tree. Used because class-based one was annoying.
void addNode(queue<char> &q, char letter, string code, TreeNode *n);

int main()
{
	map<char, string> legend;		// mapping for Morse after building tree
	queue<char> daQ;				// queue for encoding, decoding, etc. STL.
	ifstream input;					// file input from morse.txt to build tree
	TreeNode root;					// empty node for root of tree, mirroring assingment
	root.setData(' ', " ");			// just in case, initializes the node with blank stuff.

	input.open("morse.txt");

	// Begin processing file
	while (!input.eof())
	{
		char letter;				// stores letter
		string code;				// stores corresponding code

		input >> letter >> code;
		legend.insert(pair<char, string>(letter, code));	// builds the map as we go
		for (auto x = code.begin(); x != code.end(); ++x)	
		{
			// pushes chars into a queue until end of string
			daQ.push(*x);
		}

		// At the end of the string, pass to addNode to determine its place in the tree
		addNode(daQ, letter, code, &root);

	}
	
	// This was debugging outputs before user input. Legacy

	//cout << root.left->left->right->getLetter();
	/*encode("configuration", legend);
	cout << endl;
	decodeHelper("-.-. --- -. ..-. .. --. ..- .-. .- - .. --- -.", &root);
	cout << endl;*/

	char choice;				// stores user input for commands
	string userText;			// stores their entered string, morse or word
	
	cout << "Please select one of the following options" << endl;
	cout << "  1. Encode into morse" << endl;
	cout << "  2. Decode existing morse" << endl;
	cout << "  3. Quit the program" << endl;
	cout << "Select now: ";
	cin >> choice;
	cin.clear(); // Clear the cin stream / buffer just in case

	// input loop
	while (choice != '3')
	{
		if (choice == '1')
		{
			cout << "Enter a word to encode" << endl;
			cin >> userText; // cin used because it's a simple one word. No spaces.
			encode(userText, legend);
			cout << endl << endl;
		}
		if (choice == '2')
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears input stream
			cout << "Enter morse to decode \n" << endl;
			getline(cin, userText); // getline used to account spaces
			decodeHelper(userText, &root);
			cout << endl << endl;

		} // Error checking
		if (choice != '1' && choice != '2' && choice != '3')
			cout << "No command corresponding to that input. ";
		cout << "Please select one of the following options" << endl;
		cout << "  1. Encode into morse" << endl;
		cout << "  2. Decode existing morse" << endl;
		cout << "  3. Quit the program" << endl;
		cin >> choice;
		
	}
	system("pause");
	return 0;
}

// Encodes a word. Quite simple. Takes a string and iterates through it, outputting
// from a map. A space is output after each code.
void encode(string input, map<char, string> legend)
{
	for (string::iterator x = input.begin(); x != input.end(); ++x)
	{
		cout << legend.at(*x);
		cout << " ";
	}
}

/*This is the helper function for decoding called in main. It takes the string 
	and the root node from main. It then starts to process the string, pushing it
	into a queue. Queue is used for its FIFO capabilities. When it encounters 
	a space, it processes the current queue by passing it to decode proper.
	In essence, it processes each Morse code letter as it encounters it.*/
void decodeHelper(string code, TreeNode *node)
{
	queue<char> q;
	for (auto x = code.begin(); x != code.end(); ++x)
	{
		if (*x == ' ')
		{
			// process the letter, as the space indicates that it's done.
			decode(q, node);
		}
		else
		{
			// if not, that means there's still stuff to process. Push more stuff.
			q.push(*x);
		}
	}
	// At the end, that means that it's the end of the string. Decode the last letter.
	decode(q, node);
}
  /*Decode proper. Takes the queue from Helper function and the root node. 
		Recursive.
		Takes the queue and decides where to go depending on '.' or "_" or "-".
		Built to handle both sorts of dashes because some places did it different.
		When the queue is empty, that's when it has ended up in the right node, and
			it is outputted.
		Kind of unique because we don't look for the subtrees or anything. Each new node
		generates new nodes.*/
void decode(queue<char> &q, TreeNode *n)
{
	if (q.empty())
	{
		// End of queue aka right place. Output node data.
		cout << n->getLetter();
	}
	else if (q.front() == '.')
	{
		// '.' means go to left. Pop queue and pass it to decode again.
		q.pop();
		decode(q, n->left);
	}
	else if (q.front() == '_' || q.front() == '-')
	{
		// Either dash is fine Pop queue and pass to decode with right.
		q.pop();
		decode(q, n->right);
	}
}
 /*External function to add new node to the tree.
	Recursive Externalized because I felt
	dealing with the class-specific one was weird and confusing, as much as
	encapsulation and security are good. Takes the queue,  the letter and code from
	the text file, and the root node of the tree. Similar to decode, we take the queue
	and use it to traverse the tree, popping at each turn. When the queue is empty,
	we know we're in the right place, so we modify the data of that node. 
	Checks if each of its child nodes are null or not, then allocates memory to avoid
	unnecessary stuff. Essentially we're generating nodes as we go along.
	One MAJOR issue was not using the NULL method, as it was infinitely assigning memory
	to nodes because each generation of a node allocated memory themselves for new nodes.*/
void addNode(queue<char> &q, char letter, string code, TreeNode *n)
{
	if (q.empty())
	{
		// End of queue, modify data
		n->setData(letter, code);
	}
	else if (q.front() == '.')
	{
		// If there is no data, construct a new node and then recursively call based on direction
		q.pop();
		if(n->left == NULL)
			n->left = new TreeNode;
		addNode(q, letter, code, n->left);
	}
	else if (q.front() == '_' || q.front() == '-')
	{
		// If there is no data, construct a new node and then recursively call based on direction
		q.pop();
		if(n->right == NULL)
			n->right = new TreeNode;
		addNode(q, letter, code, n->right);
	}
}