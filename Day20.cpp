
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

struct node {
	long long value;
	node* prev;
	node* next;
};

node* first;
vector<node*> v;
int listsize;

void mix() {
	node* current;
	/*cout << first->value;
	current = first->next;
	while (current != first) {
		cout << ", " << current->value;
		current = current->next;
	}
	cout << endl;*/
	for (int i = 0; i < listsize; i++) {
		long long n = v[i]->value;
		current = v[i];
		if (n < 0) {
			long long m = -1 * n;
			m = m % (listsize - 1);
			n = (listsize - m) - 1;
		}
		else {
			n = n % (listsize - 1);
		}
		for (int j = 0; j < n; j++) {
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current->prev = current->next;
			current->next = current->next->next;
			current->next->prev = current;
			current->prev->next = current;
		}
	}
	return;
}

int main(int argc, char* argv[]) {

	long long n;
	ifstream infile;
	node* current = NULL;
	infile.open("data.txt");
	if (infile.is_open()) {
		infile >> n;
		n *= 811589153; //comment out this line for part 1
		first = new node();
		first->value = n;
		v.push_back(first);
		current = first;
		while (infile >> n) {
			node* element = new node();
			v.push_back(element);
			n *= 811589153; //comment out this line for part 1
			element->value = n;
			current->next = element;
			element->prev = current;
			current = element;
		}
		first->prev = current;
		current->next = first;
	}
	listsize = v.size();
	for (int i = 0; i < 10; i++) {
		mix();
	}
	long long total = 0;
	current = first;
	while (current->value != 0) {
		current = current->next;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 1000; j++) {
			current = current->next;
		}
		total += current->value;
	}
	cout << "The grove coordinates are " << total << endl;
}