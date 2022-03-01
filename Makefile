all:
	g++ -g -Wall RedBlackTree.h RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests
	g++ -g -Wall RedBlackTree.h RedBlackTree.cpp SpeedTest.cpp -o speed-test