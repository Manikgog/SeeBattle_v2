#include <iostream>
#include <locale.h>
#include <Windows.h>
#include <cstdlib>

int compShipsMap[10][10]{};
int gamerShipsMap[10][10]{};
struct point {
	int raw;
	int col;
};
void clearFilds();
void drawCompShips();
int calcEmptyCells();
void drawGamerShips();
void arrangementOfShipsComp();
void WelcomeScreen();
void arrangementOfShipsGamer();
void gamerShooting();
int compShooting();
int calcGamerShips();
int calcCompShips();
point randomShooting();
point p;// координаты предыдущей стрельбы компьютера
int compShips;



int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	WelcomeScreen();
	char name[20]{};
	int result;
	char key = 'y';
	do {
		clearFilds(); //обнуление массивов после игры
		std::cout << "Введите своё имя -> ";
		std::cin >> name;
		std::cout << "Привет, " << name << "!\n";
		srand((unsigned int)time(NULL));
		arrangementOfShipsComp();
		compShips = calcCompShips();
		std::cout << "\nНачальное количество палуб компьютера -> " << compShips << std::endl;
		arrangementOfShipsGamer();
		int gamerShips = calcGamerShips();
		std::cout << "\nНачальное количество палуб Игрока -> " << gamerShips << std::endl;
		p.raw = rand() % 10;
		p.col = rand() % 10;

		while (calcCompShips() > 0 && calcGamerShips() > 0) {
			srand((unsigned int)time(NULL));

			// стрельба Игрока
			gamerShooting();
			compShips = calcCompShips();
			
			std::cout << "У комьютера осталось " << compShips << std::endl;

			// Стрельба компьютера
			do {
				result = compShooting();
				drawGamerShips();
			} while (result);
			//drawGamerShips();

			gamerShips = calcGamerShips();
			
			std::cout << "У игрока осталось " << gamerShips << std::endl;
		}

		if (compShips == 0)
			std::cout << "\x1b[32mКомпьютер проиграл!\x1b[0m\n\n\n";
		if (gamerShips == 0)
			std::cout << "\n\n\n\x1b[31m " << name << " проиграл!\x1b[0m \n";
		system("pause");
		do {
			system("cls");
			std::cout << "Хотите сыграть ещё? y/n ";
			std::cin >> key;
		} while (key != 'y' && key != 'n');
		
	} while (key != 'n');

	return 0;
}

void clearFilds() {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			compShipsMap[i][j] = 0;
			gamerShipsMap[i][j] = 0;
		}
	}
}

int calcGamerShips() {
	int numberOfShips = 0;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j){
			if (gamerShipsMap[i][j] == '*')
				numberOfShips++;
		}
	}
	return numberOfShips;
}

int calcCompShips() {
	int numberOfShips = 0;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (compShipsMap[i][j] == '#')
				numberOfShips++;
		}
	}
	return numberOfShips;
}



