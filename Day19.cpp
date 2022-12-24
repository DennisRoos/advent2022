
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <map>
using namespace std;

int orecost;
int claycost;
int obsorecost;
int obsclaycost;
int geodeorecost;
int geodeobscost;

int highestore;


int search(char ore, char clay, char obsidian, char orebots, char claybots, char obsbots, char geodebots, char minutes) {
	if (minutes == 1) {
		return geodebots;
	}
	
	bool b = true;
	int best = 0;
	if (ore >= orecost && orebots < highestore) {
		int n = search(ore + orebots - orecost, clay + claybots, obsidian + obsbots, orebots + 1, claybots, obsbots, geodebots, minutes - 1);
		if (n > best) {
			best = n;
		}
		b = false;
	}
	if (ore >= claycost && claybots < obsclaycost) {
		int n = search(ore + orebots - claycost, clay + claybots, obsidian + obsbots, orebots, claybots + 1, obsbots, geodebots, minutes - 1);
		if (n > best) {
			best = n;
		}
		b = false;
	}
	if (ore >= obsorecost && clay >= obsclaycost && obsbots < geodeobscost) {
		int n = search(ore + orebots - obsorecost, clay + claybots - obsclaycost, obsidian + obsbots, orebots, claybots, obsbots + 1, geodebots, minutes - 1);
		if (n > best) {
			best = n;
		}
		b = false;
	}
	if (ore >= geodeorecost && obsidian >= geodeobscost) {
		int n = search(ore + orebots - geodeorecost, clay + claybots, obsidian + obsbots - geodeobscost, orebots, claybots, obsbots, geodebots + 1, minutes - 1);
		if (n > best) {
			best = n;
		}
		b = false;
	}
	if(b){
		int n = search(ore + orebots, clay + claybots, obsidian + obsbots, orebots, claybots, obsbots, geodebots, minutes - 1);
		if (n > best) {
			best = n;
		}
	}
	return best + geodebots;
}

vector<string> v;

int main(int argc, char* argv[]) {
	int total = 0;

	regex re("Blueprint ([\\d]+): Each ore robot costs ([\\d]+) ore. Each clay robot costs ([\\d]+) ore. Each obsidian robot costs ([\\d]+) ore and ([\\d]+) clay. Each geode robot costs ([\\d]+) ore and ([\\d]+) obsidian.");
	string s;
	smatch match;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open()) {
		while (getline(infile,s)) {
			if (regex_search(s, match, re) == true) {
				v.push_back(s);
				int blueprintnr = stoi(match.str(1));
				orecost = stoi(match.str(2));
				claycost = stoi(match.str(3));
				obsorecost = stoi(match.str(4));
				obsclaycost = stoi(match.str(5));
				geodeorecost = stoi(match.str(6));
				geodeobscost = stoi(match.str(7));
				highestore = max(max(orecost - 1, claycost),max( obsorecost, geodeorecost));
				int geodes = search(0, 0, 0, 1, 0, 0, 0, 24);
				total += geodes * blueprintnr;
				cout << "Blueprint " << blueprintnr << " produced " << geodes << " geodes!" << endl;

			}


		}
		cout << "The total quality level is " << total << endl;
		long long total2 = 1;
		for (int i = 0; i < 3; i++) {
			if (regex_search(v[i], match, re) == true) {
				int blueprintnr = stoi(match.str(1));
				orecost = stoi(match.str(2));
				claycost = stoi(match.str(3));
				obsorecost = stoi(match.str(4));
				obsclaycost = stoi(match.str(5));
				geodeorecost = stoi(match.str(6));
				geodeobscost = stoi(match.str(7));
				highestore = max(max(orecost - 1, claycost), max(obsorecost, geodeorecost));
				long long geodes = search(0, 0, 0, 1, 0, 0, 0, 32);
				total2 *= geodes;
				cout << "Blueprint " << blueprintnr << " produced " << geodes << " geodes!" << endl;


			}
		}
		cout << "The total quality level is " << total2 << endl;

	}
}