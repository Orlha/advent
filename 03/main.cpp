#include <fstream>
#include <iostream>

size_t count(int right, int down) {
	size_t count = 0, i = 0;
	for(auto [file,block] = std::make_pair(std::fstream("input.txt"), std::string()); std::getline(file, block); ) {
		if(i++ % down != 0) continue;
		if(block[(((i - 1) / down) * right) % 31] == '#') ++count;
	}
	return count;
}

int main() {
	std::cout << "[Part 1] Tress gathered: " << count(3, 1) << "\n";
	std::cout << "[Part 2] Trees gathered: " << count(1, 1) * count(3, 1) * count(5, 1) * count(7, 1) * count(1, 2) << "\n";
}