int compShooting() {
	int numberOfEmptyCells = calcEmptyCells();

	// ищем Х который не окружён с четырёх сторок заполненными знаками (Х, +) клетками
	for (int i = 0; i <= 9; ++i) {
		for (int j = 0; j <= 9; ++j) {
			if (i == 0 && gamerShipsMap[i][j] == 'X') {
				if (gamerShipsMap[i + 1][j] != 'X' && gamerShipsMap[i + 1][j] != '+') {
					if (gamerShipsMap[i + 1][j] == '*') {
						gamerShipsMap[i + 1][j] = 'X';
						if (j > 0)
							gamerShipsMap[i][j - 1] = '+';
						if (j < 9)
							gamerShipsMap[i][j + 1] = '+';
						if (j > 0)
							gamerShipsMap[i + 2][j - 1] = '+';
						if (j < 9)
							gamerShipsMap[i + 2][j + 1] = '+';
						return 1;
					}
					else if (gamerShipsMap[i + 1][j] == 0) {
						gamerShipsMap[i + 1][j] = '+';
						return 0;
					}
				}
				if (j > 0 && gamerShipsMap[i][j - 1] != 'X' && gamerShipsMap[i][j - 1] != '+') {
					if (gamerShipsMap[i][j - 1] == '*') {
						gamerShipsMap[i][j - 1] = 'X';
						if (j - 1 > 0)
							gamerShipsMap[i + 1][j - 2] = '+';
						gamerShipsMap[i + 1][j] = '+';
						return 1;
					}
					else if (gamerShipsMap[i][j - 1] == 0) {
						gamerShipsMap[i][j - 1] = '+';
						return 0;
					}
				}
				if (j < 9 && gamerShipsMap[i][j + 1] != 'X' && gamerShipsMap[i][j + 1] != '+') {
					if (gamerShipsMap[i][j + 1] == '*') {
						gamerShipsMap[i][j + 1] = 'X';
						gamerShipsMap[i + 1][j] = '+';
						if (j + 1 < 9)
							gamerShipsMap[i + 1][j + 2] = '+';
						return 1;
					}
					else if (gamerShipsMap[i][j + 1] == 0) {
						gamerShipsMap[i][j + 1] = '+';
						return 0;
					}
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////
			else if (i > 0 && i < 9 && gamerShipsMap[i][j] == 'X') {
				if (gamerShipsMap[i - 1][j] != 'X' && gamerShipsMap[i - 1][j] != '+') {
					if (gamerShipsMap[i - 1][j] == '*') {
						gamerShipsMap[i - 1][j] = 'X';
						if (i - 2 >= 0 && j - 1 >= 0)
							gamerShipsMap[i - 2][j - 1] = '+';
						if (i - 2 >= 0 && j + 1 <= 9)
							gamerShipsMap[i - 2][j + 1] = '+';
						if (j - 1 >= 0)
							gamerShipsMap[i][j - 1] = '+';
						if (j + 1 <= 9)
							gamerShipsMap[i][j + 1] = '+';
						return 1;
					}
					else if (gamerShipsMap[i - 1][j] == 0) {
						gamerShipsMap[i - 1][j] = '+';
						return 0;
					}
				}
				if (gamerShipsMap[i + 1][j] != 'X' && gamerShipsMap[i + 1][j] != '+') {
					if (gamerShipsMap[i + 1][j] == '*') {
						gamerShipsMap[i + 1][j] = 'X';
						if (j - 1 >= 0)
							gamerShipsMap[i][j - 1] = '+';
						if (j + 1 <= 9)
							gamerShipsMap[i][j + 1] = '+';
						if (i + 2 <= 9 && j - 1 >= 0)
							gamerShipsMap[i + 2][j - 1] = '+';
						if (i + 2 <= 9 && j + 1 <= 9)
							gamerShipsMap[i + 2][j + 1] = '+';
						return 1;
					}
					else if (gamerShipsMap[i + 1][j] == 0) {
						gamerShipsMap[i + 1][j] = '+';
						return 0;
					}
				}
				if (j > 0 && gamerShipsMap[i][j - 1] != 'X' && gamerShipsMap[i][j - 1] != '+') {
					if (gamerShipsMap[i][j - 1] == '*') {
						gamerShipsMap[i][j - 1] = 'X';
						if (j - 2 >= 0)
							gamerShipsMap[i - 1][j - 2] = '+';
						gamerShipsMap[i - 1][j] = '+';
						if (j - 2 >= 0)
							gamerShipsMap[i + 1][j - 2] = '+';
						gamerShipsMap[i + 1][j] = '+';
						return 1;
					}
					else if (gamerShipsMap[i][j - 1] == 0) {
						gamerShipsMap[i][j - 1] = '+';
						return 0;
					}
				}
				if (j < 9 && gamerShipsMap[i][j + 1] != 'X' && gamerShipsMap[i][j + 1] != '+') {
					if (gamerShipsMap[i][j + 1] == '*') {
						gamerShipsMap[i][j + 1] = 'X';
						gamerShipsMap[i - 1][j] = '+';
						gamerShipsMap[i + 1][j] = '+';
						if (j + 2 <= 9) {
							gamerShipsMap[i - 1][j + 2] = '+';
							gamerShipsMap[i + 1][j + 2] = '+';
						}
						return 1;
					}
					else if (gamerShipsMap[i][j + 1] == 0) {
						gamerShipsMap[i][j + 1] = '+';
						return 0;
					}
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////
			else if (i == 9 && gamerShipsMap[i][j] == 'X') {
				if (gamerShipsMap[i - 1][j] != 'X' && gamerShipsMap[i - 1][j] != '+') {
					if (gamerShipsMap[i - 1][j] == '*') {
						gamerShipsMap[i - 1][j] = 'X';
						if (j - 1 >= 0) {
							gamerShipsMap[i - 2][j - 1] = '+';
							gamerShipsMap[i][j - 1] = '+';
						}
						if (j + 1 <= 9) {
							gamerShipsMap[i - 2][j + 1] = '+';
							gamerShipsMap[i][j + 1] = '+';
						}
						return 1;
					}
					else if (gamerShipsMap[i - 1][j] == 0) {
						gamerShipsMap[i - 1][j] = '+';
						return 0;
					}
				}
				if (j > 0 && gamerShipsMap[i][j - 1] != 'X' && gamerShipsMap[i][j - 1] != '+') {
					if (gamerShipsMap[i][j - 1] == '*') {
						gamerShipsMap[i][j - 1] = 'X';
						if (j - 2 >= 0)
							gamerShipsMap[i - 1][j - 2] = '+';
						gamerShipsMap[i - 1][j] = '+';
						return 1;
					}
					else if (gamerShipsMap[i][j - 1] == 0) {
						gamerShipsMap[i][j - 1] = '+';
						return 0;
					}
				}
				if (j < 9 && gamerShipsMap[i][j + 1] != 'X' && gamerShipsMap[i][j + 1] != '+') {
					if (gamerShipsMap[i][j + 1] == '*') {
						gamerShipsMap[i][j + 1] = 'X';
						gamerShipsMap[i - 1][j] = '+';
						if (j + 2 <= 9)
							gamerShipsMap[i - 1][j + 2] = '+';
						return 1;
					}
					else if (gamerShipsMap[i][j + 1] == 0) {
						gamerShipsMap[i][j + 1] = '+';
						return 0;
					}
				}
			}
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////

	// если количество пустых клеток больше 75
	// если не найдены кресты, то бьём по квадратам по диагонали
	int side = rand() % 4;
	if (side == 0) {
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				if (i == j) {
					if (gamerShipsMap[i][j] == 0) {
						gamerShipsMap[i][j] = '+';
						return 0;
					}
					else if (gamerShipsMap[i][j] == '*') {
						gamerShipsMap[i][j] = 'X';
						if (i > 0 && j > 0)
							gamerShipsMap[i - 1][j - 1] = '+';
						if (i > 0 && j < 9)
							gamerShipsMap[i - 1][j + 1] = '+';
						if (i < 9 && j > 0)
							gamerShipsMap[i + 1][j - 1] = '+';
						if (p.raw < 9 && p.col < 9)
							gamerShipsMap[i + 1][j + 1] = '+';
						return 1;
					}
				}
			}
		}
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				if (i == 9 && j == 0 ||
					i == 8 && j == 1 ||
					i == 7 && j == 2 ||
					i == 6 && j == 3 ||
					i == 5 && j == 4 ||
					i == 4 && j == 5 ||
					i == 3 && j == 6 ||
					i == 2 && j == 7 ||
					i == 1 && j == 8 ||
					i == 0 && j == 9) {
					if (gamerShipsMap[i][j] == 0) {
						gamerShipsMap[i][j] = '+';
						return 0;
					}
					else if (gamerShipsMap[i][j] == '*') {
						gamerShipsMap[i][j] = 'X';
						if (i > 0 && j > 0)
							gamerShipsMap[i - 1][j - 1] = '+';
						if (i > 0 && j < 9)
							gamerShipsMap[i - 1][j + 1] = '+';
						if (i < 9 && j > 0)
							gamerShipsMap[i + 1][j - 1] = '+';
						if (p.raw < 9 && p.col < 9)
							gamerShipsMap[i + 1][j + 1] = '+';
						return 1;
					}
				}
			}
		}
	}
	else if (side == 1) {
		for (int i = 9; i >= 0; --i) {
			for (int j = 0; j < 10; ++j) {
				if (i == j) {
					if (gamerShipsMap[i][j] == 0) {
						gamerShipsMap[i][j] = '+';
						return 0;
					}
					else if (gamerShipsMap[i][j] == '*') {
						gamerShipsMap[i][j] = 'X';
						if (i > 0 && j > 0)
							gamerShipsMap[i - 1][j - 1] = '+';
						if (i > 0 && j < 9)
							gamerShipsMap[i - 1][j + 1] = '+';
						if (i < 9 && j > 0)
							gamerShipsMap[i + 1][j - 1] = '+';
						if (p.raw < 9 && p.col < 9)
							gamerShipsMap[i + 1][j + 1] = '+';
						return 1;
					}
				}
			}
		}
		for (int i = 0; i < 10; ++i) {
			for (int j = 9; j >= 0; --j) {
				if (i == 9 && j == 0 ||
					i == 8 && j == 1 ||
					i == 7 && j == 2 ||
					i == 6 && j == 3 ||
					i == 5 && j == 4 ||
					i == 4 && j == 5 ||
					i == 3 && j == 6 ||
					i == 2 && j == 7 ||
					i == 1 && j == 8 ||
					i == 0 && j == 9) {
					if (gamerShipsMap[i][j] == 0) {
						gamerShipsMap[i][j] = '+';
						return 0;
					}
					else if (gamerShipsMap[i][j] == '*') {
						gamerShipsMap[i][j] = 'X';
						if (i > 0 && j > 0)
							gamerShipsMap[i - 1][j - 1] = '+';
						if (i > 0 && j < 9)
							gamerShipsMap[i - 1][j + 1] = '+';
						if (i < 9 && j > 0)
							gamerShipsMap[i + 1][j - 1] = '+';
						if (p.raw < 9 && p.col < 9)
							gamerShipsMap[i + 1][j + 1] = '+';
						return 1;
					}
				}
			}
		}
	}
	else if (side == 2) {
		for (int i = 9; i >= 0; --i) {
			for (int j = 9; j >= 0; --j) {
				if (i == j) {
					if (gamerShipsMap[i][j] == 0) {
						gamerShipsMap[i][j] = '+';
						return 0;
					}
					else if (gamerShipsMap[i][j] == '*') {
						gamerShipsMap[i][j] = 'X';
						if (i > 0 && j > 0)
							gamerShipsMap[i - 1][j - 1] = '+';
						if (i > 0 && j < 9)
							gamerShipsMap[i - 1][j + 1] = '+';
						if (i < 9 && j > 0)
							gamerShipsMap[i + 1][j - 1] = '+';
						if (p.raw < 9 && p.col < 9)
							gamerShipsMap[i + 1][j + 1] = '+';
						return 1;
					}
				}
			}
		}
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				if (i == 9 && j == 0 ||
					i == 8 && j == 1 ||
					i == 7 && j == 2 ||
					i == 6 && j == 3 ||
					i == 5 && j == 4 ||
					i == 4 && j == 5 ||
					i == 3 && j == 6 ||
					i == 2 && j == 7 ||
					i == 1 && j == 8 ||
					i == 0 && j == 9) {
					if (gamerShipsMap[i][j] == 0) {
						gamerShipsMap[i][j] = '+';
						return 0;
					}
					else if (gamerShipsMap[i][j] == '*') {
						gamerShipsMap[i][j] = 'X';
						if (i > 0 && j > 0)
							gamerShipsMap[i - 1][j - 1] = '+';
						if (i > 0 && j < 9)
							gamerShipsMap[i - 1][j + 1] = '+';
						if (i < 9 && j > 0)
							gamerShipsMap[i + 1][j - 1] = '+';
						if (p.raw < 9 && p.col < 9)
							gamerShipsMap[i + 1][j + 1] = '+';
						return 1;
					}
				}
			}
		}
	}
	else if (side == 3) {
		for (int i = 9; i >= 0; --i) {
			for (int j = 9; j >= 0; --j) {
				if (i == j) {
					if (gamerShipsMap[i][j] == 0) {
						gamerShipsMap[i][j] = '+';
						return 0;
					}
					else if (gamerShipsMap[i][j] == '*') {
						gamerShipsMap[i][j] = 'X';
						if (i > 0 && j > 0)
							gamerShipsMap[i - 1][j - 1] = '+';
						if (i > 0 && j < 9)
							gamerShipsMap[i - 1][j + 1] = '+';
						if (i < 9 && j > 0)
							gamerShipsMap[i + 1][j - 1] = '+';
						if (p.raw < 9 && p.col < 9)
							gamerShipsMap[i + 1][j + 1] = '+';
						return 1;
					}
				}
			}
		}
		for (int i = 9; i >= 0; --i) {
			for (int j = 9; j >= 0; --j) {
				if (i == 9 && j == 0 ||
					i == 8 && j == 1 ||
					i == 7 && j == 2 ||
					i == 6 && j == 3 ||
					i == 5 && j == 4 ||
					i == 4 && j == 5 ||
					i == 3 && j == 6 ||
					i == 2 && j == 7 ||
					i == 1 && j == 8 ||
					i == 0 && j == 9) {
					if (gamerShipsMap[i][j] == 0) {
						gamerShipsMap[i][j] = '+';
						return 0;
					}
					else if (gamerShipsMap[i][j] == '*') {
						gamerShipsMap[i][j] = 'X';
						if (i > 0 && j > 0)
							gamerShipsMap[i - 1][j - 1] = '+';
						if (i > 0 && j < 9)
							gamerShipsMap[i - 1][j + 1] = '+';
						if (i < 9 && j > 0)
							gamerShipsMap[i + 1][j - 1] = '+';
						if (p.raw < 9 && p.col < 9)
							gamerShipsMap[i + 1][j + 1] = '+';
						return 1;
					}
				}
			}
		}
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////

	if (numberOfEmptyCells > 75) { 
		// если не найдены кресты (подбитые палубы) с неотмеченными клетками
		// тогда начинаем искать наугад
		p = randomShooting();
		if (gamerShipsMap[p.raw][p.col] == 0) {
			gamerShipsMap[p.raw][p.col] = '+';
			return 0;
		}
		else if (gamerShipsMap[p.raw][p.col] == '*') {
			gamerShipsMap[p.raw][p.col] = 'X';
			if (p.raw > 0 && p.col > 0)
				gamerShipsMap[p.raw - 1][p.col - 1] = '+';
			if (p.raw > 0 && p.col < 9)
				gamerShipsMap[p.raw - 1][p.col + 1] = '+';
			if (p.raw < 9 && p.col > 0)
				gamerShipsMap[p.raw + 1][p.col - 1] = '+';
			if (p.raw < 9 && p.col < 9)
				gamerShipsMap[p.raw + 1][p.col + 1] = '+';
			return 1;
		}
	}
	else {
		int firstQuadEmptyCells = 0; // количество пустых клеток в первом квадранте
		int secondQuadEmptyCells = 0; // количество пустых клеток во втором квадранте
		int thirdQuadEmptyCells = 0; // количество пустых клеток в третьем квадранте
		int fouthQuadEmptyCells = 0; // количество пустых клеток в четвертом квадранте
		int max = 0;
		// подсчёт количества пустых клеток в первом квадранте
		for (int i = 0; i <= 4; ++i) {
			for (int j = 0; j <= 4; ++j) {
				if (gamerShipsMap[i][j] != '+' && gamerShipsMap[i][j] != 'X') {
					firstQuadEmptyCells++;
				}
			}
		}
		// подсчёт количества пустых клеток во втором квадранте
		for (int i = 0; i <= 4; ++i) {
			for (int j = 5; j <= 9; ++j) {
				if (gamerShipsMap[i][j] != '+' && gamerShipsMap[i][j] != 'X') {
					secondQuadEmptyCells++;
				}
			}
		}
		// подсчёт количества пустых клеток в третьем квадранте
		for (int i = 5; i <= 9; ++i) {
			for (int j = 0; j <= 4; ++j) {
				if (gamerShipsMap[i][j] != '+' && gamerShipsMap[i][j] != 'X') {
					thirdQuadEmptyCells++;
				}
			}
		}
		// подсчёт количества пустых клеток в четвёртом квадранте
		for (int i = 5; i <= 9; ++i) {
			for (int j = 5; j <= 9; ++j) {
				if (gamerShipsMap[i][j] != '+' && gamerShipsMap[i][j] != 'X') {
					fouthQuadEmptyCells++;
				}
			}
		}
		max = firstQuadEmptyCells;
		if (max < secondQuadEmptyCells)
			max = secondQuadEmptyCells;
		else if (max < thirdQuadEmptyCells)
			max = thirdQuadEmptyCells;
		else if (max < fouthQuadEmptyCells)
			max = fouthQuadEmptyCells;
		if (max == firstQuadEmptyCells) {
			do {
				p = randomShooting();
			} while (p.raw > 4 && p.col > 4);
			if (gamerShipsMap[p.raw][p.col] == 0) {
				gamerShipsMap[p.raw][p.col] = '+';
				return 0;
			}
			else if (gamerShipsMap[p.raw][p.col] == '*') {
				gamerShipsMap[p.raw][p.col] = 'X';
				if (p.raw > 0 && p.col > 0)
					gamerShipsMap[p.raw - 1][p.col - 1] = '+';
				if (p.raw > 0 && p.col < 9)
					gamerShipsMap[p.raw - 1][p.col + 1] = '+';
				if (p.raw < 9 && p.col > 0)
					gamerShipsMap[p.raw + 1][p.col - 1] = '+';
				if (p.raw < 9 && p.col < 9)
					gamerShipsMap[p.raw + 1][p.col + 1] = '+';
				return 1;
			}

		}
		else if (max == secondQuadEmptyCells) {
			do {
				p = randomShooting();
			} while (p.raw > 4 && p.col < 5);
			if (gamerShipsMap[p.raw][p.col] == 0) {
				gamerShipsMap[p.raw][p.col] = '+';
				return 0;
			}
			else if (gamerShipsMap[p.raw][p.col] == '*') {
				gamerShipsMap[p.raw][p.col] = 'X';
				if (p.raw > 0 && p.col > 0)
					gamerShipsMap[p.raw - 1][p.col - 1] = '+';
				if (p.raw > 0 && p.col < 9)
					gamerShipsMap[p.raw - 1][p.col + 1] = '+';
				if (p.raw < 9 && p.col > 0)
					gamerShipsMap[p.raw + 1][p.col - 1] = '+';
				if (p.raw < 9 && p.col < 9)
					gamerShipsMap[p.raw + 1][p.col + 1] = '+';
				return 1;
			}
		}
		else if (max == thirdQuadEmptyCells) {
			do {
				p = randomShooting();
			} while (p.raw < 5 && p.col > 4);
			if (gamerShipsMap[p.raw][p.col] == 0) {
				gamerShipsMap[p.raw][p.col] = '+';
				return 0;
			}
			else if (gamerShipsMap[p.raw][p.col] == '*') {
				gamerShipsMap[p.raw][p.col] = 'X';
				if (p.raw > 0 && p.col > 0)
					gamerShipsMap[p.raw - 1][p.col - 1] = '+';
				if (p.raw > 0 && p.col < 9)
					gamerShipsMap[p.raw - 1][p.col + 1] = '+';
				if (p.raw < 9 && p.col > 0)
					gamerShipsMap[p.raw + 1][p.col - 1] = '+';
				if (p.raw < 9 && p.col < 9)
					gamerShipsMap[p.raw + 1][p.col + 1] = '+';
				return 1;
			}
		}
		else {
			do {
				p = randomShooting();
			} while (p.raw < 5 && p.col < 5);
			if (gamerShipsMap[p.raw][p.col] == 0) {
				gamerShipsMap[p.raw][p.col] = '+';
				return 0;
			}
			else if (gamerShipsMap[p.raw][p.col] == '*') {
				gamerShipsMap[p.raw][p.col] = 'X';
				if (p.raw > 0 && p.col > 0)
					gamerShipsMap[p.raw - 1][p.col - 1] = '+';
				if (p.raw > 0 && p.col < 9)
					gamerShipsMap[p.raw - 1][p.col + 1] = '+';
				if (p.raw < 9 && p.col > 0)
					gamerShipsMap[p.raw + 1][p.col - 1] = '+';
				if (p.raw < 9 && p.col < 9)
					gamerShipsMap[p.raw + 1][p.col + 1] = '+';
				return 1;
			}
		}

		return 0;
	}
}

point randomShooting() {
	do {
		p.raw = rand() % 10;
		p.col = rand() % 10;
	} while (gamerShipsMap[p.raw][p.col] == '+' || gamerShipsMap[p.raw][p.col] == 'X');
	return p;
}

void gamerShooting() {
	bool result = false;
	int compShips = 0;
	int x, y;
	do {
		
		result = false;
		bool first = true;
		do {
			char c[3];
			x = 0; y = 0;
			if (first == true) {
				std::cout << "Введите координаты для нанесения удара (X, Y) -> ";
			}
			else {
				std::cout << "\x1b[31mКоординаты должны быть в интервале от 1 до 10. Внимательнее вводите координаты!\x1b[0m\n";
				std::cout << "Введите координаты для нанесения удара (X, Y) -> ";
			}
			first = false;

			
			//std::cin >> x >> y;
			
			std::cin >> c;
			x = atoi(c);

			std::cin >> c;
			y = atoi(c);
		} while ((x < 1 || x > 10) || (y < 1 || y > 10));
		
		x--; y--;
		// если попал
		if (compShipsMap[y][x] == '#') {
			compShipsMap[y][x] = 'X';
			result = true;
		}
		// если не попал
		else if(compShipsMap[y][x] == 0) {
			compShipsMap[y][x] = '+'; // помечаем клетку, чтобы повторно сюда не стрелять
		}
		// если попал туда куда уже попадал
		else if (compShipsMap[y][x] == 'X' || compShipsMap[y][x] == '+') {
			std::cout << "\x1b[31mВнимательнее вводите координаты!\x1b[0m\n";
		}
		// подсчёт количества оставшихся кораблей у компьютера
		compShips = calcCompShips();
		if (compShips == 0) break;
		std::cout << "У компьютера осталось " << compShips << std::endl;
		drawCompShips();
	} while (result);
}

void arrangementOfShipsComp() {
	
	int Cx, Cy;
	int numberOfShips = 0;
	do {
		numberOfShips = 0;
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				compShipsMap[i][j] = 0;
			}
		}

		//////////////////////////////////////////////////////// постройка одного однопалубного корабля ////////////////////////////////////////
		int n = 0;
		do {
			// очистка поля компьютера
			

			Cx = rand() % 10;
			Cy = rand() % 10;
			if (compShipsMap[Cy][Cx] == 0) {
				for (int i = Cy - 1; i < Cy + 2; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j < Cx + 2; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x'; // отметка зоны равной одной клетке вокруг корабля
					}
				}
				compShipsMap[Cy][Cx] = '#';
				n++;
			}
			else {
				continue;
			}
		} while (n == 0);

		/////////////////////////////////////////////////////// постройка одного двухпалубного корабля ///////////////////////////////////////////
		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0)) { // берём координату выше на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1 - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy - 1][Cx] = '#';
				n++;
			}
			// если точка Сy - 1 занята то берём другую точку и проверяем
			else if ((compShipsMap[Cy][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0)) {// берём координату ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy; i <= Cy + 2; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy + 1][Cx] = '#';
				n++;
			}
			// если точка Сy + 1 занята то берём другую точку и проверяем
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && compShipsMap[Cy][Cx + 1] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 2; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy][Cx + 1] = '#';
				n++;
			}
			// если точка Сx + 1 занята то берём другую точку и проверяем
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx - 1 >= 0 && compShipsMap[Cy][Cx - 1] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 2; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy][Cx - 1] = '#';
				n++;
			}


		} while (n == 0);

		/////////////////////////////////////////////////////////////// постройка трёхпалубного корабля ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0)) { // берём координату выше и ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1 - 1; i <= Cy + 1 + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy - 1][Cx] = '#';
				compShipsMap[Cy + 1][Cx] = '#';
				n++;
			}
			// если точка Сy - 1  и Сy + 1 занята то проверяем Cx - 1 и Cx + 1
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && compShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && compShipsMap[Cy][Cx - 1] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1 - 1; j <= Cx + 2; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy][Cx + 1] = '#';
				compShipsMap[Cy][Cx - 1] = '#';
				n++;
			}

		} while (n == 0);

		/////////////////////////////////////////////////////////////// постройка четырёхпалубного корабля ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0) && (Cy + 2 <= 9 && compShipsMap[Cy + 2][Cx] == 0)) { // берём координату выше и ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 2; i <= Cy + 3; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy - 1][Cx] = '#';
				compShipsMap[Cy + 1][Cx] = '#';
				compShipsMap[Cy + 2][Cx] = '#';
				n++;
			}
			else if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0) && (Cy - 2 >= 0 && compShipsMap[Cy - 2][Cx] == 0)) { // берём координату выше и ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 3; i <= Cy + 2; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy - 1][Cx] = '#';
				compShipsMap[Cy - 2][Cx] = '#';
				compShipsMap[Cy + 1][Cx] = '#';
				n++;
			}

			// если точка Сy - 1  и Сy + 1 занята то проверяем Cx - 1 и Cx + 1
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && compShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && compShipsMap[Cy][Cx - 1] == 0) && (Cx - 2 >= 0 && compShipsMap[Cy][Cx - 2] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 3; j <= Cx + 2; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy][Cx + 1] = '#';
				compShipsMap[Cy][Cx - 1] = '#';
				compShipsMap[Cy][Cx - 2] = '#';
				n++;
			}
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && compShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && compShipsMap[Cy][Cx - 1] == 0) && (Cx + 2 <= 9 && compShipsMap[Cy][Cx + 2] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 2; j <= Cx + 3; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy][Cx + 1] = '#';
				compShipsMap[Cy][Cx - 1] = '#';
				compShipsMap[Cy][Cx + 2] = '#';
				n++;
			}


		} while (n == 0);

		/////////////////////////////////////////////////////////////// постройка пятипалубного корабля ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0) && (Cy + 2 <= 9 && compShipsMap[Cy + 2][Cx] == 0) &&
				(Cy - 2 >= 0 && compShipsMap[Cy - 2][Cx] == 0)) { // берём координату выше и ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 3; i <= Cy + 3; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy - 1][Cx] = '#';
				compShipsMap[Cy + 1][Cx] = '#';
				compShipsMap[Cy + 2][Cx] = '#';
				compShipsMap[Cy - 2][Cx] = '#';
				n++;
			}

			else if ((compShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && compShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && compShipsMap[Cy][Cx - 1] == 0) &&
				(Cx + 2 >= 0 && compShipsMap[Cy][Cx + 2] == 0) && (Cx - 2 >= 0 && compShipsMap[Cy][Cx - 2] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 3; j <= Cx + 3; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						compShipsMap[I][J] = 'x';
					}
				}
				compShipsMap[Cy][Cx] = '#';
				compShipsMap[Cy][Cx + 1] = '#';
				compShipsMap[Cy][Cx - 1] = '#';
				compShipsMap[Cy][Cx + 2] = '#';
				compShipsMap[Cy][Cx - 2] = '#';
				n++;
			}


		} while (n == 0);
		numberOfShips = 0;
		for (int i = 0; i <= 9; ++i) {
			for (int j = 0; j <= 9; ++j) {
				if (compShipsMap[i][j] == 'x') { // очистка поля от лишних знаков
					compShipsMap[i][j] = 0;
				}
				if (compShipsMap[i][j] == '#') { // подсчёт построенных кораблей
					numberOfShips++;
				}
			}
		}
	}while (numberOfShips < 15);
	drawCompShips();

}

