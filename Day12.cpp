
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

char H[100][200];
int L[100][200];
int height;
int width;
int sx;
int sy;
int ex;
int ey;

void move(int x, int y, int l) {
	if (l < L[x][y]) {
		L[x][y] = l;
	}
	else {
		return;
	}

	if (x == sx && y == sy) {
		return;
	}
	char c = H[x][y];
	if (x > 0) {
		if (H[x - 1][y] >= c - 1) {
			move(x - 1, y, l + 1);
		}
	}
	if (x < height - 1) {
		if (H[x + 1][y] >= c - 1) {
			move(x + 1, y, l + 1);
		}
	}
	if (y > 0) {
		if (H[x][y - 1] >= c - 1) {
			move(x, y - 1, l + 1);
		}
	}
	if (y < width - 1) {
		if (H[x][y + 1] >= c - 1) {
			move(x, y + 1, l + 1);
		}
	}
	return;
}


int main(int argc, char* argv[]) {

	string s;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open()) {
		height = 0;
		while (infile >> s) {
			for (int j = 0; j < s.size(); j++) {
				if (s[j] == 'S') {
					sx = height;
					sy = j;
					H[height][j] = 'a';
				}
				else if (s[j] == 'E') {
					ex = height;
					ey = j;
					H[height][j] = 'z';
				}
				else {
					H[height][j] = s[j];
				}
			}
			height++;
		}

		width = s.size();
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				L[i][j] = 999999;
			}
		}
		move(ex, ey, 0);
		cout << "The end was " << L[sx][sy] << " steps away from the start" << endl;
		int best = 9999;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (H[i][j] == 'a' && L[i][j] < best) {
					best = L[i][j];
				}
			}
		}
		cout << "The shortest path from any low point was " << best << endl;
	}

}