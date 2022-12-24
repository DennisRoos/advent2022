
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;


char M[1000][1000];
char C[6][50][50];
string instructions;
int T[6][4]; //returns the tile one walks onto when walking out of the given tile with given facing
int F[6][4]; // returns the facing for above
bool B[6][4]; //returns whether the axes match (i.e. if 40 along the source edge corresponds to 40 or 10 along the target edge
int realX[6];
int realY[6];

void walk1(int x, int y, int facing) {
	int i = 0;
	while (i < instructions.size()) {
		//cout << x <<  ", " << y << endl;
		int n = instructions[i] - '0';
		i++;
		while (i < instructions.size() && instructions[i] < 60) {
			n = (n * 10) + instructions[i] - '0';
			i++;
		}
		if (facing == 0) {//right
			for (int j = 0; j < n; j++) {
				if (M[x][y + 1] == '.') {
					y++;
				}
				else if (M[x][y + 1] == '#') {
					break;
				}
				else {
					int k = 0;
					while (M[x][k] == ' ') {
						k++;
					}
					if (M[x][k] == '#') {
						break;
					}
					else {
						y = k;
					}
				}
			}
		}
		else if (facing == 1) {//down
			for (int j = 0; j < n; j++) {
				if (M[x + 1][y] == '.') {
					x++;
				}
				else if (M[x + 1][y] == '#') {
					break;
				}
				else {
					int k = 0;
					while (M[k][y] == ' ') {
						k++;
					}
					if (M[k][y] == '#') {
						break;
					}
					else {
						x = k;
					}
				}
			}
		}
		else if (facing == 2) {//left
			for (int j = 0; j < n; j++) {
				if (M[x][y - 1] == '.') {
					y--;
				}
				else if (M[x][y - 1] == '#') {
					break;
				}
				else {
					int k = 200;
					while (M[x][k] == ' ') {
						k--;
					}
					if (M[x][k] == '#') {
						break;
					}
					else {
						y = k;
					}
				}
			}
		}
		else { //up
			for (int j = 0; j < n; j++) {
				if (M[x - 1][y] == '.') {
					x--;
				}
				else if (M[x - 1][y] == '#') {
					break;
				}
				else {
					int k = 200;
					while (M[k][y] == ' ') {
						k--;
					}
					if (M[k][y] == '#') {
						break;
					}
					else {
						x = k;
					}
				}
			}
		}
		if (i < instructions.size()) {
			if (instructions[i] == 'L') {
				facing--;
				if (facing < 0) {
					facing = 3;
				}
			}
			else {
				facing = (facing + 1) % 4;
			}
			i++;
		}
	}
	cout << "The password for part 1 is " << (1000 * x) + (4 * y) + facing << endl;
}

bool check(int facing, int side, int amount) {
	int newside = T[side][facing];
	int newfacing = F[side][facing];
	bool b = B[side][facing];
	if (!b) {
		amount = 49 - amount;
	}
	
	if (newfacing == 0) {
		return (C[newside][amount][0] == '.');
	}
	else if (newfacing == 1) {
		return (C[newside][0][amount] == '.');
	}
	else if (newfacing == 2) {
		return (C[newside][amount][49] == '.');
	}
	else {
		return (C[newside][49][amount] == '.');
	}

}

void transition(int& x, int& y, int& facing, int& side, int amount) {
	int newside = T[side][facing];
	int newfacing = F[side][facing];
	bool b = B[side][facing];
	if (newfacing % 2 == 0) {
		if (newfacing == 0) {
			y = 0;
		}
		else {
			y = 49;
		}
		if (b) {
			x = amount;
		}
		else{
			x = 49 - amount;
		}
	}
	else {
		if (newfacing == 1) {
			x = 0;
		}
		else {
			x = 49;
		}
		if (b) {
			y = amount;
		}
		else {
			y = 49 - amount;
		}
	}
	side = newside;
	facing = newfacing;
	return;
}

