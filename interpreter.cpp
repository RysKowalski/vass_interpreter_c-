#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

class Interpreter {
private:
	std::vector<std::vector<std::string>> program;
	std::unordered_map<std::string, int> variables;
	
	unsigned current_line = 0;
	unsigned steps = 0;

public:
	Interpreter(std::vector<std::vector<std::string>> p) {
		program = p;
		variables["A"] = 0;
		variables["B"] = 0;
		variables["C"] = 0;
		variables["D"] = 0;
	}

	void show_program() {
		for (const auto& wiersz : program) {
			for (const auto& element : wiersz) {
				std::cout << element << " ";
			}
			std::cout << std::endl;
		}
	}

	void execute() {
		std::vector<std::string> line;
		while (current_line < program.size()) {
			steps += 1;
			
			line = program[current_line];
			current_line += 1;

			
		}
	}
	

	void print_instruction(std::vector<std::string> parts) {
		if (parts[1] == "zmienną") {
			std::cout << variables[parts[2]];
		}
	

		else if (parts[1] == "napis") {
			std::string text = "";
			for (size_t i = 2; i < parts.size(); ++i) {
				text += parts[i] + " ";
			}
			
			size_t start = text.find_first_not_of(" \t");
	
			if (start != std::string::npos && (text[start] == '"' || text[start] == '\'')) {
				char delim = text[start];
				size_t end = text.find(delim, start + 1);
				
				if (end != std::string::npos) {
					std::cout << text.substr(start + 1, end - start - 1);
				}
			}
		}
	}

	void read_input(std::vector<std::string> parts) {
		int liczba;

		std::cout << "podaj liczbe: ";
		std::cin >> liczba;

		variables[parts[1]] = liczba;
	}
	
	void set_variable(std::vector<std::string> parts) {
		variables[parts[1]] = std::stoi(parts[2]);
	}

};

int main() {

	std::vector<std::vector<std::string>> test = {
		{"l1", "tekst1", "tekst2", "tekst3"},
		{"l2", "tekst1", "tekst2", "tekst3"},
		{"l3", "tekst1", "tekst2", "tekst3"}
	};

	Interpreter interpreter(test);
	interpreter.read_input({"w", "D"});
	
}
