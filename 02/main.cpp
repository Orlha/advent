#include <fstream>
#include <iostream>
#include <algorithm>

struct Entry {
	int min, max;
	char n;
	std::string rest;
	friend std::ifstream& operator>>(std::ifstream& f, Entry& b) {
		f >> b.min >> b.max >> b.n;
		b.max = -b.max;
		f.ignore(1);
		f >> b.rest;
		return f;
	}
	bool validity_rule_1() const {
		auto c = std::count(std::begin(rest), std::end(rest), n);
		return c >= min && c <= max;
	}
	bool validity_rule_2() const {
		return (rest[min - 1] == n) ^ (rest[max - 1] == n);
	}
};

int main() {
	std::ifstream f { "input.txt" };
	int valid[2] { 0 };
	for(Entry e; f >> e; ) {
		if(e.validity_rule_1()) ++valid[0];
		if(e.validity_rule_2()) ++valid[1];
	}
	std::cout << "Valid passwords 1: " << valid[0] << "\n";
	std::cout << "Valid passwords 2: " << valid[1] << "\n";
}
