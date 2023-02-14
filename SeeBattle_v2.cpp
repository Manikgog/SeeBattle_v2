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
point p;// ���������� ���������� �������� ����������
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
		clearFilds(); //��������� �������� ����� ����
		std::cout << "������� ��� ��� -> ";
		std::cin >> name;
		std::cout << "������, " << name << "!\n";
		srand((unsigned int)time(NULL));
		arrangementOfShipsComp();
		compShips = calcCompShips();
		std::cout << "\n��������� ���������� ����� ���������� -> " << compShips << std::endl;
		arrangementOfShipsGamer();
		int gamerShips = calcGamerShips();
		std::cout << "\n��������� ���������� ����� ������ -> " << gamerShips << std::endl;
		p.raw = rand() % 10;
		p.col = rand() % 10;

		while (calcCompShips() > 0 && calcGamerShips() > 0) {
			srand((unsigned int)time(NULL));

			// �������� ������
			gamerShooting();
			compShips = calcCompShips();
			
			std::cout << "� ��������� �������� " << compShips << std::endl;

			// �������� ����������
			do {
				result = compShooting();
				drawGamerShips();
			} while (result);
			//drawGamerShips();

			gamerShips = calcGamerShips();
			
			std::cout << "� ������ �������� " << gamerShips << std::endl;
		}

		if (compShips == 0)
			std::cout << "\x1b[32m��������� ��������!\x1b[0m\n\n\n";
		if (gamerShips == 0)
			std::cout << "\n\n\n\x1b[31m " << name << " ��������!\x1b[0m \n";
		system("pause");
		do {
			system("cls");
			std::cout << "������ ������� ���? y/n ";
			std::cin >> key;
		} while (key != 'y' && key != 'n');
		
	} while (key != 'n');

	return 0;
}

char Dec_to_alpha(int row) {
	char A ='z';
	switch (row) {
	case 1:
		A = 'a';
		break;
	case 2:
		A = 'b';
		break;
	case 3:
		A = 'c';
		break;
	case 4:
		A = 'd';
		break;
	case 5:
		A = 'e';
		break;
	case 6:
		A = 'f';
		break;
	case 7:
		A = 'g';
		break;
	case 8:
		A = 'h';
		break;
	case 9:
		A = 'i';
		break;
	case 10:
		A = 'j';
		break;
	}

	return A;
}

