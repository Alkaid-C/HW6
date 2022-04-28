#include "RedBlackTree-P.h"
#include <iostream>
#include<string>
 

RedBlackTree::RedBlackTree()
{
	root = nullptr;
	numItems++;
}
RedBlackTree::RedBlackTree(const RedBlackTree& theTree)
{
	root = nullptr;
	numItems = theTree.numItems;
	if (theTree.root != nullptr)
	{
		Node* NewNode = new Node;
		NewNode->color = theTree.root->color;
		NewNode->Parent = theTree.root->Parent;
		NewNode->value = theTree.root->value;
		NewNode->Left = treeCopyer(theTree.root->Left, NewNode);
		NewNode->Right = treeCopyer(theTree.root->Right, NewNode);
		root = NewNode;
	}
	
}
Node* RedBlackTree::treeCopyer(Node* OldRoot, Node* newParent)
{
	if (OldRoot == nullptr)
		return nullptr;
	else
	{

		Node* NewNode = new Node;
		NewNode->color = OldRoot->color;
		NewNode->Parent = newParent;
		NewNode->value = OldRoot->value;
		NewNode->Left = treeCopyer(OldRoot->Left, NewNode);
		NewNode->Right = treeCopyer(OldRoot->Right, NewNode);
		return NewNode;
	}
}
RedBlackTree::~RedBlackTree()
{
	RBT_deleter(root);
}
void RedBlackTree::RBT_deleter(Node* theRoot)
{
	if (theRoot != nullptr)
	{
		if (theRoot->Left != nullptr)
			RBT_deleter(theRoot->Left);
		if (theRoot->Right != nullptr)
			RBT_deleter(theRoot->Right);
	}
	delete theRoot;
}
bool RedBlackTree::Contains(unsigned long long int value)
{
	return exist(value);
}
bool RedBlackTree::exist(unsigned long long int value)
{
	return exist(value, root);
}
bool RedBlackTree::exist(unsigned long long int value, Node* theRoot)
{
	if (theRoot == nullptr)
		return false;
	if (theRoot->value == value)
		return true;
	else if (theRoot->value > value)
	{
		if (theRoot->Left == nullptr)
			return false;
		return exist(value, theRoot->Left);
	}
	else
	{
		if (theRoot->Right == nullptr)
			return false;
		return exist(value, theRoot->Right);
	}
}
Node* RedBlackTree::find(unsigned long long int value)
{
	return find(value, root);
}
Node* RedBlackTree::find(unsigned long long int value, Node* theRoot)
{
	if (theRoot->value == value)
		return theRoot;
	else if (theRoot->value > value)
	{
		if (theRoot->Left == nullptr)
			return nullptr;
		return find(value, theRoot->Left);
	}
	else
	{
		if (theRoot->Right == nullptr)
			return nullptr;
		return find(value, theRoot->Right);
	}
}
Node* RedBlackTree::Insert(unsigned long long int value)
{
		numItems++;
		if (root == nullptr)
		{//if it is the first node, make it root
			Node* theNode = new Node;
			theNode->color = Black;
			theNode->value = value;
			root = theNode;
			return theNode;
		}
		else
		{
			Node* theNode = new Node;
			theNode->color = Red;
			theNode->value = value;
			bst_insert(theNode, root);
			insert_balancer(theNode);
			return theNode;
		}
}
void RedBlackTree::bst_insert(Node* theNode, Node* theRoot)
{
	if (theRoot->value > theNode->value)
	{
		if (theRoot->Left == nullptr)
		{
			theRoot->Left = theNode;
			theNode->Parent = theRoot;
		}
		else
			bst_insert(theNode, theRoot->Left);
	}
	else if (theRoot->value < theNode->value)
	{
		if (theRoot->Right == nullptr)
		{
			theRoot->Right = theNode;
			theNode->Parent = theRoot;
		}
		else
			bst_insert(theNode, theRoot->Right);
	}
  else
  {
    theNode=nullptr;
  }
}
void RedBlackTree::insert_balancer(Node* theNode)
{
	if (theNode->Parent->color != Black)
	{
		if (theNode->Parent->Parent->Left != nullptr && theNode->Parent->Parent->Right != nullptr)
		{
			if (theNode->Parent->Parent->Left->color == Red && theNode->Parent->Parent->Right->color == Red)
			{
				recolorator(theNode);
				if (theNode->Parent->Parent->Parent != nullptr)
				{
					insert_balancer(theNode->Parent->Parent);
				}
				else
				{
					theNode->Parent->Parent->color = Black;
				}
			}
			else
			{
				if (theNode->Parent->value == theNode->Parent->Parent->Left->value)
				{
					if (theNode->Parent->Left->value == theNode->value)
					{
						theNode->Parent->Parent->color = Red;
						theNode->Parent->color = Black;
						right_rotater(theNode->Parent->Parent);
					}
					else
					{
						left_rotater(theNode->Parent);
						Node* newTheNode = theNode->Left;
						newTheNode->Parent->Parent->color = Red;
						newTheNode->Parent->color = Black;
						right_rotater(newTheNode->Parent->Parent);
					}
				}
				else
				{
					if (theNode->Parent->Right->value == theNode->value)
					{
						theNode->Parent->color = Black;
						theNode->Parent->Parent->color = Red;
						left_rotater(theNode->Parent->Parent);
					}
					else
					{
						right_rotater(theNode->Parent);
						Node* newTheNode = theNode->Right;
						newTheNode->Parent->Parent->color = Red;
						newTheNode->Parent->color = Black;
						left_rotater(newTheNode->Parent->Parent);
					}
				}
			}
		}
		else
		{
			if (theNode->Parent->Parent->Right == nullptr)
			{
				if (theNode->Parent->Left != nullptr)
				{
					if (theNode->Parent->Left->value == theNode->value)
					{
						theNode->Parent->Parent->color = Red;
						theNode->Parent->color = Black;
						right_rotater(theNode->Parent->Parent);
					}
					else
					{
						left_rotater(theNode->Parent);
						Node* newTheNode = theNode->Left;
						newTheNode->Parent->Parent->color = Red;
						newTheNode->Parent->color = Black;
						right_rotater(newTheNode->Parent->Parent);
					}
				}
				else
				{
					left_rotater(theNode->Parent);
					Node* newTheNode = theNode->Left;
					newTheNode->Parent->Parent->color = Red;
					newTheNode->Parent->color = Black;
					right_rotater(newTheNode->Parent->Parent);
				}
			}
			else
			{
				if (theNode->Parent->Right != nullptr)
				{
					if (theNode->Parent->Right->value == theNode->value)
					{
						theNode->Parent->color = Black;
						theNode->Parent->Parent->color = Red;
						left_rotater(theNode->Parent->Parent);
					}
					else
					{
						left_rotater(theNode->Parent);
						Node* newTheNode = theNode->Right;
						newTheNode->Parent->Parent->color = Red;
						newTheNode->Parent->color = Black;
						left_rotater(newTheNode->Parent->Parent);
					}
				}
				else
				{
					right_rotater(theNode->Parent);
					Node* newTheNode = theNode->Right;
					newTheNode->Parent->Parent->color = Red;
					newTheNode->Parent->color = Black;
					left_rotater(newTheNode->Parent->Parent);
				}
			}
		}
	}
}
void RedBlackTree::Remove(unsigned long long int value)
{
	Node* theNode = find(value);
	if (theNode!=nullptr)//this if avoids deleting non-existing value
		bst_remove(theNode, root);
}
void RedBlackTree::bst_remove(Node* theNode, Node* theRoot)
{
	// in binary search tree, there are 3 cases for deleting: the node has no child, 1 child, and 2 children
	if (theNode->Left == nullptr && theNode->Right == nullptr)
	{
		//cout << "Branch 1 reached" << endl;
		//cout << "No Child" << endl;
		//if it has no child, just delete it. don't forget delete it from its parent's child list.
		if (theNode->Parent == nullptr)
			//if it is the root
			root = nullptr;
		else if (theNode->Parent->Left == theNode)
			//if it is the left child
			theNode->Parent->Left = nullptr;
		else
			//if it is the right child
		{
			theNode->Parent->Right = nullptr;
		}
		theNode->color ++;
		//Note this trick here: black is 1, red is 0, and double black is hence 2.
		//We know that, for the replacing node, if it is red & red then it is red; if it is red & black it is black; if it is black & black it is double black;
		//It just fits with addition.
		remove_balancer(theNode);
		delete theNode;
	}
	else if (theNode->Left == nullptr || theNode->Right == nullptr)
	{
		//cout << "Single Child" << endl;
		//if it has one child, then use the child to replace it
		if (theNode->Left != nullptr)
		{
			//cout << "Branch 2 reached" << endl;
			theNode->Left->Parent = theNode->Parent;
			if (theNode->Parent == nullptr)
				root = theNode->Left;
			else if (theNode->Parent->Left == theNode)
				theNode->Parent->Left = theNode->Left;
			else
				theNode->Parent->Right = theNode->Left;
			theNode->Left->color += theNode->color;
			//Trick again. See comment above
			remove_balancer(theNode->Left);
		}
		else
		{
			//cout << "Branch 3 reached" << endl;
			theNode->Right->Parent = theNode->Parent;
			if (theNode->Parent == nullptr)
				root = theNode->Right;
			else if (theNode->Parent->Left == theNode)
				theNode->Parent->Left = theNode->Right;
			else
				theNode->Parent->Right = theNode->Right;
			theNode->Right->color += theNode->color;
			remove_balancer(theNode->Right);
		}
		delete theNode;
	}
	else
	{
		//the line below is for debug check
		//cout << "Double Child" << endl;
		if (theRoot != root)
			cout << "Unexpected behavior!" << endl;
		//cout << "Branch 4 reached" << endl;
		//then if it has 2 children, replace it with the immediate successor
		Node* SucNode = find(GetMin(theNode->Right));
		//exchange value
		unsigned long long int temp = SucNode->value;
		SucNode->value = theNode->value;
		theNode->value = temp;
		//note, exchanging value and deleting it does NOT make the tree to be an invalid BST.
		bst_remove(SucNode, theNode->Right);
		//note, it will not cause infinite loop since the immediate successor must not have 2 children.
	}
	//Need work on this part
}
void RedBlackTree::remove_balancer(Node* theNode)
{
	if (theNode->color == DoubleBlack)
	{//if there is double black, then we need to deal with it
		if (theNode->Parent == nullptr)
			//if the double black happen at the root node, just turn it to black.
			theNode->color = Black;
		else
		{//otherwise...
			//initialize some varibles
			bool isLeftChild = true;
			bool isNotAbandonedNode = (theNode->Parent->Left == theNode || theNode->Parent->Right == theNode);
			Node* Sibling = nullptr;
			unsigned short SibColor = Black;
			Node* SibLeft = nullptr;
			unsigned short SibLeftColor = Black;
			unsigned short SibRightColor = Black;
			Node* SibRight = nullptr;
			if (isNotAbandonedNode)
				if (theNode->value < theNode->Parent->value)
				{
					//cout << "Branch A reached" << endl;
					isLeftChild = true;
					if (theNode->Parent->Right != nullptr)
					{
						Sibling = theNode->Parent->Right;
						SibColor = Sibling->color;
						if (Sibling->Left != nullptr)
						{
							SibLeft = Sibling->Left;
							SibLeftColor = SibLeft->color;
						}
						else
						{
							SibLeftColor = Black;
						}
						if (Sibling->Right != nullptr)
						{
							SibRight = Sibling->Right;
							SibRightColor = SibRight->color;
						}
						else
						{
							SibRightColor = Black;
						}
					}
					SibColor = Black;
				}
				else
				{
					//cout << "Branch B reached" << endl;
					isLeftChild = false;
					if (theNode->Parent->Left != nullptr)
					{
						Sibling = theNode->Parent->Left;
						SibColor = Sibling->color;
						if (Sibling->Left != nullptr)
						{
							SibLeft = Sibling->Left;
							SibLeftColor = SibLeft->color;
						}
						else
						{
							SibLeftColor = Black;
						}
						if (Sibling->Right != nullptr)
						{
							SibRight = Sibling->Right;
							SibRightColor = SibRight->color;
						}
						else
						{
							SibRightColor = Black;
						}
					}
					SibColor = Black;
				}
			else
			{
				//cout << "Branch C reached" << endl;
				if (theNode->Parent->Left != nullptr)
					isLeftChild = false;
				if (isLeftChild)
					Sibling = theNode->Parent->Right;
				else
					Sibling = theNode->Parent->Left;
				SibColor = Sibling->color;
				if (Sibling->Left != nullptr)
				{
					SibLeft = Sibling->Left;
					SibLeftColor = SibLeft->color;
				}
				else
				{
					SibLeftColor = Black;
				}
				if (Sibling->Right != nullptr)
				{
					SibRight = Sibling->Right;
					SibRightColor = SibRight->color;
				}
				else
				{
					SibRightColor = Black;
				}
			}
			//initializing finished.
			if (Sibling == nullptr)
				cout << "unexpected behavior!!!" << endl;
			else if (SibColor == Black)
			{//case 2 in lecture. Note, the implementation of this case is not standard.
				if (SibLeftColor == Black && SibRightColor == Black)
				{
					//cout << "Branch a reached" << endl;
					Sibling->color = Red;
					theNode->color = Black;
					theNode->Parent->color++;//this trick has been explained before
					remove_balancer(theNode->Parent);
				}
				else
				{
					if (isLeftChild)
					{
						if (SibRightColor != Red)
						{//left left case
							//cout << "Branch b reached" << endl;
							SibLeft->color = Black;
							Sibling->color = Red;
							right_rotater(Sibling);
							remove_balancer(theNode);
						}
						else
						{//left right case
							//cout << "Branch c reached" << endl;
							SibRight->color = Sibling->color;
							Sibling->color = theNode->Parent->color;
							theNode->Parent->color = Black;
							theNode->color = Black;
							left_rotater(theNode->Parent);
						}
					}
					else
					{
						if (SibLeftColor != Red)
						{//right right case
							//cout << "Branch d reached" << endl;
							Sibling->color = Red;
							Sibling->Right->color = Black;
							left_rotater(Sibling);
							remove_balancer(theNode);
						}
						else
						{//right left case
							//cout << "Branch e reached" << endl;
							SibLeft->color = Black;
							Sibling->color = theNode->Parent->color;
							theNode->Parent->color = Black;
							theNode->color = Black;
							right_rotater(theNode->Parent);
						}
					}
				}
			}
			else
			{//case 3 in lecture
				//cout << "Branch f reached" << endl;
				Sibling->color = Black;
				theNode->Parent->color = Red;
				if (isLeftChild)
					left_rotater(theNode->Parent);
				else
					right_rotater(theNode->Parent);
				remove_balancer(theNode);
			}
		}
	}
}
void RedBlackTree::left_rotater(Node* theNode)
{
	if (theNode->Parent == nullptr)
	{
		root = theNode->Right;
		root->Parent = nullptr;
		theNode->Right = root->Left;
		if (theNode->Right != nullptr)
			theNode->Right->Parent = theNode;
		root->Left = theNode;
		theNode->Parent = root;
	}
	else
	{
		bool StatePerserveVarible = false;
		if (theNode->Parent->Left !=nullptr)
			StatePerserveVarible=(theNode->Parent->Left->value == theNode->value);
		if (StatePerserveVarible)
			theNode->Parent->Left = theNode->Right;
		else
			theNode->Parent->Right = theNode->Right;
		theNode->Right->Parent = theNode->Parent;
		theNode->Right = theNode->Right->Left;
		if (theNode->Right != nullptr)
			theNode->Right->Parent = theNode;
		if (StatePerserveVarible)
			theNode->Parent = theNode->Parent->Left;
		else
			theNode->Parent = theNode->Parent->Right;
		theNode->Parent->Left = theNode;
	}
}
void RedBlackTree::right_rotater(Node* theNode)
{
	if (theNode->Parent == nullptr)
	{
		root = theNode->Left;
		root->Parent = nullptr;
		theNode->Left = root->Right;
		if (theNode->Left != nullptr)
			theNode->Left->Parent = theNode;
		root->Right = theNode;
		theNode->Parent = root;
	}
	else
	{
		bool StatePerserveVarible = false;
		if (theNode->Parent->Left != nullptr)
			StatePerserveVarible = (theNode->Parent->Left->value == theNode->value);
		if (StatePerserveVarible)
			theNode->Parent->Left = theNode->Left;
		else
			theNode->Parent->Right = theNode->Left;
		theNode->Left->Parent = theNode->Parent;
		theNode->Left = theNode->Left->Right;
		if (theNode->Left != nullptr)
			theNode->Left->Parent = theNode;
		if (StatePerserveVarible)
			theNode->Parent = theNode->Parent->Left;
		else
			theNode->Parent = theNode->Parent->Right;
		theNode->Parent->Right = theNode;
	}
}
void RedBlackTree::recolorator(Node* theNode)
{
	theNode->Parent->Parent->Left->color = Black;
	theNode->Parent->Parent->Right->color = Black;
	theNode->Parent->Parent->color = Red;
}
unsigned long long int RedBlackTree::GetMin()
{
	return GetMin(root);
}
unsigned long long int RedBlackTree::GetMin(Node* theRoot)
{
	if (theRoot->Left != nullptr)
		return GetMin(theRoot->Left);
	else
		return theRoot->value;
}
unsigned long long int RedBlackTree::GetMax()
{
	return GetMax(root);
}
unsigned long long int RedBlackTree::GetMax(Node* theRoot)
{
	if (theRoot->Right != nullptr)
		return GetMax(theRoot->Right);
	else
		return theRoot->value;
}
size_t RedBlackTree::Size()
{
	return Size(root);
}
size_t RedBlackTree::Size(Node* theRoot)
{
	size_t output = 0;
	if (theRoot != nullptr)
	{
		output++;
		output += Size(theRoot->Left);
		output += Size(theRoot->Right);
	}
	return output;
}
void RedBlackTree::printer()
{
	printer(root);
}
void RedBlackTree::printer(Node* theRoot)
{
	if (theRoot->Left != nullptr)
		printer(theRoot->Left);
	cout << theRoot->value << ", ";
	if (theRoot->Right != nullptr)
		printer(theRoot->Right);
}
void RedBlackTree::NodePrinter(Node* theNode)
{
	cout << theNode->value << "|";
	if (theNode->color == Black)
		cout << "Black, ";
	if (theNode->color == Red)
		cout << "Red,   ";
	if (theNode->Parent != nullptr)
		cout << "P" << theNode->Parent->value;
	else
		cout << "P*";
	if (theNode->Left != nullptr)
		cout << ", {" << theNode->Left->value;
	else
		cout << ", {*";
	if (theNode->Right != nullptr)
		cout <<"," << theNode->Right->value<<"}";
	else
		cout << ",*}";
	cout << endl;
}
string RedBlackTree::ToInfixString(Node* theRoot) const
{
	string output;
	if (theRoot != nullptr)
	{
		output += ToInfixString(theRoot->Left);
		output += " ";
		if (theRoot->color == Red)
		{
			output += "R";
		}
		else
		{
			output += "B";
		}
		output += to_string(theRoot->value);
		output += " ";
		output += ToInfixString(theRoot->Right);
	}
	return output;
}
string RedBlackTree::ToPrefixString(Node* theRoot) const 
{
	string output;
	if (theRoot != nullptr)
	{
		output += " ";
		if (theRoot->color == Red)
		{
			output += "R";
		}
		else
		{
			output += "B";
		}
		output += to_string(theRoot->value);
		output += " ";
		output += ToPrefixString(theRoot->Left);
		output += ToPrefixString(theRoot->Right);
	}
	return output;
}
string RedBlackTree::ToPostfixString(Node* theRoot) const
{
	string output;
	if (theRoot != nullptr)
	{
		output += ToPostfixString(theRoot->Left);
		output += ToPostfixString(theRoot->Right);
		output += " ";
		if (theRoot->color == Red)
		{
			output += "R";
		}
		else
		{
			output += "B";
		}
		output += to_string(theRoot->value);
		output += " ";
	}
	return output;
}
string RedBlackTree::ToInfixString() const 
{ 
	return ToInfixString(root); 
}
string RedBlackTree::ToPrefixString() const 
{
	return ToPrefixString(root); 
}
string RedBlackTree::ToPostfixString() const 
{
	return ToPostfixString(root);
}
