#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

int X;
int score;
int cycle;

void noop() {
	cycle++;
	if ((cycle - 20) % 40 == 0) {
		score += cycle * X;
	}
	int c = (cycle - 1) % 40;
	if (c <= X + 1 && c >= X - 1) {
		cout << '#';
	}
	else {
		cout << '.';
	}
	if (cycle % 40 == 0) {
		cout << endl;
	}
}

int main(int argc, char * argv[]) {
	X = 1;
	score = 0;
	cycle = 0;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		cout << "test " << endl;
		string s;
		int n;
		while (infile >> s) {
			if (s.compare("noop") == 0) {
				noop();
			}
			else {//addx instruction
				noop();
				noop();
				infile >> n;
				X += n;
			}
		}
		cout << "The signal strength is " << score << endl;
	}
	return 0;
}