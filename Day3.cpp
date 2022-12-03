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

char overlap2(int n, string s1, string s2) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (s1[i] == s2[j]) {
				return s1[i];
			}
		}
	}
	return '_';
}

char overlap3(string s1, string s2, string s3) {

	for (int i = 0; i < s1.size(); i++) {
		for (int j = 0; j < s2.size(); j++) {
			for (int k = 0; k < s3.size(); k++) {
				if (s1[i] == s2[j] && s1[i] == s3[k]) {
					return s1[i];
				}
			}
		}
	}
	return '_';
}

int priority(char c) {
	if (c >= 'a') {//lowercase letter
		return c - 96;
	}
	else {//uppercase letter
		return c - 38;
	}
}

int part1(string s) {

	int n = s.size() / 2;
	string s1 = s.substr(0, n);
	string s2 = s.substr(n, n);
	char c = overlap2(n, s1, s2);
	return priority(c);
}

int main(int argc, char* argv[]) {
	int totalpriority = 0;
	int badgesum = 0;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s1;
		string s2;
		string s3;
		while (infile >> s1) {
			infile >> s2;
			infile >> s3;
			totalpriority += part1(s1);
			totalpriority += part1(s2);
			totalpriority += part1(s3);
			char c = overlap3(s1, s2, s3);
			badgesum += priority(c);
		}
		cout << "Total priority for part 1 is " << totalpriority << endl;
		cout << "Badge priority for part 2 is " << badgesum << endl;

	}
	return 0;
}