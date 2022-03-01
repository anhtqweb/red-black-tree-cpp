
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt->ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}


void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	// cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
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


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	cout << "rbt: "  << rbt->ToPrefixString() << endl;
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
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(65); // Right right
	assert(rbt->ToPrefixString() == " B45  R30  R65 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(35); // Left right
	assert(rbt->ToPrefixString() == " B35  R30  R45 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	rbt->Insert(45);
	// cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  B10  B30  R45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(65); // Right right
	rbt->Insert(85);
	assert(rbt->ToPrefixString() == " B45  B30  B65  R85 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(65); // Right right
	rbt->Insert(55);
	assert(rbt->ToPrefixString() == " B45  B30  B65  R55 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(65); // Right right
	rbt->Insert(85);
	rbt->Insert(100);
	assert(rbt->ToPrefixString() == " B45  B30  B85  R65  R100 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(65); // Right right
	rbt->Insert(85);
	rbt->Insert(75);
	assert(rbt->ToPrefixString() == " B45  B30  B75  R65  R85 ");
	delete rbt;	
	cout << "PASSED!" << endl << endl;
}

void TestToStrings(){
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

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
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

void TestCopyConstructor(){
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






void TestContains(){
	cout << "Testing Contains..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
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
	assert(!rbt->Contains(0));
	assert(!rbt->Contains(99));
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestGetMinimumMaximum(){
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

void TestSize() {
	cout << "Testing Size" << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);

	assert(rbt->Size() == 9);
	delete rbt;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.Size() == 6);

	RedBlackTree rbt2 = RedBlackTree();
	assert(rbt2.Size() == 0);

	cout << "PASSED!" << endl << endl;
}

void TestInsertWithRecursiveFixUp(){
	cout << "Testing Recursive FixUp..." << endl;
	// Red uncle, and we "move the blackness up"
	// the makes the grandparent red and that might cause issues
	// at the grand-parent level.
	// This may repeat until the root node (which must be black)
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(400);
	rbt->Insert(800);
	rbt->Insert(200);
	rbt->Insert(600);
	rbt->Insert(150);
	rbt->Insert(900);
	rbt->Insert(300);
	rbt->Insert(100);
	rbt->Insert(175);
	rbt->Insert(160); // does some weird stuff!
	assert(rbt->ToPrefixString() == " B200  R150  B100  B175  R160  R400  B300  B800  R600  R900 ");
	rbt->Insert(185);
	rbt->Insert(180); // does a recursive fix-up
	assert(rbt->ToPrefixString() == " B200  B150  B100  R175  B160  B185  R180  B400  B300  B800  R600  R900 ");
	// cout << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestRemoveSimple() {
	cout << "Testing remove simple" << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	rbt.Insert(15);

	assert(rbt.ToPrefixString() == " B30  R15 ");

	rbt.Remove(30);
	cout << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B15 ");

	cout << "PASSED!" << endl << endl;
}

void TestRemoveRoot() {
	cout << "Testing remove root" << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(9);

	assert(rbt.ToPrefixString() == " B9 ");

	rbt.Remove(9);
	assert(rbt.ToPrefixString() == "");

	cout << "PASSED!" << endl << endl;
}


void TestRemoveRoot2() {
	cout << "Testing remove root 2" << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(9);
	rbt.Insert(12);
	rbt.Insert(7);

	// assert(rbt.ToPrefixString() == " B9  R12 ");

	rbt.Remove(9);
	cout << rbt.ToPrefixString() << endl;
	// assert(rbt.ToPrefixString() == " B7 R12 ");

	cout << "PASSED!" << endl << endl;
}

void TestRemoveDoubleBlackRightRight() {
	cout << "Testing remove double black right right" << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	rbt.Insert(20);
	rbt.Insert(40);
	rbt.Insert(35);
	rbt.Insert(50);

	assert(rbt.ToPrefixString() == " B30  B20  B40  R35  R50 ");

	rbt.Remove(20);
	assert(rbt.ToPrefixString() == " B40  B30  R35  B50 ");

	cout << "PASSED!" << endl << endl;
}

void TestRemoveDoubleBlackRightLeft() {
	cout << "Testing remove double black right left" << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	rbt.Insert(20);
	rbt.Insert(40);
	rbt.Insert(35);

	assert(rbt.ToPrefixString() == " B30  B20  B40  R35 ");

	rbt.Remove(20);
	cout << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B35  B30  B40 ");

	cout << "PASSED!" << endl << endl;
}

void TestRemoveDoubleBlackLeftLeft() {
	cout << "Testing remove double black left left" << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	rbt.Insert(20);
	rbt.Insert(40);
	rbt.Insert(15);

	assert(rbt.ToPrefixString() == " B30  B20  R15  B40 ");

	rbt.Remove(40);
	cout << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B20  B15  B30 ");

	cout << "PASSED!" << endl << endl;
}

void TestRemoveDoubleBlackLeftRight() {
	cout << "Testing remove double black left left" << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	rbt.Insert(20);
	rbt.Insert(40);
	rbt.Insert(25);

	assert(rbt.ToPrefixString() == " B30  B20  R25  B40 ");

	rbt.Remove(40);
	cout << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B25  B20  B30 ");

	cout << "PASSED!" << endl << endl;
}

void Test() {
	cout << "test" << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	rbt.Insert(15);
	rbt.Insert(10);
	rbt.Insert(45);

	rbt.Remove(15);
	cout << rbt.ToPrefixString() << endl;
	rbt.Remove(30);
	cout << rbt.ToPrefixString() << endl;
}

int main(){
	
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
	TestSize();
	TestInsertWithRecursiveFixUp();

	TestRemoveSimple();
	TestRemoveRoot();
	TestRemoveRoot2();
	TestRemoveDoubleBlackRightRight();
	TestRemoveDoubleBlackRightLeft();
	TestRemoveDoubleBlackLeftLeft();
	TestRemoveDoubleBlackLeftRight();
	// Test();
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
