#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Op {
#define Instructions S(nop), S(acc), S(jmp)
#define S(x) x
	enum Type { Instructions };
	static inline const Type types[] { Instructions };
#undef S
#define S(x) #x
	static inline const std::string strings[] { Instructions };
#undef S
#undef Instructions
	Type type;
	int arg;
	Op(std::string s):
		type(Type(std::distance(strings, std::find(strings, std::end(strings), s.substr(0, 3))))),
		arg(std::stoi(s.erase(0, 3)))
	{}
};

std::pair<bool, int> run(std::vector<Op> ops) {
	int reg = 0, pc = 0;
	std::vector<int> flow;
	while(pc >= 0 and pc < ops.size()) {
		reg += ops[pc].type == Op::Type::acc ? ops[pc].arg : 0;
		pc  += ops[pc].type == Op::Type::jmp ? ops[pc].arg : 1;
		if(std::find(flow.begin(), flow.end(), pc) != flow.end()) return { false, reg };
		flow.push_back(pc);
	}
	return { true, reg };
}

std::optional<std::vector<Op>> patch_firmware(std::vector<Op> ops, int patch_index) {
	auto it = ops.begin();
	do {
		it = std::find_if(++it, ops.end(), [](auto op) { return op.type != Op::acc; });
	} while(patch_index-- != 0);
	if(it == ops.end()) return {};
	it->type = it->type == Op::jmp ? Op::nop : Op::jmp;
	return ops;
}

int main() {
	std::fstream file { "input.txt" };
	std::vector<Op> firmware;
	for(std::string tmp; std::getline(file, tmp); ) {
		firmware.emplace_back(tmp);
	}
	// Part 1;
	std::cout << "Result 1: " << run(firmware).second << "\n";
	// Part 2;
	for(auto [patch,index] = std::make_pair(std::optional<std::vector<Op>>{},0); patch = patch_firmware(firmware,index++);) {
		auto [success,result] = run(*patch);
		if(success) {
			std::cout << "Result 2: " << result<< "\n";
			return 0;
		}
	}
	std::cout << "Result 2: No solution;\n";
}
