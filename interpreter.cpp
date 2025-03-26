#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <fstream>

class Interpreter {
private:
	std::vector<std::vector<std::string>> program;
	std::unordered_map<std::string, int> variables = {{"A", 0}, {"B", 0}, {"C", 0}, {"D", 0}};
	
	unsigned current_line = 0;
	unsigned steps = 0;

public:
	Interpreter(std::vector<std::vector<std::string>> p) {
		program = p;
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

			if (line[0] == "wypisz") {print_instruction(line);}
			else if (line[0] == "wczytaj") {read_input(line);}
			else if (line[0] == "ustaw") {set_variable(line);}
			else if (line[0] == "zwiększ") {increment_variable(line);}
			else if (line[0] == "zmniejsz") {decrement_variable(line);}
			else if (line[0] == "jeżeli") {conditional_jump(line);}
			else if (line[0] == "skocz") {jump(line);}
			else if (line[0] == "nowa") {new_line();}
			else {std::cout << "unknown command: " << line[0] << std::endl;}

			if (steps > 10000) {std::cout << "przekroczono 10000 kroków" << std::endl; exit(0);}
		}

		std::cout << std::endl;
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
		if (variables.find(parts[2]) != variables.end()) {
			variables[parts[1]] = variables[parts[2]];
		} else {
			variables[parts[1]] = std::stoi(parts[2]);
		}
	}

	void increment_variable(std::vector<std::string> parts) {
		if (variables.find(parts[2]) != variables.end()) {
			variables[parts[1]] += variables[parts[2]];
		} else {
			variables[parts[1]] += std::stoi(parts[2]);
		}
	}

	void decrement_variable(std::vector<std::string> parts) {
			if (variables.find(parts[2]) != variables.end()) {
				variables[parts[1]] -= variables[parts[2]];
			} else {
				variables[parts[1]] -= std::stoi(parts[2]);
			}
		}

	void conditional_jump(std::vector<std::string> parts) {
		std::string operation = parts[2];
		bool condition;
		int value;

		if (variables.find(parts[3]) != variables.end()) {
			value = variables[parts[3]];			
		} else {
			value = std::stoi(parts[3]);
		}

		if (operation == "<") {condition = variables[parts[1]] < value;}
		else if (operation == "<=") {condition = variables[parts[1]] <= value;}
		else if (operation == "=") {condition = variables[parts[1]] == value;}
		else if (operation == "!=") {condition = variables[parts[1]] != value;}
		else if (operation == ">") {condition = variables[parts[1]] > value;}
		else if (operation == ">=") {condition = variables[parts[1]] >= value;}
		else {condition = false;}

		if (condition) {
			if (parts[4] == "end") {exit(0);}

			else if (parts[4] == "next") {
				return;
			}

			else {
				current_line = std::stoi(parts[4]) - 1;
			}
			
		} else {
			if (parts[5] == "end") {exit(0);}

			else if (parts[5] == "next") {
				return;
			}

			else {
				current_line = std::stoi(parts[5]) - 1;
			}
		}
	}

	void jump(std::vector<std::string> parts) {
		if (parts[1] == "end") {exit(0);}

		else if (parts[1] == "next") {return;}
		
		else {current_line = std::stoi(parts[1]) - 1;}
	}

	void new_line() {
		std::cout << std::endl;
	}

	void show_d() {std::cout << variables["D"];}

};

std::vector<std::vector<std::string>> load_program(const std::string& path) {
	std::ifstream plik(path);
	if (!plik) {
		throw std::runtime_error("Nie można otworzyć pliku: " + path);
	}


	std::vector<std::vector<std::string>> wynik;
	std::string linia;

	while (std::getline(plik, linia)) {
		std::istringstream linia_strumien(linia);
		std::vector<std::string> slowa;
		std::string slowo;

		while (linia_strumien >> slowo) {
			slowa.push_back(slowo);
		}

		if (!slowa.empty()) {
			wynik.push_back(slowa);
		}
	}

	return wynik;
}

int main(int argc, char* argv[]) {

	if (argc < 2) {std::cout << "proszę podać ścieżkę do pliku" << std::endl; exit(0);}

	std::vector<std::vector<std::string>> program = load_program(argv[1]);	

	

	Interpreter interpreter(program);
	interpreter.execute();
	
}
