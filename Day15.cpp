
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include <cmath>

using namespace std;

struct range {
	int a;
	int b;
	range(int aa, int bb) : a(aa), b(bb) {}
};

vector<range> v;

struct sensor {
	int x;
	int y;
	int dist;
	sensor(int xx, int yy, int d) : x(xx), y(yy), dist(d) {}
};


struct beacon {
	int x;
	int y;
	beacon(int aa, int bb) : x(aa), y(bb) {}
};

struct less_than_angle
{
	inline bool operator() (const range& a1, const range& a2)
	{
		return (a1.a < a2.a);
	}
};

vector<sensor*> sensors;
vector<beacon*> beacons;

void addbeacon(beacon* b) {
	for (int i = 0; i < beacons.size(); i++) {
		if (beacons[i]->x == b->x && beacons[i]->y == b->y) {
			delete b;
			return;
		}
	}
	beacons.push_back(b);
}

int manhattan(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void openspace(int y) {
	vector<range> v;
	for (int i = 0; i < sensors.size(); i++) {
		int d = abs(sensors[i]->y - y);
		if (d <= sensors[i]->dist) {//y is in sensor range
			int a = sensors[i]->x - (sensors[i]->dist - d);
			int b = sensors[i]->x + (sensors[i]->dist - d);
			range r = range(a, b);
			v.push_back(r);
		}
	}
	sort(v.begin(), v.end(), less_than_angle());
	int total = 0;
	int n = v[0].a;

	for (int i = 0; i < v.size(); i++) {
		if (n < v[i].a) {
			total += (abs(v[i].a - n));
			long long x = v[i].a - 1;
			long long yy = y;
			long long product = (x * 4000000) + y;
			cout << "x = " << v[i].a - 1 << ", y = " << y << ". The tuning frequency is " << product << endl;
			exit(0);
			n = v[i].b + 1;
		}
		else if (n <= v[i].b) {
			n = v[i].b + 1;
		}
	}
	return;
}

int count(int y) {
	vector<range> v;
	for (int i = 0; i < sensors.size(); i++) {
		int d = abs(sensors[i]->y - y);
		if (d <= sensors[i]->dist) {//y is in sensor range
			int a = sensors[i]->x - (sensors[i]->dist - d);
			int b = sensors[i]->x + (sensors[i]->dist - d);
			range r = range(a, b);
			v.push_back(r);
		}
	}
	sort(v.begin(), v.end(), less_than_angle());
	int total = 0;
	int n = v[0].a;

	for (int i = 0; i < v.size(); i++) {
		if (n < v[i].a) {
			total += (abs(v[i].a - n));
			long long x = v[i].a - 1;
			long long yy = y;
			long long product = (x * 4000000) + yy;
			cout << "x = " << x << ", y = " << y << ". The tuning frequency is " << product << endl;
			exit(0);
			n = v[i].b + 1;
		}
		else if (n <= v[i].b) {
			n = v[i].b + 1;
		}
	}

	int r = n - v[0].a;
	int open = r - total;
	for (int i = 0; i < beacons.size(); i++) {
		if (beacons[i]->y == y) {
			open--;
		}
	}
	return open;
}

int main(int argc, char* argv[]) {

	regex re("Sensor at x=([-]?[\\d]+), y=([-]?[\\d]+): closest beacon is at x=([-]?[\\d]+), y=([-]?[\\d]+)");
	string s;
	smatch match;
	ifstream f("data.txt");
	while (getline(f, s)) {
		if (regex_search(s, match, re) == true) {
			int x1 = stoi(match.str(1));
			int y1 = stoi(match.str(2));
			int x2 = stoi(match.str(3));
			int y2 = stoi(match.str(4));
			int d = manhattan(x1, y1, x2, y2);
			sensor* sen = new sensor(x1, y1, d);
			sensors.push_back(sen);
			beacon* b = new beacon(x2, y2);
			addbeacon(b);

		}
	}
	int open = count(2000000);
	cout << "There are " << open << " spaces at y=2000000" << endl;

	for (int i = 0; i < 4000000; i++) {
		openspace(i);
	}
	return 0;
}