void arrangementOfShipsGamer() {

	int Cx, Cy;
	int numberOfShips = 0;
	do{
		numberOfShips = 0;
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				gamerShipsMap[i][j] = 0;
			}
		}

		//////////////////////////////////////////////////////// постройка одного однопалубного корабля ////////////////////////////////////////
		int n = 0;
		do {
			// очистка поля игрока
			
			Cx = rand() % 10;
			Cy = rand() % 10;
			if (gamerShipsMap[Cy][Cx] == 0) {
				for (int i = Cy - 1; i < Cy + 2; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j < Cx + 2; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-'; // отметка зоны равной одной клетке вокруг корабля
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				n++;
			}
			else {
				continue;
			}
		} while (n == 0);

		/////////////////////////////////////////////////////// постройка одного двухпалубного корабля ///////////////////////////////////////////
		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0)) { // берём координату выше на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1 - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy - 1][Cx] = '*';
				n++;
			}
			// если точка Сy - 1 занята то берём другую точку и проверяем
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0)) {// берём координату ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy; i <= Cy + 2; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy + 1][Cx] = '*';
				n++;
			}
			// если точка Сy + 1 занята то берём другую точку и проверяем
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && gamerShipsMap[Cy][Cx + 1] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 2; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy][Cx + 1] = '*';
				n++;
			}
			// если точка Сx + 1 занята то берём другую точку и проверяем
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx - 1 >= 0 && gamerShipsMap[Cy][Cx - 1] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 2; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy][Cx - 1] = '*';
				n++;
			}


		} while (n == 0);

		/////////////////////////////////////////////////////////////// постройка трёхпалубного корабля ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0)) { // берём координату выше и ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1 - 1; i <= Cy + 1 + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy - 1][Cx] = '*';
				gamerShipsMap[Cy + 1][Cx] = '*';
				n++;
			}
			// если точка Сy - 1  и Сy + 1 занята то проверяем Cx - 1 и Cx + 1
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && gamerShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && gamerShipsMap[Cy][Cx - 1] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1 - 1; j <= Cx + 2; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy][Cx + 1] = '*';
				gamerShipsMap[Cy][Cx - 1] = '*';
				n++;
			}

		} while (n == 0);

		/////////////////////////////////////////////////////////////// постройка четырёхпалубного корабля ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0) && (Cy + 2 <= 9 && gamerShipsMap[Cy + 2][Cx] == 0)) { // берём координату выше и ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 2; i <= Cy + 3; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy - 1][Cx] = '*';
				gamerShipsMap[Cy + 1][Cx] = '*';
				gamerShipsMap[Cy + 2][Cx] = '*';
				n++;
			}
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0) && (Cy - 2 >= 0 && gamerShipsMap[Cy - 2][Cx] == 0)) { // берём координату выше и ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 3; i <= Cy + 2; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy - 1][Cx] = '*';
				gamerShipsMap[Cy - 2][Cx] = '*';
				gamerShipsMap[Cy + 1][Cx] = '*';
				n++;
			}

			// если точка Сy - 1  и Сy + 1 занята то проверяем Cx - 1 и Cx + 1
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && gamerShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && gamerShipsMap[Cy][Cx - 1] == 0) && (Cx - 2 >= 0 && gamerShipsMap[Cy][Cx - 2] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 3; j <= Cx + 2; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy][Cx + 1] = '*';
				gamerShipsMap[Cy][Cx - 1] = '*';
				gamerShipsMap[Cy][Cx - 2] = '*';
				n++;
			}
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && gamerShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && gamerShipsMap[Cy][Cx - 1] == 0) && (Cx + 2 <= 9 && gamerShipsMap[Cy][Cx + 2] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 2; j <= Cx + 3; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy][Cx + 1] = '*';
				gamerShipsMap[Cy][Cx - 1] = '*';
				gamerShipsMap[Cy][Cx + 2] = '*';
				n++;
			}


		} while (n == 0);

		/////////////////////////////////////////////////////////////// постройка пятипалубного корабля ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0) && (Cy + 2 <= 9 && gamerShipsMap[Cy + 2][Cx] == 0) &&
				(Cy - 2 >= 0 && compShipsMap[Cy - 2][Cx] == 0)) { // берём координату выше и ниже на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 3; i <= Cy + 3; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 1; j <= Cx + 1; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy - 1][Cx] = '*';
				gamerShipsMap[Cy + 1][Cx] = '*';
				gamerShipsMap[Cy + 2][Cx] = '*';
				gamerShipsMap[Cy - 2][Cx] = '*';
				n++;
			}

			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && gamerShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && gamerShipsMap[Cy][Cx - 1] == 0) &&
				(Cx + 2 >= 0 && gamerShipsMap[Cy][Cx + 2] == 0) && (Cx - 2 >= 0 && gamerShipsMap[Cy][Cx - 2] == 0)) {// берём координату правее на один от точки Сy Cx и проверяем находится ли она в поле и не занято ли клетка

				for (int i = Cy - 1; i <= Cy + 1; ++i) {
					int I, J;
					if (i < 0)
						I = 0;
					else if (i > 9)
						I = 9;
					else
						I = i;
					for (int j = Cx - 3; j <= Cx + 3; ++j) {
						if (j < 0)
							J = 0;
						else if (j > 9)
							J = 9;
						else
							J = j;
						gamerShipsMap[I][J] = '-';
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				gamerShipsMap[Cy][Cx + 1] = '*';
				gamerShipsMap[Cy][Cx - 1] = '*';
				gamerShipsMap[Cy][Cx + 2] = '*';
				gamerShipsMap[Cy][Cx - 2] = '*';
				n++;
			}


		} while (n == 0);

		numberOfShips = 0;
		for (int i = 0; i <= 9; ++i) {
			for (int j = 0; j <= 9; ++j) {
				if (gamerShipsMap[i][j] == '-') {
					gamerShipsMap[i][j] = 0;
				}
				if (gamerShipsMap[i][j] == '*') {
					numberOfShips++;
				}
			}
		}
	}while (numberOfShips != 15);
	drawGamerShips();


}


