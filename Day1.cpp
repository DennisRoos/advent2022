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

int main(int argc, char* argv[]) {

	string s;
	ifstream f("data.txt");
	int highest = 0;
	int total = 0;
	int n;
	while (getline(f, s)) {
		if (s.empty()) {
			if (total > highest) {
				highest = total;
			}
			total = 0;
		}
		else{
			s >> n;
			total += n;
		}
	}
	cout << "The highest calorie count was " << highest << endl;
	return 0;
}