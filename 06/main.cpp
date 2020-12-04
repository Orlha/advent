#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

void part1() {
	std::fstream file { "input.txt" };
	std::string acc;
	std::string tmp;
	std::vector<std::string> blanks;
	while(std::getline(file, tmp)) {
		if(tmp.size() == 0) {
			blanks.push_back(acc);
			acc.clear();
		} else {
			acc += tmp;
		}
	}
	if(acc.size() != 0) {
		blanks.push_back(acc);
	}
	size_t result = 0;
	for(const auto& s: blanks) {
		std::set<char> apply;
		result += std::count_if(std::begin(s), std::end(s), [&](char ch) {
			if(apply.find(ch) != apply.end()) return false;
			apply.insert(ch);
			return true;
		});
	}
	std::cout << "Result: " << result << "\n";
}

void part2() {
	std::fstream file { "input.txt" };
	std::set<char> unique;
	std::string tmp;
	size_t result = 0;
	bool start = true;
	while(std::getline(file, tmp)) {
		if(tmp.size() == 0) {
			result += unique.size();
			unique.clear();
			start = true;
			continue;
		}
		if(start) {
			std::for_each(std::begin(tmp), std::end(tmp), [&unique](auto ch) {
				unique.insert(ch);
			});
			start = false;
		} else {
			for(auto f = unique.begin(); f != unique.end(); ) {
				if(tmp.find(*f) == tmp.npos) {
					f = unique.erase(f);
				} else {
					++f;
				}
			}
		}
	}
	result += unique.size();
	std::cout << "Result: " << result << "\n";
}

int main() {
	part1();
	part2();
}