void drawCompShips() {
	std::cout << "\x1b[36m";
	std::cout << "++++++++++ поле Компьютера ++++++++++\n\n";
	// прорисовка строчки цифр по оси X
	std::cout << "      ";
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
				if (j == 9) std::cout << "   |";
				else std::cout << "   ";
			}
			else if (compShipsMap[i][j] == 'x') {
				if (j == 9) std::cout << "   |";
				else std::cout << "   ";
			}
			else if (compShipsMap[i][j] == '-') {
				if (j == 9) std::cout << "   |";
				else std::cout << "   ";
			}
			else if (compShipsMap[i][j] == '+') {
				if (j == 9) std::cout << " + |";
				else std::cout << " + ";
			}
			else if (compShipsMap[i][j] == 'X') {
				if (j == 9) std::cout << "[X]|";
				else std::cout << "[X]";
			}

		}
		std::cout << "\n";
	}
	std::cout << "  -";
	for (int i = 0; i < 11; ++i) {
		std::cout << "---";
	}
	std::cout << "\x1b[0m";
	std::cout << std::endl;
}

void drawGamerShips() {
	std::cout << "\x1b[32m";
	std::cout << ">>>>>>>>>>> поле Игрока <<<<<<<<<<<\n\n";
	// прорисовка строчки цифр по оси X
	std::cout << "      ";
	for (int i = 1; i <= 10; ++i) {
		std::cout << i << "  ";
	}
	std::cout << "\n";
	for (unsigned int i = 0; i < 10; ++i) {
		std::cout << "  ";
		if (i == 9) std::cout << i + 1 << " "; // прорисовка столбца цифр по оси Y
		else std::cout << i + 1 << "  ";
		for (unsigned int j = 0; j < 10; ++j) {
			if (gamerShipsMap[i][j] == 0) {
				if (j == 9) std::cout << "   |";
				else std::cout << "   ";
			}
			else if (gamerShipsMap[i][j] == '*') {
				if (j == 9) std::cout << "[ ]|";
				else std::cout << "[ ]";
			}
			else if (gamerShipsMap[i][j] == '-') {
				if (j == 9) std::cout << "   |";
				else std::cout << "   ";
			}
			else if (gamerShipsMap[i][j] == '+') {
				if (j == 9) std::cout << " + |";
				else std::cout << " + ";
			}
			else if (gamerShipsMap[i][j] == 'X') {
				if (j == 9) std::cout << "[X]|";
				else std::cout << "[X]";
			}

		}
		std::cout << "\n";
	}
	std::cout << "  -";
	for (int i = 0; i < 11; ++i) {
		std::cout << "---";
	}
	std::cout << "\x1b[0m";
	std::cout << std::endl;
}

