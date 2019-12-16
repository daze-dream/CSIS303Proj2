#pragma once
#include <string>
#include <iostream>

using namespace std;
class TreeNode
{
public:
	TreeNode();
	TreeNode(char l, string code, TreeNode *left = NULL, TreeNode *right = NULL);
	TreeNode* left = NULL;
	TreeNode* right = NULL;
	void setData(char l, string c) { this->letter = l; this->code = c; };
	char getLetter() { return letter; };
	~TreeNode();
private:
	char letter = ' ';
	string code;
};