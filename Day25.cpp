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

long long SNAFUtoDecimal(string s) {
	long long n = 0;
	long long v = 1;
	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i] == '=') {
			n -= 2 * v;
		}
		else if (s[i] == '-') {
			n -= v;
		}
		else {
			n += (s[i] - '0') * v;
		}
		v *= 5;
	}
	return n;
}

string DecimalToSNAFU(long long n) {
	string s;
	long long v = 5;
	while (n != 0) {
		long long remainder = n % v;
		char c;
		if (remainder < 3) {
			c = remainder + '0';
			s.insert(0, 1, c);
			n = (n - remainder) / v;
		}
		else if (remainder == 3) {
			s.insert(0, 1, '=');
			n = (n + 2) / v;
		}
		else {
			s.insert(0, 1, '-');
			n = (n + 1) / v;
		}
	}
	return s;
}

int main(int argc, char * argv[]) {
	string s;
	long long total = 0;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		while (infile >> s) {
			long long n = SNAFUtoDecimal(s);
			//string test = DecimalToSNAFU(n);
			//cout << s << " -> " << n << " -> " << test << endl;
			total += n;
		}
		cout << "The total amount in decimal is " << total << endl;
		cout << "The total amount in SNAFU is " << DecimalToSNAFU(total) << endl;
	}
	return 0;
}