#include <fstream>
#include <iostream>
#include <algorithm>

struct Entry {
	int min = 0, max = 0;
	char n = '0';
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
	while(f) {
		Entry e;
		if(!(f >> e)) {
			break;
		};
		if(e.validity_rule_1()) ++valid[0];
		if(e.validity_rule_2()) ++valid[1];
	}
	std::cout << "Valid passwords: " << valid[0] << "\n";
	std::cout << "Valid passwords: " << valid[1] << "\n";
}
