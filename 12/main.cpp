#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>

int main() {
	const int result_1 = [] {
		std::fstream file { "input.txt" };
		int x = 0, y = 0, dir = 1;
		for(std::string tmp; std::getline(file, tmp); ) {
			int num = std::stoi(tmp.substr(1));
			switch(tmp[0]) {
				case 'L': dir = (dir - num / 90 + 4) % 4; break;
				case 'R': dir = (dir + num / 90 + 0) % 4; break;
				case 'N': y += num;                       break;
				case 'S': y -= num;                       break;
				case 'E': x += num;                       break;
				case 'W': x -= num;                       break;
				case 'F': x += dir == 1 ? num : dir == 3 ? -num : 0;
						  y += dir == 0 ? num : dir == 2 ? -num : 0;
			}
		}
		return std::abs(x) + std::abs(y);
	} ();
	std::cout << "Part 1: "<< result_1 << "\n";

	const int result_2 = [] {
		std::fstream file { "input.txt" };
		std::pair<int,int> way { 10, 1 }, pos { 0, 0 };
		for(std::string tmp; std::getline(file, tmp); ) {
			auto l90  = [&way] { way.second = std::exchange(way.first , -way.second); };
			auto r90  = [&way] { way.first  = std::exchange(way.second, -way.first ); };
			auto f180 = [&way] { way.first = -way.first; way.second = -way.second; };
			int num = std::stoi(tmp.substr(1));
			switch(tmp[0]) {
				case 'L': num == 90 ? l90() : num == 270 ? r90() : f180(); break;
				case 'R': num == 90 ? r90() : num == 270 ? l90() : f180(); break;
				case 'N': way.second += num;                               break;
				case 'S': way.second -= num;                               break;
				case 'E': way.first  += num;                               break;
				case 'W': way.first  -= num;                               break;
				case 'F': pos.first  += num * way.first;
						  pos.second += num * way.second;
			}
		}
		return std::abs(pos.first) + std::abs(pos.second);
	} ();
	std::cout << "Part 2: " << result_2 << "\n";
}
