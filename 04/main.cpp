#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

bool validity(const std::string& passport) {
	auto f = passport.find("byr:");
	if(f == passport.npos) return false;
	auto year = std::stoi(passport.substr(f + 4, 4));
	if(year < 1920 || year > 2002) return false;
	//std::cout << "Valid byr: " << year << "\n";

	f = passport.find("iyr:");
	if(f == passport.npos) return false;
	year = std::stoi(passport.substr(f + 4, 4));
	if(year < 2010 | year > 2020) return false;
	//std::cout << "Valid iyr: " << year << "\n";

	f = passport.find("eyr:");
	if(f == passport.npos) return false;
	year = std::stoi(passport.substr(f + 4, 4));
	if(year < 2020 | year > 2030) return false;
	//std::cout << "Valid eyr: " << year << "\n";

	f = passport.find("hgt:");
	if(f == passport.npos) return false;
	auto cm = passport.find("cm", f + 4, 2);
	auto in = passport.find("in", f + 4, 2);
	if(cm == passport.npos && in == passport.npos) return false;
	if(cm != passport.npos && in != passport.npos) return false;
	if(cm != passport.npos) {
		if(cm - f > 7) return false;
		auto hgt = std::stoi(passport.substr(f + 4, cm - f - 4));
		if(hgt < 150 || hgt > 193) return false;
		//std::cout << "Valid hgt: " << hgt << "cm\n";
	}
	if(in != passport.npos) {
		if(in - f > 6) return false;
		auto hgt = std::stoi(passport.substr(f + 4, in - f - 4));
		if(hgt < 59 || hgt > 76) return false;
		//std::cout << "Valid hgt: " << hgt << "in\n";
	}

	f = passport.find("hcl:#");
	if(f == passport.npos) return false;
	auto cl = passport.substr(f + 5, 6);
	bool cl_ok = true;
	for(auto c: cl) {
		if(!std::isdigit(c)
				&& c != 'a' && c != 'A'
				&& c != 'b' && c != 'B'
				&& c != 'c' && c != 'C'
				&& c != 'd' && c != 'D'
				&& c != 'e' && c != 'E'
				&& c != 'f' && c != 'F')
			cl_ok = false;
	}
	if(!cl_ok) return false;
	//std::cout << "Valid hcl:#" << cl << "\n";
	
	bool ecl = [&] {
		for(const auto& s: { "ecl:amb", "ecl:blu", "ecl:brn", "ecl:gry", "ecl:grn", "ecl:hzl", "ecl:oth" }) {
			if(passport.find(s) != passport.npos) {
				return true;
			}
		}
		return false;
	} ();
	if(!ecl) return false;

	f = passport.find("pid:");
	if(f == passport.npos) return false;
	auto pid_str = passport.substr(f + 4, 9);
	//std::cout << "pid: " << pid_str << "\n";
	auto pp = passport.substr(f + 4, 10);
	if(std::isdigit(pp[9])) return false;
	bool pid = [&] {
		for(auto c: pid_str) {
			if(!std::isdigit(c)) return false;
		}
		//std::cout << "Valid pid " << pid_str << "\n";
		return true;
	} ();
	if(!pid) return false;

	//std::cout << "Valid passport:\n" << passport << "\n";
	return true;
}

int main() {
	std::vector<std::string> passports;
	std::fstream f { "input.txt" };

	std::string tmp;
	std::string accum;
	while(std::getline(f, tmp)) {
		if(tmp.size() != 0) {
			accum += tmp + " ";
		} else {
			passports.push_back(accum);
			accum.clear();
		}
	}
	if(accum.size()) {
		passports.push_back(accum);
	}

	size_t valid = std::count_if(std::begin(passports), std::end(passports), [](auto passport) {
		for(const auto& s: { "byr:", "iyr:", "eyr:", "hgt:", "hcl:", "ecl:", "pid:" }) {
			if(passport.find(s) == passport.npos) {
				return false;
			}
		}
		return true;
	});
	std::cout << "Total valid passports: " << valid << "\n";

	// Part 2;
	size_t valid_2 = std::count_if(std::begin(passports), std::end(passports), validity);
	std::cout << "Total valid passports: " << valid_2 << "\n";
}
