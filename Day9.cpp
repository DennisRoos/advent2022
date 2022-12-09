
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

bool V[1000][1000];
bool V2[1000][1000];

int X[10];
int Y[10];


void move(int i) {
	int j = i + 1;
	if (Y[i] < Y[j] - 1) {
		if (X[i] < X[j]) {
			X[j]--;
		}
		else if (X[i] > X[j]) {
			X[j]++;
		}
		Y[j]--;
	}
	else if (Y[i] > Y[j] + 1) {
		if (X[i] < X[j]) {
			X[j]--;
		}
		else if (X[i] > X[j]) {
			X[j]++;
		}
		Y[j]++;
	}
	else if (X[i] < X[j] - 1) {
		if (Y[i] < Y[j]) {
			Y[j]--;
		}
		else if (Y[i] > Y[j]) {
			Y[j]++;
		}
		X[j]--;
	}
	else if (X[i] > X[j] + 1) {
		if (Y[i] < Y[j]) {
			Y[j]--;
		}
		else if (Y[i] > Y[j]) {
			Y[j]++;
		}
		X[j]++;
	}
	return;
}


int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	int n;
	char d;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			V[i][j] = false;
			V2[i][j] = false;
		}
	}
	for (int i = 0; i < 10; i++) {
		X[i] = 500;
		Y[i] = 500;
	}
	if (infile.is_open())
	{
		while (infile >> d) {
			infile >> n;
			if (d == 'U') {
				for (int i = 0; i < n; i++) {
					Y[0]--;
					for (int k = 0; k < 9; k++) {
						move(k);
					}
					V[X[1]][Y[1]] = true;
					V2[X[9]][Y[9]] = true;
				}
			}
			else if (d == 'D') {
				for (int i = 0; i < n; i++) {
					Y[0]++;
					for (int k = 0; k < 9; k++) {
						move(k);
					}
					V[X[1]][Y[1]] = true;
					V2[X[9]][Y[9]] = true;
				}
			}
			else if (d == 'L') {
				for (int i = 0; i < n; i++) {
					X[0]--;
					for (int k = 0; k < 9; k++) {
						move(k);
					}
					V[X[1]][Y[1]] = true;
					V2[X[9]][Y[9]] = true;
				}
			}
			else {
				for (int i = 0; i < n; i++) {
					X[0]++;
					for (int k = 0; k < 9; k++) {
						move(k);
					}
					V[X[1]][Y[1]] = true;
					V2[X[9]][Y[9]] = true;
				}
			}

		}
		int total = 0;
		int total2 = 0;
		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 1000; j++) {
				if (V[i][j]) {
					total++;
				}
				if (V2[i][j]) {
					total2++;
				}
			}
		}
		cout << "There were " << total << " visited tiles" << endl;
		cout << "There were " << total2 << " visited tiles by the longer tail" << endl;
	}
	return 0;
}