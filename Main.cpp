#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include "TreeNode.h"


using namespace std;

void encode(string input, map<char, string> legend);
void decode(queue<char> &q, TreeNode *n);
void decodeHelper(string code, TreeNode *node);
void addNode(queue<char> &q, char letter, string code, TreeNode *n);

int main()
{
	map<char, string> legend;
	queue<char> daQ;
	ifstream input;
	TreeNode root;
	root.setData(' ', " ");

	input.open("morse.txt");

	while (!input.eof())
	{
		char letter;
		string code;

		input >> letter >> code;
		legend.insert(pair<char, string>(letter, code));
		for (auto x = code.begin(); x != code.end(); ++x)
		{
			daQ.push(*x);
		}

		addNode(daQ, letter, code, &root);

	}

	//cout << root.left->left->right->getLetter();
	/*encode("configuration", legend);
	cout << endl;
	decodeHelper("-.-. --- -. ..-. .. --. ..- .-. .- - .. --- -.", &root);
	cout << endl;*/

	char choice;
	string userText;
	
	cout << "Please select one of the following options" << endl;
	cout << "  1. Encode into morse" << endl;
	cout << "  2. Decode existing morse" << endl;
	cout << "  3. Quit the program" << endl;
	cout << "Select now: ";
	cin >> choice;
	cin.clear();
	while (choice != '3')
	{
		if (choice == '1')
		{
			cout << "Enter message to encode" << endl;
			cin >> userText;
			encode(userText, legend);
			cout << endl << endl;
		}
		if (choice == '2')
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Enter morse to decode \n" << endl;
			getline(cin, userText);
			decodeHelper(userText, &root);
			cout << endl << endl;

		}
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

void encode(string input, map<char, string> legend)
{
	for (string::iterator x = input.begin(); x != input.end(); ++x)
	{
		cout << legend.at(*x);
		cout << " ";
	}
}

void decodeHelper(string code, TreeNode *node)
{
	queue<char> q;
	for (auto x = code.begin(); x != code.end(); ++x)
	{
		if (*x == ' ')
		{
			decode(q, node);
		}
		else
		{
			q.push(*x);
		}
	}
	decode(q, node);
}

void decode(queue<char> &q, TreeNode *n)
{
	if (q.empty())
	{
		cout << n->getLetter();
	}
	else if (q.front() == '.')
	{
		q.pop();
		decode(q, n->left);
	}
	else if (q.front() == '_' || q.front() == '-')
	{
		q.pop();
		decode(q, n->right);
	}
}

void addNode(queue<char> &q, char letter, string code, TreeNode *n)
{
	if (q.empty())
	{
		n->setData(letter, code);
	}
	else if (q.front() == '.')
	{
		q.pop();
		if(n->left == NULL)
			n->left = new TreeNode;
		addNode(q, letter, code, n->left);
	}
	else if (q.front() == '_' || q.front() == '-')
	{
		q.pop();
		if(n->right == NULL)
			n->right = new TreeNode;
		addNode(q, letter, code, n->right);
	}
}