void WelcomeScreen() {
	std::cout << "\x1b[31m" << R"(
                                                                                                               [_]

        [ ]               [ ]      [ ][ ]       [ ][ ][ ]      [ ][ ]     [ ]      [ ]      [ ][ ]       [ ]         [ ]                                                                                                                
        [ ][ ]         [ ][ ]    [ ]    [ ]     [ ]    [ ]   [ ]    [ ]   [ ]    [ ]      [ ]    [ ]     [ ]      [ ][ ]                                                                                                             
        [ ]  [ ]     [ ]  [ ]  [ ]        [ ]   [ ]    [ ]   [ ]          [ ]  [ ]      [ ]        [ ]   [ ]     [ ] [ ]                                                                                                                
        [ ]    [ ] [ ]    [ ]  [ ]        [ ]   [ ][ ][ ]    [ ]          [ ][ ] [ ]    [ ]        [ ]   [ ]    [ ]  [ ]                                                                                                                
        [ ]      [ ]      [ ]  [ ]        [ ]   [ ]          [ ]          [ ]     [ ]   [ ]        [ ]   [ ]  [ ]    [ ]                                                                                                                
        [ ]               [ ]    [ ]    [ ]     [ ]          [ ]    [ ]   [ ]      [ ]    [ ]    [ ]     [ ][ ]      [ ]                                                                                                                
        [ ]               [ ]      [ ][ ]       [ ]            [ ][ ]     [ ]      [ ]      [ ][ ]       [ ]         [ ]                                                                                                                


                                                                              [_]

                                        [ ][ ][ ][ ]       [ ][ ]       [ ]         [ ]
                                        [ ]              [ ]    [ ]     [ ]      [ ][ ]
                                        [ ]            [ ]        [ ]   [ ]     [ ] [ ]
                                        [ ][ ][ ]      [ ]        [ ]   [ ]    [ ]  [ ]
                                        [ ]      [ ]   [ ]        [ ]   [ ]  [ ]    [ ]
                                        [ ]      [ ]     [ ]    [ ]     [ ][ ]      [ ]
                                        [ ][ ][ ]          [ ][ ]       [ ]         [ ]


)" << "\x1b[0m";

	system("pause");
	system("cls");
}

int calcEmptyCells() {
	int numberOfEmptyCells = 0;
	for (int i = 0; i <= 9; ++i) {
		for (int j = 0; j <= 9; ++j) {
			if (gamerShipsMap[i][j] != '+' && gamerShipsMap[i][j] != 'X') {
				numberOfEmptyCells++;
			}
		}
	}
	return numberOfEmptyCells;
}