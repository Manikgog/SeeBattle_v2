#include <iostream>
#include "drawMaps.h"
#include "arrangementOfShipsComp.h"
#include "arrangementOfShipsComp.cpp"

void drawCompShips() {
	std::cout << "++++++++++ поле Компьютера ++++++++++\n\n";
	// прорисовка строчки цифр по оси X
	std::cout << "    ";
	for (int i = 1; i <= 10; ++i) {
		std::cout << i << "  ";
	}
	std::cout << "\n";
	for (unsigned int i = 0; i < 10; ++i) {
		std::cout << "  ";
		if (i == 9) std::cout << i + 1 << " "; // прорисовка столбца цифр по оси Y
		else std::cout << i + 1 << "  ";
		for (unsigned int j = 0; j < 10; ++j) {
			if (compShipsMap[i][j] == 0) {
				if (j == 9) std::cout << "   |";
				else std::cout << "   ";
			}
			else if (compShipsMap[i][j] == '#') {
				if (j == 9) std::cout << "[ ]|";
				else std::cout << "[ ]";
			}
			else if (compShipsMap[i][j] == 'x') {
				if (j == 9) std::cout << " x |";
				else std::cout << " x ";
			}
			else if (compShipsMap[i][j] == '-') {
				if (j == 9) std::cout << " - |";
				else std::cout << " - ";
			}
			else if (compShipsMap[i][j] == '+') {
				if (j == 9) std::cout << " + |";
				else std::cout << " + ";
			}

		}
		std::cout << "\n";
	}
	std::cout << "  -";
	for (int i = 0; i < 11; ++i) {
		std::cout << "---";
	}
	std::cout << std::endl;
}