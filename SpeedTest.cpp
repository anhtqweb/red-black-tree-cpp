#include <cstdlib>
#include <ctime>
#include <iostream>
#include "RedBlackTree.h"

using namespace std;


int main(){

	// create a simulated 3.7 million ID number system.
	const int N = 3700000;

	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();
	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Collected " << rbt.Size() << " ID numbers in " << (duration) << " seconds." << endl;


	// Your code goes here to simulate leaving / joining.
	int numInsert = 0;
	int numRemove = 0;

	while (numInsert < 5 || numRemove < 5) {
		int num = rand();
		duration = 0.0;
		if (rbt.Contains(num)) {
			if (numRemove < 5) {
				numRemove++;
				start = clock();
				rbt.Remove(num);
				stop = clock();
				duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
				cout << "Removing " << num << " takes " << duration << " seconds" << endl;
			}
		}
		else {
			if (numInsert < 5) {
				numInsert++;
				start = clock();
				rbt.Insert(num);
				stop = clock();
				duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
				cout << "Inserting " << num << " takes " << duration << " seconds" << endl;
			}
			
		}
	}

	return 0;
}