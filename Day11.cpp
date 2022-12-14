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

class monkey {
public:
	char optype;
	int opn;
	long long test;
	int inspects;
	int yes;
	int no;
	vector<long long> items;
	monkey(char c, int o, int t, int y, int n) {
		optype = c;
		opn = o;
		test = t;
		inspects = 0;
		yes = y;
		no = n;
	}
};

monkey* M[8];

int main(int argc, char * argv[]) {
	long long ceiling = 1;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		//test initialization
		/*
		int monkeycount = 4;
		M[0] = new monkey('*', 19, 23, 2, 3);
		M[1] = new monkey('+', 6, 19, 2, 0);
		M[2] = new monkey('*', 0, 13, 1, 3);
		M[3] = new monkey('+', 3, 17, 0, 1);

		M[0]->items.push_back(79);
		M[0]->items.push_back(98);

		M[1]->items.push_back(54);
		M[1]->items.push_back(65);
		M[1]->items.push_back(75);
		M[1]->items.push_back(74);

		M[2]->items.push_back(79);
		M[2]->items.push_back(60);
		M[2]->items.push_back(97);

		M[3]->items.push_back(74);*/
		//end test initialisation

		int monkeycount = 8;
		M[0] = new monkey('*', 3, 5, 2, 3);
		M[1] = new monkey('+', 8, 11, 4, 7);
		M[2] = new monkey('+', 2, 2, 5, 3);
		M[3] = new monkey('+', 4, 13, 1, 5);
		M[4] = new monkey('*', 19, 7, 7, 6);
		M[5] = new monkey('+', 5, 3, 4, 1);
		M[6] = new monkey('*', 0, 17, 0, 2);
		M[7] = new monkey('+', 1, 19, 6, 0);

		M[0]->items.push_back(65);
		M[0]->items.push_back(78);

		M[1]->items.push_back(54);
		M[1]->items.push_back(78);
		M[1]->items.push_back(86);
		M[1]->items.push_back(79);
		M[1]->items.push_back(73);
		M[1]->items.push_back(64);
		M[1]->items.push_back(85);
		M[1]->items.push_back(88);

		M[2]->items.push_back(69);
		M[2]->items.push_back(97);
		M[2]->items.push_back(77);
		M[2]->items.push_back(88);
		M[2]->items.push_back(87);

		M[3]->items.push_back(99);

		M[4]->items.push_back(60);
		M[4]->items.push_back(57);
		M[4]->items.push_back(52);

		M[5]->items.push_back(91);
		M[5]->items.push_back(82);
		M[5]->items.push_back(85);
		M[5]->items.push_back(73);
		M[5]->items.push_back(84);
		M[5]->items.push_back(53);

		M[6]->items.push_back(88);
		M[6]->items.push_back(74);
		M[6]->items.push_back(68);
		M[6]->items.push_back(56);

		M[7]->items.push_back(54);
		M[7]->items.push_back(82);
		M[7]->items.push_back(72);
		M[7]->items.push_back(71);
		M[7]->items.push_back(53);
		M[7]->items.push_back(99);
		M[7]->items.push_back(67);

		for (int i = 0; i < monkeycount; i++) {
			ceiling *= M[i]->test;
		}
		cout << ceiling << endl;

		for (int rounds = 0; rounds < 10000; rounds++) {
			for (int i = 0; i < monkeycount; i++) {
				for (int k = 0; k < M[i]->items.size(); k++) {
					long long n = M[i]->items[k];
					long long m;
					if (M[i]->opn == 0) {
						m = n;
					}
					else {
						m = M[i]->opn;
					}
					if (M[i]->optype == '*') {
						n *= m;
					}
					else {
						n += m;
					}

					//n = n / 3;
					n = n % ceiling;
					M[i]->inspects++;
					if (n % M[i]->test == 0) {
						M[M[i]->yes]->items.push_back(n);
					}
					else {
						M[M[i]->no]->items.push_back(n);
					}
				}
				M[i]->items.clear();
			}
		}
		for (int i = 0; i < monkeycount; i++) {
			cout << i << ": " << M[i]->inspects << endl;
		}

	}
	return 0;
}