int alpha_to_dec(char A) {
	int row = 1;
	switch (A) {
	case 'A':
		row = 1;
		break;
	case 'a':
		row = 1;
		break;
	case 'B':
		row = 2;
		break;
	case 'b':
		row = 2;
		break;
	case 'C':
		row = 3;
		break;
	case 'c':
		row = 3;
		break;
	case 'D':
		row = 4;
		break;
	case 'd':
		row = 4;
		break;
	case 'E':
		row = 5;
		break;
	case 'e':
		row = 5;
		break;
	case 'F':
		row = 6;
		break;
	case 'f':
		row = 6;
		break;
	case 'G':
		row = 7;
		break;
	case 'g':
		row = 7;
		break;
	case 'H':
		row = 8;
		break;
	case 'h':
		row = 8;
		break;
	case 'I':
		row = 9;
		break;
	case 'i':
		row = 9;
		break;
	case 'J':
		row = 10;
		break;
	case 'j':
		row = 10;
		break;
	default:
		row = 11;
	}
	return row;
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

	// ���� � ������� �� ������ � ������ ������ ������������ ������� (�, +) ��������
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

	// ���� ���������� ������ ������ ������ 75
	// ���� �� ������� ������, �� ���� �� ��������� �� ���������
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
		// ���� �� ������� ������ (�������� ������) � ������������� ��������
		// ����� �������� ������ ������
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
		int firstQuadEmptyCells = 0; // ���������� ������ ������ � ������ ���������
		int secondQuadEmptyCells = 0; // ���������� ������ ������ �� ������ ���������
		int thirdQuadEmptyCells = 0; // ���������� ������ ������ � ������� ���������
		int fouthQuadEmptyCells = 0; // ���������� ������ ������ � ��������� ���������
		int max = 0;
		// ������� ���������� ������ ������ � ������ ���������
		for (int i = 0; i <= 4; ++i) {
			for (int j = 0; j <= 4; ++j) {
				if (gamerShipsMap[i][j] != '+' && gamerShipsMap[i][j] != 'X') {
					firstQuadEmptyCells++;
				}
			}
		}
		// ������� ���������� ������ ������ �� ������ ���������
		for (int i = 0; i <= 4; ++i) {
			for (int j = 5; j <= 9; ++j) {
				if (gamerShipsMap[i][j] != '+' && gamerShipsMap[i][j] != 'X') {
					secondQuadEmptyCells++;
				}
			}
		}
		// ������� ���������� ������ ������ � ������� ���������
		for (int i = 5; i <= 9; ++i) {
			for (int j = 0; j <= 4; ++j) {
				if (gamerShipsMap[i][j] != '+' && gamerShipsMap[i][j] != 'X') {
					thirdQuadEmptyCells++;
				}
			}
		}
		// ������� ���������� ������ ������ � �������� ���������
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
		char str[20];
		x = 0; y = 0;
		do {
			std::cout << "������� ���������� ������ (a - j) -> ";
			std::cin >> str;
			y = alpha_to_dec(str[0]);	
		} while (y < 1 || y > 10);

		do {
			std::cout << "������� ���������� ������� (1 - 10) -> ";
			std::cin >> str;
			x = std::atoi(str);
		} while (x < 1 || x > 10);
		
		x--; y--;
		// ���� �����
		if (compShipsMap[y][x] == '#') {
			compShipsMap[y][x] = 'X';
			result = true;
		}
		// ���� �� �����
		else if(compShipsMap[y][x] == 0) {
			compShipsMap[y][x] = '+'; // �������� ������, ����� �������� ���� �� ��������
		}
		// ���� ����� ���� ���� ��� �������
		else if (compShipsMap[y][x] == 'X' || compShipsMap[y][x] == '+') {
			std::cout << "\x1b[31m������������ ������� ����������!\x1b[0m\n";
		}
		// ������� ���������� ���������� �������� � ����������
		compShips = calcCompShips();
		if (compShips == 0) break;
		std::cout << "� ���������� �������� " << compShips << std::endl;
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

		//////////////////////////////////////////////////////// ��������� ������ ������������� ������� ////////////////////////////////////////
		int n = 0;
		do {
			// ������� ���� ����������
			

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
						compShipsMap[I][J] = 'x'; // ������� ���� ������ ����� ������ ������ �������
					}
				}
				compShipsMap[Cy][Cx] = '#';
				n++;
			}
			else {
				continue;
			}
		} while (n == 0);

		/////////////////////////////////////////////////////// ��������� ������ ������������� ������� ///////////////////////////////////////////
		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0)) { // ���� ���������� ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			// ���� ����� �y - 1 ������ �� ���� ������ ����� � ���������
			else if ((compShipsMap[Cy][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0)) {// ���� ���������� ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			// ���� ����� �y + 1 ������ �� ���� ������ ����� � ���������
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && compShipsMap[Cy][Cx + 1] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			// ���� ����� �x + 1 ������ �� ���� ������ ����� � ���������
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx - 1 >= 0 && compShipsMap[Cy][Cx - 1] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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

		/////////////////////////////////////////////////////////////// ��������� ������������ ������� ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0)) { // ���� ���������� ���� � ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			// ���� ����� �y - 1  � �y + 1 ������ �� ��������� Cx - 1 � Cx + 1
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && compShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && compShipsMap[Cy][Cx - 1] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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

		/////////////////////////////////////////////////////////////// ��������� ��������������� ������� ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0) && (Cy + 2 <= 9 && compShipsMap[Cy + 2][Cx] == 0)) { // ���� ���������� ���� � ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			else if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0) && (Cy - 2 >= 0 && compShipsMap[Cy - 2][Cx] == 0)) { // ���� ���������� ���� � ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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

			// ���� ����� �y - 1  � �y + 1 ������ �� ��������� Cx - 1 � Cx + 1
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && compShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && compShipsMap[Cy][Cx - 1] == 0) && (Cx - 2 >= 0 && compShipsMap[Cy][Cx - 2] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			else if ((compShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && compShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && compShipsMap[Cy][Cx - 1] == 0) && (Cx + 2 <= 9 && compShipsMap[Cy][Cx + 2] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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

		/////////////////////////////////////////////////////////////// ��������� ������������� ������� ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((compShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && compShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && compShipsMap[Cy + 1][Cx] == 0) && (Cy + 2 <= 9 && compShipsMap[Cy + 2][Cx] == 0) &&
				(Cy - 2 >= 0 && compShipsMap[Cy - 2][Cx] == 0)) { // ���� ���������� ���� � ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
				(Cx + 2 >= 0 && compShipsMap[Cy][Cx + 2] == 0) && (Cx - 2 >= 0 && compShipsMap[Cy][Cx - 2] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
				if (compShipsMap[i][j] == 'x') { // ������� ���� �� ������ ������
					compShipsMap[i][j] = 0;
				}
				if (compShipsMap[i][j] == '#') { // ������� ����������� ��������
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

		//////////////////////////////////////////////////////// ��������� ������ ������������� ������� ////////////////////////////////////////
		int n = 0;
		do {
			// ������� ���� ������
			
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
						gamerShipsMap[I][J] = '-'; // ������� ���� ������ ����� ������ ������ �������
					}
				}
				gamerShipsMap[Cy][Cx] = '*';
				n++;
			}
			else {
				continue;
			}
		} while (n == 0);

		/////////////////////////////////////////////////////// ��������� ������ ������������� ������� ///////////////////////////////////////////
		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0)) { // ���� ���������� ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			// ���� ����� �y - 1 ������ �� ���� ������ ����� � ���������
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0)) {// ���� ���������� ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			// ���� ����� �y + 1 ������ �� ���� ������ ����� � ���������
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && gamerShipsMap[Cy][Cx + 1] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			// ���� ����� �x + 1 ������ �� ���� ������ ����� � ���������
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx - 1 >= 0 && gamerShipsMap[Cy][Cx - 1] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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

		/////////////////////////////////////////////////////////////// ��������� ������������ ������� ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0)) { // ���� ���������� ���� � ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			// ���� ����� �y - 1  � �y + 1 ������ �� ��������� Cx - 1 � Cx + 1
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && gamerShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && gamerShipsMap[Cy][Cx - 1] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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

		/////////////////////////////////////////////////////////////// ��������� ��������������� ������� ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0) && (Cy + 2 <= 9 && gamerShipsMap[Cy + 2][Cx] == 0)) { // ���� ���������� ���� � ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0) && (Cy - 2 >= 0 && gamerShipsMap[Cy - 2][Cx] == 0)) { // ���� ���������� ���� � ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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

			// ���� ����� �y - 1  � �y + 1 ������ �� ��������� Cx - 1 � Cx + 1
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && gamerShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && gamerShipsMap[Cy][Cx - 1] == 0) && (Cx - 2 >= 0 && gamerShipsMap[Cy][Cx - 2] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
			else if ((gamerShipsMap[Cy][Cx] == 0) && (Cx + 1 <= 9 && gamerShipsMap[Cy][Cx + 1] == 0) && (Cx - 1 >= 0 && gamerShipsMap[Cy][Cx - 1] == 0) && (Cx + 2 <= 9 && gamerShipsMap[Cy][Cx + 2] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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

		/////////////////////////////////////////////////////////////// ��������� ������������� ������� ////////////////////////////////////////////////////////////////////////

		n = 0;
		do {
			Cx = rand() % 10;
			Cy = rand() % 10;

			if ((gamerShipsMap[Cy][Cx] == 0) && (Cy - 1 >= 0 && gamerShipsMap[Cy - 1][Cx] == 0) && (Cy + 1 <= 9 && gamerShipsMap[Cy + 1][Cx] == 0) && (Cy + 2 <= 9 && gamerShipsMap[Cy + 2][Cx] == 0) &&
				(Cy - 2 >= 0 && compShipsMap[Cy - 2][Cx] == 0)) { // ���� ���������� ���� � ���� �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
				(Cx + 2 >= 0 && gamerShipsMap[Cy][Cx + 2] == 0) && (Cx - 2 >= 0 && gamerShipsMap[Cy][Cx - 2] == 0)) {// ���� ���������� ������ �� ���� �� ����� �y Cx � ��������� ��������� �� ��� � ���� � �� ������ �� ������

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
	std::cout << "++++++++++ ���� ���������� ++++++++++\n\n";
	// ���������� ������� ���� �� ��� X
	std::cout << "      ";
	for (int i = 1; i <= 10; ++i) {
		std::cout << i << "  ";
	}
	std::cout << "\n";
	for (unsigned int i = 0; i < 10; ++i) {
		std::cout << "  ";
		std::cout << Dec_to_alpha(i + 1) << "  "; // ���������� ������� ���� �� ��� Y
		
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
	std::cout << ">>>>>>>>>>> ���� ������ <<<<<<<<<<<\n\n";
	// ���������� ������� ���� �� ��� X
	std::cout << "      ";
	for (int i = 1; i <= 10; ++i) {
		std::cout << i << "  ";
	}
	std::cout << "\n";
	for (unsigned int i = 0; i < 10; ++i) {
		std::cout << "  ";
		std::cout << Dec_to_alpha(i + 1) << "  "; // ���������� ������� ���� �� ��� Y
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