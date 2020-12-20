#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string src, const std::string& del) {
	std::vector<std::string> result;
	auto it = src.begin();
	do {
		auto f = src.find(del);
		auto s = src.substr(0, f);
		if(s.size() != 0) {
			result.push_back(s);
			if(f == src.npos) {
				break;
			} else {
				src.erase(0, f + del.size());
			}
		} else {
			break;
		}
	} while(src.size() != 0);
	return result;
}

int main() {
	std::fstream file { "input.txt" };
	int time = [&] {
		std::string time;
		std::getline(file, time);
		return std::stoi(time);
	}();
	auto buses = [&file] {
		std::string schedule;
		std::getline(file, schedule);
		auto tmp = split(schedule, ",");
		tmp.erase(std::remove_if(std::begin(tmp), std::end(tmp), [](auto c) { return c == "x"; }), std::end(tmp));
		std::vector<int> result;
		for(const auto& s: tmp) {
			result.push_back(std::stoi(s));
		}
		return result;
	}();
	std::cout << "Current time: " << time << "\n";
	std::vector<int> nexts;
	for(const auto& s: buses) {
		std::cout << "Bus: " << s << "\n";
		int next = ((time / s) + 1) * s;
		std::cout << "Next time: " << next << "\n";
		nexts.push_back(next);
	}
	auto min = std::min_element(nexts.begin(), nexts.end());
	std::cout << "Best bus: " << *min << "\n";
	int id = buses[std::distance(nexts.begin(), min)];

	std::cout << "It's ID: " << id << "\n";
	std::cout << "Result: " << id * (*min - time) << "\n";
	//for
}
