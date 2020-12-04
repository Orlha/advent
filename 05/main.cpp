#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>

int main() {
	std::fstream file { "input.txt" };
	int result = 0;
	std::map<int, int> seats;
	for(std::string ticket; std::getline(file, ticket); ) {
		std::transform(std::begin(ticket), std::end(ticket), std::begin(ticket), [](auto character) {
			if(character == 'B' or character == 'R') return '1';
			return '0';
		});
		auto row = std::stoi(ticket.substr(0,  7), nullptr, 2);
		auto col = std::stoi(ticket.substr(7, 10), nullptr, 2);
		auto seat_id = row * 8 + col;
		seats[row] += (col + 1);
		if(seat_id > result) result = seat_id;
	}
	std::cout << "Result 1: " << result << "\n";
	auto seat = std::find_if(++std::begin(seats), --std::end(seats), [](auto p) { return p.second != 36; });
	result = seat->first * 8 + (36 - seat->second - 1);
	std::cout << "Result 2: " << result << "\n";
}
