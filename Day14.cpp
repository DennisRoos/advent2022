
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

char M[1000][200];

int sand;
bool done;

void movesand(int x, int y) {
	if (y == 200) {
		done = true;
		return;
	}
	while (done == false) {
		if (M[x][y + 1] == '.') {
			movesand(x, y + 1);
		}
		else if (M[x - 1][y + 1] == '.') {
			movesand(x - 1, y + 1);
		}
		else if (M[x + 1][y + 1] == '.') {
			movesand(x + 1, y + 1);
		}
		else {
			sand++;
			M[x][y] = 'o';
			return;
		}
	}
}

int main(int argc, char* argv[]) {

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 200; j++) {
			M[i][j] = '.';
		}
	}
	int x1;
	int y1;
	int x2;
	int y2;
	int highesty;
	sand = 0;
	done = false;
	string s;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open()) {
		infile >> x1;
		infile >> y1;
		highesty = y1;
		while (infile >> s) {
			if (s.compare("->") == 0) {
				infile >> x2;
				infile >> y2;
				if (y2 > highesty) {
					highesty = y2;
				}
				if (x1 == x2) {
					if (y1 < y2) {
						for (int i = y1; i < y2 + 1; i++) {
							M[x1][i] = '#';
						}
					}
					else {
						for (int i = y2; i < y1 + 1; i++) {
							M[x1][i] = '#';
						}
					}
				}
				else {
					if (x1 < x2) {
						for (int i = x1; i < x2 + 1; i++) {
							M[i][y1] = '#';
						}
					}
					else {
						for (int i = x2; i < x1 + 1; i++) {
							M[i][y1] = '#';
						}
					}

				}
				x1 = x2;
				y1 = y2;
			}
			else {
				x1 = stoi(s);
				infile >> y1;
			}

		}
		for (int i = 0; i < 1000; i++) {
			M[i][highesty + 2] = '#';
		}

		movesand(500, 0);
		cout << "There were " << sand << " tiles of resting sand" << endl;


	}

}