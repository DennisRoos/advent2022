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
int width;
int height;
int best;
char M[30][200];
bool Visited[20][150][500];
int goalx;
int goaly;
int offset;


bool safe(int x, int y, int m) {
	m += offset;
	int right = (y + m) % (width);
	int left = y - (m % width);
	if (left < 0) {
		left += width;
	}
	int down = (x + m) % (height); 
	int up = x - (m % height);
	if (up < 0) {
		up += height;
	}
	//cout << x << "," << y << ": " << m << " is ";
	if (M[x][right] == '<') {
		//cout << " Unsafe, right" << endl;
		return false;
	}
	if (M[x][left] == '>') {
		//cout << left << "," << M[x][left];
		//cout << " Unsafe, left" << endl;
		return false;
	}
	if (M[down][y] == '^') {
		//cout << " Unsafe, down" << endl;
		return false;
	}
	if (M[up][y] == 'v') {
		//cout << " Unsafe, up" << endl;
		return false;
	}

	//cout << " Safe!" << endl;
	return true;

}

void clearVisited() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 150; j++) {
			for (int k = 0; k < 500; k++) {
				Visited[i][j][k] = false;
			}
		}
	}
}

void search(int x, int y, int minutes) {
	if (Visited[x][y][minutes]) {
		return;
	}
	Visited[x][y][minutes] = true;
	if (minutes >= best) {
		return;
	}
	if (x == goalx && y == goaly) {
		//cout << x << ", " << y << ": " << minutes << endl;
		if (minutes < best) {
			best = minutes;
		}
		return;
	}

	//cout << x << ", " << y << " ; " << minutes << endl;

	if (x < height - 1) {
		if (safe(x + 1, y, minutes)) {
			search(x + 1, y, minutes + 1);
		}
	}
	if (y < width - 1) {
		if (safe(x, y + 1, minutes)) {
			search(x, y + 1, minutes + 1);
		}
	}
	if (x > 0) {
		if (safe(x - 1, y, minutes)) {
			search(x - 1, y, minutes + 1);
		}
	}
	if (y > 0) {
		if (safe(x, y - 1, minutes)) {
			search(x, y - 1, minutes + 1);
		}
	}
	if (safe(x, y, minutes)) {
		search(x, y, minutes + 1);
	}
	return;
}

int main(int argc, char * argv[]) {
	string s;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		infile >> s;
		int x = 0;
		while (infile >> s) {
			for (int y = 1; y < s.size() - 1; y++) {
				M[x][y - 1] = s[y];
			}
			x++;
		}
		height = x - 1;
		width = s.size() - 2;
		best = 500;
		goalx = height - 1;
		goaly = width - 1;
		offset = 0;
		clearVisited();
		search(0, 0, 2);
		cout << "The shortest path takes " << best << " minutes." << endl;
		int best1 = best;
		best = 500;
		offset = best1;
		goalx = 0; 
		goaly = 0;
		clearVisited();
		search(height - 1, width - 1, 2);
		cout << "The shortest path back to the start takes " << best << " minutes." << endl;
		int best2 = best;
		offset += best;
		best = 500;
		goalx = height - 1;
		goaly = width - 1;
		clearVisited();
		search(0, 0, 2);
		cout << "The shortest path back to from the start to the peak the second time takes " << best << " minutes." << endl;
		int total = best1 + best2 + best;
		cout << "The trip took " << total << " minutes in total." << endl;


		
	}
	return 0;
}