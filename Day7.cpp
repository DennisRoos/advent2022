
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

class file {
public:
	string name;
	int size = 0;
};

class directory {
public: 
	string name;
	directory* parent;
	vector<directory*> subs;
	vector<file*> files;
	int size;
	directory(string s, directory* p) {
		name = s;
		parent = p;
		size = 0;
	}
};

directory* root;
int total1;
int smallestsize;
int target;


int findsize(directory* d) {
	for (int i = 0; i < d->subs.size(); i++) {
		d->size += findsize(d->subs[i]);
	}
	for (int i = 0; i < d->files.size(); i++) {
		d->size += d->files[i]->size;
	}
	int n = d->size;
	if (n <= 100000) {
		total1 += n;
	}
	return d->size;
}

void findbest(directory* d) {
	for (int i = 0; i < d->subs.size(); i++) {
		findbest(d->subs[i]);
	}
	int n = d->size;
	if (n >= target && n < smallestsize) {
		smallestsize = n;
	}
}


int main(int argc, char* argv[]) {
	total1 = 0;
	string s;
	ifstream infile;
	infile.open("data.txt");
	root = new directory("/", NULL);
	directory* current = NULL;
	if (infile.is_open()) {
		while (infile >> s) {
			if (s.compare("$") == 0) {//command
				infile >> s;
				if (s.compare("cd") == 0) {//cd
					infile >> s;
					if (s.compare("/") == 0) {
						current = root;
					}
					else if(s.compare("..") == 0) {
						current = current->parent;
					}
					else {//subdirectory
						for (int i = 0; i < current->subs.size(); i++) {
							if (current->subs[i]->name.compare(s) == 0) {
								current = current->subs[i];
							}
						}
					}
				}
			}
			else {//directory or file
				if (s.compare("dir") == 0) {//new directory
					infile >> s;
					directory* d = new directory(s, current);
					current->subs.push_back(d);
				}
				else {
					file* f = new file();
					f->size = stoi(s);
					infile >> s;
					f->name = s;
					current->files.push_back(f);
				}
			}
		}
		findsize(root);
		cout << "The total size of the smaller directories is " << total1 << endl;
		smallestsize = root->size;
		int freespace = 70000000 - smallestsize;
		target = 30000000 - freespace;
		findbest(root);
		cout << "The size of the directory to be deleted is " << smallestsize << endl;


	}
}