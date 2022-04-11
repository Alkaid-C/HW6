#ifndef REDBLACKTREE
#define REDBLACKTREE

#define Black 0
#define Red 1

#include<vector>
#include<string>

using namespace std;

struct Node
{
	unsigned long long int value = 0;
	short color = Black;
	Node* Parent = nullptr;
	Node* Left = nullptr;
	Node* Right = nullptr;
};

class RedBlackTree
{
private:
	Node* root = nullptr;
	unsigned long long int numItems = 0;
	vector<Node*> DebugVector;
	Node* treeCopyer(Node* OldRoot, Node* newParent);
	bool exist(unsigned long long int value, Node* theRoot);
	Node* find(unsigned long long int value, Node* theRoot);
	void bst_insert(Node* theNode, Node* theRoot);
	void insert_balancer(Node* theNode);
	void RBT_deleter(Node* theRoot);
	void left_rotater(Node* theNode);
	void right_rotater(Node* theNode);
	void recolorator(Node* theNode);
	unsigned long long int GetMin(Node* theRoot);
	unsigned long long int GetMax(Node* theRoot);
	size_t Size(Node* theRoot);
	void printer(Node* theRoot);
	void NodePrinter(Node* theNode);
	string ToInfixString(Node* theRoot) const;
	string ToPrefixString(Node* theRoot) const;
	string ToPostfixString(Node* theRoot) const;
public:
	RedBlackTree();
	RedBlackTree(const RedBlackTree&);
	//~RedBlackTree();
	bool exist(unsigned long long int value);
	bool Contains(unsigned long long int value);
	Node* find(unsigned long long int value);
	Node* Insert(unsigned long long int value);
	unsigned long long int GetMin();
	unsigned long long int GetMax();
	size_t Size();
	void printer();
	void DebugPrinter(); 
	string ToInfixString() const { return ToInfixString(root); };
	string ToPrefixString() const { return ToPrefixString(root); };
	string ToPostfixString() const { return ToPostfixString(root); };
}
#endif
;
