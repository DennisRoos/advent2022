#include <iostream>
#include <fstream>
//#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include <cmath>

using namespace std;



int main(int argc, char* argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int total1 = 0;
		int total2 = 0;
		char a;
		char b;

		while (infile >> a) {
			infile >> b;
			b -= 23;
			int score;
			int score2;
			if (b == 'A') {
				score = 1;
				if (a == 'A') {
					score2 = 3;
				}
				else if (a == 'B') {
					score2 = 1;
				}
				else {
					score2 = 2;
				}
			}
			else if (b == 'B') {
				score = 2;
				score2 = a - 'A' + 4;
			}
			else {
				score = 3;
				if (a == 'A') {
					score2 = 8;
				}
				else if (a == 'B') {
					score2 = 9;
				}
				else {
					score2 = 7;
				}
			}

			if (a == b) {//draw
				score += 3;
			}
			else if ((a == 'A' && b == 'B') ||
				(a == 'B' && b == 'C') ||
				(a == 'C' && b == 'A')){
				score += 6;
			}
			total1 += score;
			total2 += score2;
		}
		cout << "Total score for part 1 is " << total1 << endl;
		cout << "Total score for part 2 is " << total2 << endl;
	}
	return 0;
}