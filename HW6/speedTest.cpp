
#include <iostream>
#include <cassert>
#include <random>
#include <cstdlib>
#include <ctime>
#include "RedBlackTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){

	// create a simulated 3.7 million ID number system.
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


	return 0;
}
