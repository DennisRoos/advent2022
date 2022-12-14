
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

struct node{
	bool l;
	int value;
	node* sublist;
	node* next;
	node(bool ll, int v, node* s) : l(ll), value(v), sublist(s), next(NULL) {};
	~node(){
		if (sublist != NULL) {
			delete sublist;
		}
		if (next != NULL) {
			delete next;
		}
	}

};


int si;

void printe(node* n) {
	cout << '[';
	while (n != NULL) {
		if (n->l) {
			printe(n->sublist);
		}
		else {
			cout << n->value;
		}
		n = n->next;
		if (n != NULL){
			cout << ',';
		}
	}
	cout << ']';
}

node* parse(string s) {
	node* last = NULL;
	node* n;
	node* p = NULL;
	while (s[si] != ']') {
		if (s[si] == ',') {
			si++;
		}
		//cout << "test3 " << si << endl;
		if (s[si] == '[') {//element is list
			si++;
			n = new node(true, -1, parse(s));
		}
		else {
			int v = s[si] - '0';
			si++;
			while (s[si] > 46 && s[si] < 58) {
				int w = (s[si] - '0');
				v = (v * 10) + w;
				si++;
			}
			n = new node(false, v, NULL);
			si--;
		}
		if (p == NULL) {
			p = n;
		}
		else {
			last->next = n;
		}
		last = n;
		si++;
	}
	if (s[si] == ',') {
		si++;
	}
	//cout << "Done with parsing " << s << " at index " << si << endl;
	return p;
}


int compare(node* c1, node* c2) {
	int b = 2;// 0 is out of order, 1 is correct, 2 is indecisive
	while (b == 2) {
		if (c1 == NULL) {
			if (c2 == NULL) {
				return 2;
			}
			else {
				return 1;

			}
		}
		else if (c2 == NULL) {
			return 0;
		}
		else if (c1->l) {//c1 is a list
			if (c2->l) {//both are lists
				b = compare(c1->sublist, c2->sublist);
			}
			else {//c1 is a list, c2 is an integer
				node* n = new node(false, c2->value, NULL);
				c2->l = true;
				c2->value = -1;
				c2->sublist = n;
				b = compare(c1->sublist, c2->sublist);
			}
		}
		else {
			if (c2->l) {//c1 is an integer, c2 is a list
				node* n = new node(false, c1->value, NULL);
				c1->l = true;
				c1->value = -1;
				c1->sublist = n;
				b = compare(c1->sublist, c2->sublist);

			}
			else {//both are integers
				if (c1->value < c2->value) {

					return 1;
				}
				else if(c1->value > c2->value){
					return 0;
				}
				else { 
					b = 2; 
				}
			}
		}
		c1 = c1->next;
		c2 = c2->next;
	}
	return b;
}

bool gate(string s1, string s2) {
	si = 1;
	node* n1 = parse(s1);
	si = 1;
	node* n2 = parse(s2);
	int b = compare(n1, n2);
	delete n1;
	delete n2;
	if (b != 0) {
		return true;
	}
	else{
		return false;
	}
}


vector<string> v;


int main(int argc, char* argv[]) {
	int index = 1;
	int total = 0;
	string s;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open()) {
		while (infile >> s) {
			v.push_back(s);
			si = 1;
			node* p1 = parse(s);
			infile >> s;
			v.push_back(s);
			si = 1;
			node* p2 = parse(s);

			int b = compare(p1, p2);

			if (b == 1) {
				//cout << "index " << index << " is true" << endl;
				total += index;
			}

			index++;
		}
		cout << "The total of the correct indices is " << total << endl;


		v.push_back("[[2]]");
		v.push_back("[[6]]");
		sort(v.begin(), v.end(), gate);
		//Quicksort(0, v.size() - 1);

		int d1;
		int d2;
		for (int i = 0; i < v.size(); i++) {
			//cout << v[i] << endl;
			if (v[i].compare("[[2]]") == 0) {
				d1 = i + 1;
			}
			if (v[i].compare("[[6]]") == 0) {
				d2 = i + 1;
			}
		}
		cout << "The decoder keys are " << d1 << " and " << d2 << ". Their product is " << d1 * d2 << endl;
	}
}