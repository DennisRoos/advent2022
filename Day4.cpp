
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;


int main(int argc, char* argv[]) {

	regex re("([\\d]+)-([\\d]+),([\\d]+)-(-?[\\d]+)");
	string s;
	smatch match;
	ifstream infile;
	infile.open("data.txt");
	int total = 0;
	int total2 = 0;
	if (infile.is_open()) {
		string command;
		while (infile >> s) {
			if (regex_search(s, match, re) == true) {
				int a1 = stoi(match.str(1));
				int a2 = stoi(match.str(2));
				int b1 = stoi(match.str(3));
				int b2 = stoi(match.str(4));
				if ((b1 <= a1 && b2 >= a2) || (a1 <= b1 && a2 >= b2)) {
					total++;
				}
				if (a2 >= b1 && a1 <= b2) {
					total2++;
				}


			}


		}

	}
	cout << "There were " << total << " pairs with complete overlap\n";
	cout << "There were " << total2 << " pairs with some overlap\n";
}