
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

int lava[25][25][25];// 0 represents (internal) air, 1 is lava, 2 is air exposed to the exterior (steam)

void map() {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			lava[0][i][j] = 2;
			lava[24][i][j] = 2;
			lava[i][0][j] = 2;
			lava[i][24][j] = 2;
			lava[i][j][0] = 2;
			lava[i][j][24] = 2;
		}
	}
	bool changed = true;
	while (changed) {
		changed = false;
		for (int i = 1; i < 24; i++) {
			for (int j = 1; j < 24; j++) {
				for (int k = 1; k < 24; k++) {
					if (lava[i][j][k] == 0) {
						if (lava[i - 1][j][k] == 2 || lava[i + 1][j][k] == 2 ||
							lava[i][j - 1][k] == 2 || lava[i][j + 1][k] == 2 ||
							lava[i][j][k - 1] == 2 || lava[i][j][k + 1] == 2) {
							lava[i][j][k] = 2;
							changed = true;
						}
					}
				}
			}
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	int sides1 = 0;
	int sides2 = 0;

	regex re("([\\d]+),([\\d]+),([\\d]+)");
	string s;
	smatch match;
	ifstream infile;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			for (int k = 0; k < 25; k++) {

				lava[i][j][k] = 0;
			}
		}
	}
	infile.open("data.txt");
	if (infile.is_open()) {
		while (infile >> s) {
			if (regex_search(s, match, re) == true) {
				int x = stoi(match.str(1));
				int y = stoi(match.str(2));
				int z = stoi(match.str(3));
				lava[x+1][y+1][z+1] = 1;
			}
		}
	}

	map();
	for (int i = 1; i < 24; i++) {
		for (int j = 1; j < 24; j++) {
			for (int k = 1; k < 24; k++) {
				if (lava[i][j][k] == 1) {

					
					if (lava[i + 1][j][k] != 1) {
						if (lava[i + 1][j][k] == 2) {
							sides2++;
						}
						sides1++;
					}
					if (lava[i - 1][j][k] != 1) {
						if (lava[i - 1][j][k] == 2) {
							sides2++;
						}
						sides1++;
					}
					if (lava[i][j + 1][k] != 1) {
						if (lava[i][j + 1][k] == 2) {
							sides2++;
						}
						sides1++;
					}
					if (lava[i][j - 1][k] != 1) {
						if (lava[i][j - 1][k] == 2) {
							sides2++;
						}
						sides1++;
					}
					if (lava[i][j][k + 1] != 1) {
						if (lava[i][j][k + 1] == 2) {
							sides2++;
						}
						sides1++;
					}
					if (lava[i][j][k - 1] != 1) {
						if (lava[i][j][k - 1] == 2) {
							sides2++;
						}
						sides1++;
					}
				}
			}
		}
	}
	cout << "The surface area is " << sides1 << endl;
	cout << "The exterior surface area is " << sides2 << endl;


}