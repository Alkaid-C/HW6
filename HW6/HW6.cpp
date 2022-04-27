
#include <iostream>
#include <cassert>
#include <random>
#include <cstdlib>
#include <ctime>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor() {
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt->ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");

	cout << "PASSED!" << endl << endl;
}


void TestInsertFirstNode() {
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode() {
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree* rbt = new RedBlackTree();
	rbt->Insert(30); // leak here
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode() {
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree* rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;

	// more tests go here
	// consider some symmetry!

	cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode() {
	cout << "Testing Insert Fourth Node..." << endl;

	cout << "TESTS MISSING" << endl << endl;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode() {
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree* rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;

	cout << "TESTS MISSING" << endl << endl;

	cout << "PASSED!" << endl << endl;
}


void TestToStrings() {
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests() {
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree* rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;


	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;


	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor() {
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);
	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);
	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}





void TestContains() {
	cout << "Testing Contains..." << endl;
	RedBlackTree* rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);


	assert(rbt->Contains(34));
	assert(rbt->Contains(12));
	assert(rbt->Contains(35) == false);
	delete rbt;
	rbt = new RedBlackTree();
	assert(rbt->Contains(34) == false);
	delete rbt;
	cout << "PASSED!" << endl << endl;
}


void TestGetMinimumMaximum() {
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	rbt.Insert(20);
	rbt.Insert(60);
	rbt.Insert(33);
	rbt.Insert(23);
	rbt.Insert(85);
	rbt.Insert(61);
	assert(rbt.GetMin() == 20);
	assert(rbt.GetMax() == 85);

	cout << "PASSED!" << endl << endl;
}


void TestDelete() {
	cout << "Testing Delete..." << endl;

	RedBlackTree tree = RedBlackTree();
	cout << endl << "Insert 7,3,18,10,22,8,11,26,2,6,13" << endl;
	tree.Insert(7);
	tree.Insert(3);
	tree.Insert(18);
	tree.Insert(10);
	tree.Insert(22);
	tree.Insert(8);
	tree.Insert(11);
	tree.Insert(26);
	tree.Insert(2);
	tree.Insert(6);
	tree.Insert(13);
	tree.DebugPrinter();
	cout << endl << "Deleting 18, 11, 3, 10, 22" << endl;

	tree.Remove(18);
	tree.Remove(11);
	tree.Remove(3);
	tree.Remove(10);
	tree.Remove(22);

	tree.DebugPrinter();
	cout << endl << "Deleting 23(not in the tree)" << endl;
	tree.Remove(23);
	tree.DebugPrinter();
	cout << endl << "Please check the result by hand" << endl<<endl;
}



void SpeedTest()
{
	const int N = 3700000;
	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();
	for (int i = 0; i < N; i++) {
		rbt.Insert(i);
	}
	clock_t stop = clock();
	double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Collected " << rbt.Size() << " ID numbers in " << (duration) << " seconds." << endl;
	rbt.Remove(rand() % 3700000);
	rbt.Remove(rand() % 3700000);
	rbt.Remove(rand() % 3700000);
	rbt.Remove(rand() % 3700000);
	rbt.Remove(rand() % 3700000);
	clock_t remove = clock();
	double duration_remove = (static_cast<double>(remove - stop)) / CLOCKS_PER_SEC;
	cout << "Removeed 5 ID numbers in " << (duration_remove) << " seconds." << endl;
	rbt.Insert(rand());
	rbt.Insert(rand());
	rbt.Insert(rand());
	rbt.Insert(rand());
	rbt.Insert(rand());
	clock_t add = clock();
	double duration_add = (static_cast<double>(add - remove)) / CLOCKS_PER_SEC;
	cout << "Added 5 ID numbers in " << (duration_add) << " seconds." << endl;
}


int main() {
	TestSimpleConstructor();
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();
	TestToStrings();
	TestInsertRandomTests();
	TestCopyConstructor();
	TestContains();
	TestGetMinimumMaximum();
	TestDelete();
	cout << "ALL TESTS PASSED!!" << endl;
	SpeedTest();
	return 0;
	
}
