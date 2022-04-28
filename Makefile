all:
	g++ -Wall -O3 HW6/RedBlackTree.cpp HW6/test.cpp -o test
	g++ -Wall -O3 HW6/RedBlackTree-P.cpp HW6/speedTest.cpp -o speed-test
	
