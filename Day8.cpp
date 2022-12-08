
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

int H[100][100];
bool V[100][100];


int w;

int scenicscore(int i, int j) {
	if (i == 0 || j == 0 || i == w - 1 || j == w - 1) {
		return 0;
	}
	int score = 1;
	int count = 0;
	int h = H[i][j];
	for (int k = i - 1; k >= 0; k--) {
		if (H[k][j] < h) {
			count++;
		}
		else {
			count++;
			break;
		}
	}
	score *= count;
	count = 0;
	for (int k = i + 1; k < w; k++) {
		if (H[k][j] < h) {
			count++;
		}
		else {
			count++;
			break;
		}
	}
	score *= count;
	count = 0;
	for (int k = j - 1; k >= 0; k--) {
		if (H[i][k] < h) {
			count++;
		}
		else {
			count++;
			break;
		}
	}
	score *= count;
	count = 0;
	for (int k = j + 1; k < w; k++) {
		if (H[i][k] < h) {
			count++;
		}
		else {
			count++;
			break;
		}
	}
	score *= count;
	return score;
}

int main(int argc, char* argv[]) {
	string s;
	w = 99;
	ifstream f("data.txt");
	int i = 0;
	while (getline(f, s)) {
		for (int j = 0; j < w; j++) {
			H[i][j] = s[j] - '0';
			V[i][j] = false;
		}
		i++;
	}
	for (int i = 0; i < w; i++) {
		int h = -1;
		for (int j = 0; j < w; j++) {
			if (H[i][j] > h) {
				h = H[i][j];
				V[i][j] = true;
			}
			if (h == 9) {
				break;
			}
		}
		h = -1;
		for (int j = w - 1; j >= 0; j--) {
			if (H[i][j] > h) {
				h = H[i][j];
				V[i][j] = true;
			}
			if (h == 9) {
				break;
			}
		}
	}


	for (int i = 0; i < w; i++) {
		int h = -1;
		for (int j = 0; j < w; j++) {
			if (H[j][i] > h) {
				h = H[j][i];
				V[j][i] = true;
			}
			if (h == 9) {
				break;
			}
		}
		h = -1;
		for (int j = w - 1; j >= 0; j--) {
			if (H[j][i] > h) {
				h = H[j][i];
				V[j][i] = true;
			}
			if (h == 9) {
				break;
			}
		}
	}
	int best = 0;
	int total = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			if (V[i][j]) {
				total++;
			}
			int score = scenicscore(i, j);
			if (score > best) {
				best = score;
			}
		}
	}
	cout << "The amount of trees visible is " << total << endl;
	cout << "The best scenic score is " << best << endl;
	return 0;
}