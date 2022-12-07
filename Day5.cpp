
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

class node {
public: 
	node* next;
	char value;
	node(char c) {
		next = NULL;
		value = c;
	}
};

node* S[10];

void insert(node* start, node* n) {
	node* t = start;
	while (t->next != NULL) {
		t = t->next;
	}
	t->next = n;
	return;
}

string s;
ifstream f("data.txt");

void move1(){
	getline(f, s);
	regex re("move ([\\d]+) from ([\\d]+) to ([\\d]+)");
	smatch match;
	while (getline(f, s)) {
		if (regex_search(s, match, re) == true) {
			int amount = stoi(match.str(1));
			int source = stoi(match.str(2));
			int target = stoi(match.str(3));
			for (int i = 0; i < amount; i++) {
				node* n = S[source];
				S[source] = n->next;
				n->next = S[target];
				S[target] = n;
			}
		}
	}
	return;
}

void move2() {
	getline(f, s);
	regex re("move ([\\d]+) from ([\\d]+) to ([\\d]+)");
	smatch match;
	while (getline(f, s)) {
		if (regex_search(s, match, re) == true) {
			int amount = stoi(match.str(1));
			int source = stoi(match.str(2));
			int target = stoi(match.str(3));
			node* n = S[source];
			node* m = n;
			for (int i = 1; i < amount; i++) {
				m = m->next;
			}
			S[source] = m->next;
			m->next = S[target];
			S[target] = n;
		}
	}
	return;

}

int main(int argc, char* argv[]) {
	for (int i = 0; i < 10; i++) {
		S[i] = NULL;
	}
	getline(f, s);
	while (s[1] > 64) {
		int i = 1;
		int j = 1;
		while (i < s.size()) {
			if (s[i] != ' ') {
				node* n = new node(s[i]);
				if (S[j] == NULL) {
					S[j] = n;
				}
				else {
					insert(S[j], n);
				}
			}
			j++;
			i += 4;
		}
		getline(f, s);
	}
	cout << "Everything inserted" << endl;
	//move1();
	move2();
	for (int i = 1; i < 10; i++) {
		cout << S[i]->value;
	}

	cout << endl;


	return 0;
}