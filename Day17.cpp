
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <map>

using namespace std;

map<string, int> mymap;
char M[10000][9];
string s;
int highestx;
int heights[10000];

class block {
public:
	int blocksize;
	int x;
	int y;
	int tilex[5];
	int tiley[5];
	block(int n);
	void moveleft();
	void moveright();
	bool movedown();
};

block::block(int n) {
	y = 3;
	if (n == 0) {// - shape
		blocksize = 4;
		tilex[0] = 0;
		tiley[0] = 0;
		tilex[1] = 0;
		tiley[1] = 1;
		tilex[2] = 0;
		tiley[2] = 2;
		tilex[3] = 0;
		tiley[3] = 3;
	}
	else if (n == 1) {// + shape
		blocksize = 5;
		tilex[0] = 1;
		tiley[0] = 0;
		tilex[1] = 0;
		tiley[1] = 1;
		tilex[2] = 1;
		tiley[2] = 1;
		tilex[3] = 2;
		tiley[3] = 1;
		tilex[4] = 1;
		tiley[4] = 2;
	}
	else if (n == 2) {// _| shape
		blocksize = 5;
		tilex[0] = 0;
		tiley[0] = 0;
		tilex[1] = 0;
		tiley[1] = 1;
		tilex[2] = 0;
		tiley[2] = 2;
		tilex[3] = 1;
		tiley[3] = 2;
		tilex[4] = 2;
		tiley[4] = 2;
	}
	else if (n == 3) {// | shape
		blocksize = 4;
		tilex[0] = 0;
		tiley[0] = 0;
		tilex[1] = 1;
		tiley[1] = 0;
		tilex[2] = 2;
		tiley[2] = 0;
		tilex[3] = 3;
		tiley[3] = 0;
	}
	else if (n == 4) {// [] shape
		blocksize = 4;
		tilex[0] = 0;
		tiley[0] = 0;
		tilex[1] = 0;
		tiley[1] = 1;
		tilex[2] = 1;
		tiley[2] = 0;
		tilex[3] = 1;
		tiley[3] = 1;
	}
}

void block::moveleft() {
	bool b = true;
	for (int i = 0; i < blocksize; i++) {
		if (M[x + tilex[i]][y + tiley[i] - 1] == '#') {//hitting a wall
			b = false;

		}
	}
	if (b) {
		y--;
	}
	else {
		//cout << "Block hit wall to the left" << endl;
	}
}

void block::moveright() {
	bool b = true;
	for (int i = 0; i < blocksize; i++) {
		if (M[x + tilex[i]][y + tiley[i] + 1] == '#') {//hitting a wall
			b = false;
		}
	}
	if (b) {
		//cout << "Block moves right" << endl;
		y++;
	}
	else {
		//cout << "Block hit wall to the right" << endl;
	}
}

bool block::movedown() {
	bool b = true;
	for (int i = 0; i < blocksize; i++) {
		if (M[x + tilex[i] - 1][y + tiley[i]] == '#') {//hitting a wall
			b = false;
		}
	}
	if (b) {
		x--;
		//cout << "Block moves down" << endl;
		return false;
	}
	else {//block settles
		for (int i = 0; i < blocksize; i++) {
			M[x + tilex[i]][y + tiley[i]] = '#';
			if (x + tilex[i] > highestx) {
				highestx = x + tilex[i];
			}
		}
		//cout << "Block settles" << endl;
		return true;
	}
}


int main(int argc, char* argv[]) {
	highestx = 0;
	int blockcount = 0;
	int ventcount = 0;
	for (int i = 0; i < 10000; i++) {
		M[i][0] = '#';
		M[i][1] = '.';
		M[i][2] = '.';
		M[i][3] = '.';
		M[i][4] = '.';
		M[i][5] = '.';
		M[i][6] = '.';
		M[i][7] = '.';
		M[i][8] = '#';
	}
	for (int i = 1; i < 8; i++) {
		M[0][i] = '#';
	}
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open()) {
		infile >> s;
	}
	int turn = 1;
	while(turn <= 2022) {
		block* b = new block(blockcount);
		b->x = highestx + 4;
		blockcount = (blockcount + 1) % 5;
		bool settled = false;
		while (!settled) {
			if (s[ventcount] == '<') {
				b->moveleft();
			}
			else {
				b->moveright();
			}
			ventcount = (ventcount + 1) % s.size();
			settled = b->movedown();
		}
		heights[turn] = highestx;
		delete b;
		turn++;
	}

	std::cout << "The highest point in the tower after 2022 blocks is " << highestx << endl;
	bool found = false;
	int t = 0;
	while (!found) {
		block* b = new block(blockcount);
		b->x = highestx + 4;
		blockcount = (blockcount + 1) % 5;
		bool settled = false;
		while (!settled) {
			if (s[ventcount] == '<') {
				b->moveleft();
			}
			else {
				b->moveright();
			}
			ventcount = (ventcount + 1) % s.size();
			settled = b->movedown();
		}
		string K = to_string(blockcount);
		for (int i = 1; i < 8; i++) {
			int j = highestx;
			while (M[j][i] != '#') {
				j--;
			}
			K.append(to_string(highestx - j));
		}
		K.append(to_string(ventcount));
		heights[turn] = highestx;
		delete b;
		map<string, int>::iterator it = mymap.find(K);
		if (it != mymap.end()) {
			t = it->second;
			found = true;
			std::cout << "Found a cycle after " << turn << " blocks. It matches the configuration at turn " << t << "." << endl;
			break;
		}
		else {
			mymap.insert({ K, turn });
		}
		turn++;
	}
	long long cyclecount = turn - t;
	long long cycles = (1000000000000 - turn) / cyclecount;
	long long heightdifference = highestx - heights[t];
	long long remaining = (1000000000000 - turn) % cyclecount;
	//cout << cyclecount << ", " << cycles << ", " << heightdifference << ", " << remaining << endl;

	for (long long i = 0; i < remaining; i++) {
		block* b = new block(blockcount);
		b->x = highestx + 4;
		blockcount = (blockcount + 1) % 5;
		bool settled = false;
		while (!settled) {
			if (s[ventcount] == '<') {
				b->moveleft();
			}
			else {
				b->moveright();
			}
			ventcount = (ventcount + 1) % s.size();
			settled = b->movedown();
		}
		delete b;
		turn++;
	}
	long long H = highestx;
	H += heightdifference * cycles;
	cout << "The highest point in the tower after 1000000000000 blocks is " << H << endl;

	/*for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 9; j++) {
			cout << M[i][j];
		}
		cout << endl;
	}*/

}