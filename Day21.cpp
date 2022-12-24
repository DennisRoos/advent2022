#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <map>

#include <cmath>

using namespace std;
map<string, long long> mymap;

struct monkey {
	string name;
	string s1;
	string s2;
	char op;
};

vector<monkey> M;

long long calculate(string s) {
	map<string, long long>::iterator it = mymap.find(s);
	if (it != mymap.end()) {
		return it->second;
	}
	int i = 0;
	while (M[i].name.compare(s) != 0) {
		i++;
	}
	long long n1 = calculate(M[i].s1);
	long long n2 = calculate(M[i].s2);
	long long n;
	if (M[i].op == '+') {
		n = n1 + n2;
	}
	else if (M[i].op == '-') {
		n = n1 - n2;
	}
	else if (M[i].op == '*') {
		n = n1 * n2;
	}
	else {
		n = n1 / n2;
	}
	mymap.insert({ s,n });
	return n;
}

long long search(string s) {
	int i = 0;
	while (M[i].s1.compare(s) != 0 && M[i].s2.compare(s) != 0) {
		i++;
	}
	if (M[i].name.compare("root") == 0) {
		if (M[i].s1.compare(s) == 0) {
			return calculate(M[i].s2);
		}
		else {
			return calculate(M[i].s1);
		}
	}
	else {//not root
		long long n = search(M[i].name);
		if (M[i].s1.compare(s) == 0) {
			long long n2 = calculate(M[i].s2);
			if (M[i].op == '+') {
				return n - n2;
			}
			else if (M[i].op == '-') {
				return n + n2;
			}
			else if (M[i].op == '*') {
				return n / n2;
			}
			else if (M[i].op == '/') {
				return n * n2;
			}
		}
		else {
			long long n2 = calculate(M[i].s1);
			if (M[i].op == '+') {
				return n - n2;
			}
			else if (M[i].op == '-') {
				return n2 - n;
			}
			else if (M[i].op == '*') {
				return n / n2;
			}
			else if (M[i].op == '/') {
				return n2 / n;
			}

		}
	}
}

int main(int argc, char* argv[]) {
	ifstream infile;
	infile.open("data.txt");
	string source;
	string s;
	if (infile.is_open())
	{
		while (infile >> source) {
			source.pop_back();
			infile >> s;
			if (s[0] > 95) { //character
				char op;
				string s2;
				infile >> op;
				infile >> s2;
				monkey m = monkey();
				m.name = source;
				m.s1 = s;
				m.s2 = s2;
				m.op = op;
				M.push_back(m);
			}
			else {
				long long n = stoi(s);
				mymap.insert({ source, n });
			}
		}
		int i = 0;
		long long result = calculate("root");
		cout << "The result of part 1 is " << result << endl;
		long long result2 = search("humn");
		cout << "The result of part 2 is " << result2 << endl;

	}
	return 0;
}