
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

string s; 

bool findmarker(int n, int k) {
	for (int i = k - n + 1; i <= k; i++) {
		for (int j = i + 1; j < k + 1; j++) {
			if (s[i] == s[j]) {
				return false;
			}
		}
	}
	return true;
}


int main(int argc, char* argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open()) {
		infile >> s;
		for (int i = 3; i < s.size(); i++) {
			if (findmarker(4, i)) {
				cout << "The first 4-size marker is at position " << i + 1 << endl;
				break;
			}
		}

		for (int i = 14; i < s.size(); i++) {
			if (findmarker(14, i)) {
				cout << "The first 14-size marker is at position " << i + 1 << endl;
				break;
			}
		}
	}
}