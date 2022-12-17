
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

struct valve {
	string name;
	int pressure;
};

vector<valve> v;

int addvalve(string name) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].name.compare(name) == 0) {
			return i;
		}
	}
	valve va = valve();
	va.name = name;
	v.push_back(va);
	return v.size() - 1;
}

bool checked[60];
int dist[60][60];
int valvenumber;

vector<int> useful;

void map() {
	bool changed = true;
	while (changed) {
		changed = false;
		for (int i = 0; i < valvenumber; i++) {
			for (int j = i + 1; j < valvenumber; j++) {
				for (int k = 0; k < valvenumber; k++) {
					int d = dist[i][k] + dist[k][j];
					if (dist[i][j] > d) {
						dist[i][j] = d;
						dist[j][i] = d;
						changed = true;
					}
				}
			}
		}
	}
	return;
}

int search(int k, int minutes, int pressure, bool elephant) {
	pressure += minutes * v[k].pressure;
	int best = pressure;
	for (int i = 0; i < useful.size(); i++) {
		int tar = useful[i];
		int d = dist[k][tar] + 1;
		if (!checked[tar] && d < minutes) {//there's a point in even trying to go for this valve
			checked[tar] = true;
			int p = search(tar, minutes - d, pressure, elephant);
			if (p > best) {
				best = p;
			}
			if (elephant) {//send in the elephant
				p = pressure + ((minutes - d) * v[tar].pressure) + search(0, 26, 0, false);
				if (p > best) {
					best = p;
				}
			}
			checked[tar] = false;
		}
	}
	return best;
}

int main(int argc, char* argv[]) {

	regex re("rate=([\\d]+);");
	string s;
	smatch match;
	ifstream infile;
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 60; j++) {
			dist[i][j] = 99999;
		}
	}
	infile.open("data.txt");
	if (infile.is_open()) {
		string t;
		string name;
		infile >> t;
		while (infile >> name) {
			infile >> t;
			infile >> t;
			infile >> t;
			int nr;
			if (regex_search(t, match, re) == true) {
				int p = stoi(match.str(1));
				nr = addvalve(name);
				v[nr].pressure = p;
				if (p > 0) {
					useful.push_back(nr);
				}
				checked[nr] = false;
			}
			infile >> t;
			infile >> t;
			infile >> t;
			infile >> t;
			infile >> t;
			while (t.compare("Valve") != 0) {
				int tar = addvalve(t);
				dist[nr][tar] = 1;
				infile >> t;
			}
		}
		valvenumber = v.size();
		map();
		for(int i = 0; i < valvenumber; i++){
			cout << v[i].name << ":  ";
			for (int j = 0; j < valvenumber; j++) {
				cout << dist[i][j] << ", ";
			}
			cout << endl;
		}
		int best = search(0, 30, 0, false);
		cout << "The most pressure we can vent on out own is " << best << endl;

		best = search(0, 26, 0, true);
		cout << "The most pressure we can vent with the elephant is " << best << endl;

	}
}