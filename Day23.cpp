
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

struct elf {
	int x;
	int y;
	bool proposing;
	int px;
	int py;
};

vector<elf*> v;
int elfcount;
char M[1000][1000];
int direction;// 0 is North, 1 is South, 2 is West, 3 is East

bool propose(elf* e, int d) {
	int x = e->x;
	int y = e->y;
	if (d == 0) {
		if (M[x - 1][y - 1] == '.' && M[x - 1][y] == '.' && M[x - 1][y + 1] == '.') {
			e->proposing = true;
			e->px = x - 1;
			e->py = y;
			return true;
		}
	}
	else if (d == 1) {
		if (M[x + 1][y - 1] == '.' && M[x + 1][y] == '.' && M[x + 1][y + 1] == '.') {
			e->proposing = true;
			e->px = x + 1;
			e->py = y;
			return true;
		}
	}
	else if (d == 2) {
		if (M[x - 1][y - 1] == '.' && M[x][y - 1] == '.' && M[x + 1][y - 1] == '.') {
			e->proposing = true;
			e->px = x;
			e->py = y - 1;
			return true;
		}
	}
	else if (d == 3) {
		if (M[x - 1][y + 1] == '.' && M[x][y + 1] == '.' && M[x + 1][y + 1] == '.') {
			e->proposing = true;
			e->px = x;
			e->py = y + 1;
			return true;
		}
	}
	return false;
}

int rectangle() {
	int xmin = 9999;
	int xmax = 0;
	int ymin = 9999;
	int ymax = 0;
	for (int i = 0; i < elfcount; i++) {
		if (xmin > v[i]->x) {
			xmin = v[i]->x;
		}
		if (xmax < v[i]->x) {
			xmax = v[i]->x;
		}
		if (ymin > v[i]->y) {
			ymin = v[i]->y;
		}
		if (ymax < v[i]->y) {
			ymax = v[i]->y;
		}
	}
	int xrange = xmax - xmin + 1;
	int yrange = ymax - ymin + 1;
	cout << xmin << "-" << xmax << " , " << ymin << "-" << ymax << endl;
	return xrange * yrange - elfcount;
}

bool round() {
	bool moved = false;
	for (int i = 0; i < elfcount; i++) {
		v[i]->proposing = false;
		int x = v[i]->x;
		int y = v[i]->y;
		if (M[x - 1][y - 1] == '#' || M[x - 1][y] == '#' || M[x - 1][y + 1] == '#' ||
			M[x][y - 1] == '#' || M[x][y + 1] == '#' ||
			M[x + 1][y - 1] == '#' || M[x + 1][y] == '#' || M[x + 1][y + 1] == '#') {
			int d = direction;
			for (int j = 0; j < 4; j++) {
				bool b = propose(v[i], d);
				d = (d + 1) % 4;
				if (b) {
					break;
				}
			}
		}
	}
	for (int k = 0; k < elfcount; k++) {
		if (v[k]->proposing) {
			for (int l = k + 1; l < elfcount; l++) {
				if (v[l]->proposing && v[k]->px == v[l]->px && v[k]->py == v[l]->py) {
					v[k]->proposing = false;
					v[l]->proposing = false;
				}
			}
		}
	}

	for (int k = 0; k < elfcount; k++) {
		if (v[k]->proposing) {
			M[v[k]->x][v[k]->y] = '.';
			v[k]->x = v[k]->px;
			v[k]->y = v[k]->py;
			M[v[k]->x][v[k]->y] = '#';
			moved = true;
		}
	}
	direction = (direction + 1) % 4;
	return moved;
}

int main(int argc, char* argv[]) {
	direction = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			M[i][j] = '.';
		}
	}

	string s;
	ifstream f("data.txt");
	int x = 0;
	while (getline(f, s)) {
		for (int y = 0; y < s.size(); y++) {
			if (s[y] == '#') {
				elf* e = new elf();
				e->x = x + 500;
				e->y = y + 500;
				v.push_back(e);
				M[x + 500][y + 500] = '#';
			}
		}
		x++;
	}
	elfcount = v.size();
	int rounds;
	for (rounds = 0; rounds < 10; rounds++) {
		/*for (int i = 475; i < 525; i++) {
			for (int j = 475; j < 525; j++) {
				cout << M[i][j];
			}
			cout << endl;
		}
		cout << endl;*/
		round();
	}

	/*for (int i = 475; i < 525; i++) {
		for (int j = 475; j < 525; j++) {
			cout << M[i][j];
		}
		cout << endl;
	}*/

	int emptycount = rectangle();
	cout << "After 10 rounds there were " << emptycount << " empty tiles" << endl;
	bool b = true;
	while (b) {
		b = round();
		rounds++;
	}
	cout << "The elves stop moving after round " << rounds << endl;
	emptycount = rectangle();
	return 0;
}