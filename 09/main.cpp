#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using u64 = uint64_t;

int main() {
	std::fstream file { "input.txt" };
	std::vector<u64> nums;

	for(std::string tmp; std::getline(file, tmp); ) {
		nums.push_back(std::stoll(tmp));
	}

	auto check_sum = [&] (auto begin, auto end, auto val) {
		for(auto i = begin; i != end; ++i) {
			for(auto k = begin + 1; k != end; ++k) {
				if(*i + *k == val) return true;
			}
		}
		return false;
	};

	u64 result_1 = [&nums,&check_sum] {
		for(auto it = nums.begin() + 25; it != nums.end(); ++it) {
			if(!check_sum(it - 25, it, *it)) return *it;
		}
		return 0ul;
	}();
	std::cout << "Result 1: " << result_1 << "\n";

	u64 result_2 = [&nums,result_1] {
		for(auto i = nums.begin(); i != nums.end(); ++i) {
			u64 sum = *i;
			for(auto k = i + 1; k != nums.end(); ++k) {
				sum += *k;
				if(sum == result_1) {
					return *i + *k;
				}
			}
		}
		return 0ul;
	}();
	std::cout << "Result 2: " << result_2 << "\n";
}
