#include <fstream>
#include <string>
#include <iostream>
#include <vector>

enum Place {
	Empty,
	Occupied,
	Floor,
};

struct Grid {
	std::vector<Place> data;
	int width = 0, height = 0;
};

int main() {
	const Grid input = []() {
		std::fstream file { "input.txt" };
		Grid grid;
		for(std::string tmp; std::getline(file, tmp); ++grid.height) {
			for(auto c: tmp) {
				switch(c) {
				case 'L': grid.data.push_back(Place::Empty);    break;
				case '#': grid.data.push_back(Place::Occupied); break;
				case '.': grid.data.push_back(Place::Floor);    break;
				}
			}
		}
		grid.width = grid.data.size() / grid.height;
		return grid;
	} ();

	auto part1 = [](const Grid& grid) {
		Grid result { grid };
		auto count_occupied = [&](int seat_x, int seat_y) {
			int result = 0;
			for(int y = seat_y - 1; y <= seat_y + 1; ++y) {
				for(int x = seat_x - 1; x <= seat_x + 1; ++x) {
					if(x == seat_x && y == seat_y) continue;
					if(y < 0 || x < 0 || y == grid.height || x == grid.width) continue;
					if(grid.data[y * grid.width + x] == Occupied) ++result;
				}
			}
			return result;
		};
		for(int i = 0; i < grid.data.size(); ++i) {
			int x = i % grid.width;
			int y = i / grid.width;
			switch(grid.data[i]) {
				case Occupied: if(count_occupied(x, y) >= 4) result.data[i] = Empty; break;
				case Empty: if(count_occupied(x, y) == 0) result.data[i] = Occupied; break;
			}
		}
		return result;
	};

	auto part2 = [](const Grid& grid) {
		Grid result { grid };
		auto scan_n = [&grid](int seat_x, int seat_y) {
			for(int y = seat_y - 1; y >= 0; --y) {
				auto place = grid.data[y * grid.width + seat_x];
				if(place != Floor) return place == Occupied;
			}
			return false;
		};
		auto scan_s = [&grid](int seat_x, int seat_y) {
			for(int y = seat_y + 1; y < grid.height; ++y) {
				auto place = grid.data[y * grid.width + seat_x];
				if(place != Floor) return place == Occupied;
			}
			return false;
		};
		auto scan_w = [&grid](int seat_x, int seat_y) {
			for(int x = seat_x - 1; x >= 0; --x) {
				auto place = grid.data[seat_y * grid.width + x];
				if(place != Floor) return place == Occupied;
			}
			return false;
		};
		auto scan_e = [&grid](int seat_x, int seat_y) {
			for(int x = seat_x + 1; x < grid.width; ++x) {
				auto place = grid.data[seat_y * grid.width + x];
				if(place != Floor) return place == Occupied;
			}
			return false;
		};
		auto scan_nw = [&grid](int seat_x, int seat_y) {
			for(int x = seat_x - 1, y = seat_y - 1; x >= 0 && y >= 0; --x, --y) {
				auto place = grid.data[y * grid.width + x];
				if(place != Floor) return place == Occupied;
			}
			return false;
		};
		auto scan_ne = [&grid](int seat_x, int seat_y) {
			for(int x = seat_x + 1, y = seat_y - 1; x < grid.width && y >= 0; ++x, --y) {
				auto place = grid.data[y * grid.width + x];
				if(place != Floor) return place == Occupied;
			}
			return false;
		};
		auto scan_sw = [&grid](int seat_x, int seat_y) {
			for(int x = seat_x - 1, y = seat_y + 1; x >= 0 && y < grid.height; --x, ++y) {
				auto place = grid.data[y * grid.width + x];
				if(place != Floor) return place == Occupied;
			}
			return false;
		};
		auto scan_se = [&grid](int seat_x, int seat_y) {
			for(int x = seat_x + 1, y = seat_y + 1; x < grid.width && y < grid.height; ++x, ++y) {
				auto place = grid.data[y * grid.width + x];
				if(place != Floor) return place == Occupied;
			}
			return false;
		};
		auto count_occupied = [&](int seat_x, int seat_y) {
			int result = 0;
			result += scan_n(seat_x, seat_y);
			result += scan_s(seat_x, seat_y);
			result += scan_w(seat_x, seat_y);
			result += scan_e(seat_x, seat_y);
			result += scan_ne(seat_x, seat_y);
			result += scan_nw(seat_x, seat_y);
			result += scan_se(seat_x, seat_y);
			result += scan_sw(seat_x, seat_y);
			return result;
		};
		for(int i = 0; i < grid.data.size(); ++i) {
			int x = i % grid.width;
			int y = i / grid.width;
			switch(grid.data[i]) {
				case Occupied: if(count_occupied(x, y) >= 5) result.data[i] = Empty; break;
				case Empty: if(count_occupied(x, y) == 0) result.data[i] = Occupied; break;
			}
		}
		return result;
	};

	auto simulate = [] (const Grid& input, auto& step){
		auto grid { input };
		for(Grid tmp; (tmp = step(grid)).data != grid.data; grid = tmp);
		return std::count(grid.data.begin(), grid.data.end(), Occupied);
	};

	std::cout << "Part 1: " << simulate(input, part1) << "\n";
	std::cout << "Part 2: " << simulate(input, part2) << "\n";
}
