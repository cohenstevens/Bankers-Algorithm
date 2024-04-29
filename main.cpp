#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int PROCCESS = 5;	// # of processes
const int RESOURCES = 3; // # of resources

void input(int data[]) {
	ifstream in;
	in.open("input.txt");
	if (!in) { 	// error opening file
		cerr << "Error opening input file.\n";
		exit(2);
	}
	
	int i = 0, j;
	while (in >> j) { // numbers going into array
		data[i] = j;
		++i;
	}
}

int main() {
	const int arrSize = (RESOURCES*PROCCESS)+(RESOURCES*PROCCESS)+RESOURCES; // arrSize based on # of proccesses and resources
	int data[arrSize]; 
	input(data);
	
	// allocation matrix
	int alloc[PROCCESS][RESOURCES] = { 
		{ data[0],  data[1],  data[2]  },   // P0
		{ data[3],  data[4],  data[5]  },   // P1
		{ data[6],  data[7],  data[8]  },   // P2
		{ data[9],  data[10], data[11] },   // P3
		{ data[12], data[13], data[14] } }; // P4
							
	// max matrix
	int max[PROCCESS][RESOURCES] = { 
		{ data[15], data[16], data[17] },
		{ data[18], data[19], data[20] },
		{ data[21], data[22], data[23] },
		{ data[24], data[25], data[26] },
		{ data[27], data[28], data[29] } };	
			       
	// available resources
	int avail[RESOURCES] = { data[30], data[31], data[32] }; // Resource A B C
	
	// resource need matrix
	// max - alloc = need
	int need[PROCCESS][RESOURCES];	
	for (int i = 0; i < PROCCESS; ++i) {
		for (int j = 0; j < RESOURCES; ++j) {
			need[i][j] = max[i][j] - alloc[i][j];	
		}
	}
	
	bool finished[PROCCESS] = {false}, unsafe = false;
	int safe[PROCCESS], index = 0;	

	for (int i = 0; i < PROCCESS; ++i) {
		for (int j = 0; j < PROCCESS; ++j) {
			if (finished[j] == 0) {	// if process is not finished
				unsafe = false;
				for (int k = 0; k < RESOURCES; ++k) {
					if (need[j][k] > avail[k]) {	// if need > available = unsafe
						unsafe = true;	// unsafe state
						break;
					}
				}
						
				if (unsafe == false) {	// if theres been no unsafe state found
					safe[index++] = j;	// safe [index] = current process
					for (int l = 0; l < RESOURCES; ++l)
						avail[l] += alloc[j][l];	// add to list of available
					finished[j] = 1;	// process # is finished
				}
			}	
		}
	}
	unsafe = true;
	
	for (int i = 0; i < PROCCESS; ++i) {
		if (finished[i] == 0) {	// if not finished
			unsafe = false;	// in deadlock so its unsafe
			cout << "The system is not in a safe state.\n";
			exit(1);
			break;
		}
	}	
	
	if (unsafe == true) {
		cout << "The system is in a safe state. The proper sequence is: ";
		for (int i = 0; i < PROCCESS; ++i) {
			cout << "P";
			cout << safe[i] << " ";
		}
		cout << "\n";
	}
	
	return 0;
}
