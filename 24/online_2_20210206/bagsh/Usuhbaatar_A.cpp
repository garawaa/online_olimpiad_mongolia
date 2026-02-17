#include <unordered_map>
#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin;
	fin.open("input.txt");
	
	unordered_map<string, int> m;
	string line, reg = "";

	for (int i = 0; i < 4; i++) {
		int mask = (1 << i);
		getline(fin, line);
		//cout << line << endl;
		for (int j = 0; j < line.size(); j++) {
			if (line[j] == ' ' || line[j] == '\0') {
				if (reg.size() > 0)
					m[reg] |= mask;
				reg = "";
			} else {
				reg = reg + line[j];
			}
		}
		if (reg.size() > 0)
			m[reg] |= mask;
		reg = "";
	}

	int count = 0;
	for (std::pair<std::string, int> it : m) {
	// for (map<string, int>::iterator it=m.begin(); it != m.end(); it++) {
		if (__builtin_popcount(it.second) == 1)
			count++;
	}
	ofstream fout;
	fout.open("output.txt");
	fout << count << endl;
	return 0;
}