void walk2(int x, int y, int facing, int side) {
	int i = 0;
	while (i < instructions.size()) {
		int n = instructions[i] - '0';
		i++;
		while (i < instructions.size() && instructions[i] < 60) {
			n = (n * 10) + instructions[i] - '0';
			i++;
		}
		//cout << endl << side << ": " << x << ", " << y << ". Facing: " << facing << ". Movement " << n <<  endl;
		for (int j = 0; j < n; j++) {
			//cout << side << ": " << x << ", " << y << endl;
			if (facing == 0) {//right
				if (y == 49) {
					if (check(facing, side, x)) {
						transition(x, y, facing, side, x);
					}
					else {
						break;
					}
				}
				else if (C[side][x][y + 1] == '.') {
					y++;
				}
				else {
					break;
				}
			}
			else if (facing == 1) {//down
				if (x == 49) {
					if (check(facing, side, y)) {
						transition(x, y, facing, side, y);
					}
					else {
						break;
					}
				}
				else if (C[side][x + 1][y] == '.') {
					x++;
				}
				else {
					break;
				}
			}
		
			else if (facing == 2) {//left

				if (y == 0) {
					if (check(facing, side, x)) {
						transition(x, y, facing, side, x);
					}
					else {
						break;
					}
				}
				else if (C[side][x][y - 1] == '.') {
					y--;
				}
				else {
					break;
				}
			}
			else { //up
				if (x == 0) {
					if (check(facing, side, y)) {
						transition(x, y, facing, side, y);
					}
					else {
						break;
					}
				}
				else if (C[side][x - 1][y] == '.') {
					x--;
				}
				else {
					break;
				}
			}
		}

		if (i < instructions.size()) {
			if (instructions[i] == 'L') {
				facing--;
				if (facing < 0) {
					facing = 3;
				}
			}
			else {
				facing = (facing + 1) % 4;
			}
			i++;
		}
	}
	cout << "The password for part 2 is " << (1000 * (x + realX[side])) + (4 * (y + realY[side])) + facing << endl;
}


void setup() {

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			C[0][i][j] = M[i + 1][j + 51];		//A
			C[1][i][j] = M[i + 1][j + 101];		//B
			C[2][i][j] = M[i + 51][j + 51];		//C
			C[3][i][j] = M[i + 101][j + 51];	//D
			C[4][i][j] = M[i + 101][j + 1];		//E
			C[5][i][j] = M[i + 151][j + 1];		//F
		}
	}



	realX[0] = 1;
	realX[1] = 1;
	realX[2] = 51;
	realX[3] = 101;
	realX[4] = 101;
	realX[5] = 151;

	realY[0] = 51;
	realY[1] = 101;
	realY[2] = 51;
	realY[3] = 51;
	realY[4] = 1;
	realY[5] = 1;

	F[0][0] = 0;
	F[0][1] = 1;
	F[0][2] = 0;
	F[0][3] = 0;

	F[1][0] = 2;
	F[1][1] = 2;
	F[1][2] = 2;
	F[1][3] = 3;

	F[2][0] = 3;
	F[2][1] = 1;
	F[2][2] = 1;
	F[2][3] = 3;

	F[3][0] = 2;
	F[3][1] = 2;
	F[3][2] = 2;
	F[3][3] = 3;

	F[4][0] = 0;
	F[4][1] = 1;
	F[4][2] = 0;
	F[4][3] = 0;

	F[5][0] = 3;
	F[5][1] = 1;
	F[5][2] = 1;
	F[5][3] = 3;


	T[0][0] = 1;
	T[0][1] = 2;
	T[0][2] = 4;
	T[0][3] = 5;

	T[1][0] = 3;
	T[1][1] = 2;
	T[1][2] = 0;
	T[1][3] = 5;

	T[2][0] = 1;
	T[2][1] = 3;
	T[2][2] = 4;
	T[2][3] = 0;

	T[3][0] = 1;
	T[3][1] = 5;
	T[3][2] = 4;
	T[3][3] = 2;

	T[4][0] = 3;
	T[4][1] = 5;
	T[4][2] = 0;
	T[4][3] = 2;

	T[5][0] = 3;
	T[5][1] = 1;
	T[5][2] = 0;
	T[5][3] = 4;


	B[0][0] = true;
	B[0][1] = true;
	B[0][2] = false;
	B[0][3] = true;

	B[1][0] = false;
	B[1][1] = true;
	B[1][2] = true;
	B[1][3] = true;

	B[2][0] = true;
	B[2][1] = true;
	B[2][2] = true;
	B[2][3] = true;

	B[3][0] = false;
	B[3][1] = true;
	B[3][2] = true;
	B[3][3] = true;

	B[4][0] = true;
	B[4][1] = true;
	B[4][2] = false;
	B[4][3] = true;

	B[5][0] = true;
	B[5][1] = true;
	B[5][2] = true;
	B[5][3] = true;
	return;
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			M[i][j] = ' ';
		}
	}

	string s;
	ifstream f("data.txt");
	getline(f, s);
	int x = 1;
	while (!s.empty()) {
		for (int y = 0; y < s.size(); y++) {
			M[x][y + 1] = s[y];
		}
		x++;
		getline(f, s);
	}
	int y = 0;
	while (M[1][y] != '.') {
		y++;
	}
	getline(f, instructions);
	walk1(1, y, 0);

	setup();
	walk2(0, 0, 0, 0);
	return 0;
}