#include "Lesson3DLLPCH.h"

/*
�������� ���������, ����������� ��������� a* (b + (c / d)) � ��������� ��������� � ��������� ������, ��� a, b, c, d � 
������������� ���������.����������� static_cast ��� �Style cast � float ����� ��������� ������ �������.
���� ����� �����.���� ��� ������ ��� ����� 21, �� �������� �� ����� ������� ����� ���� ������ � ������ 21. 
���� �� �������� ����� ������, ��� 21, ���������� ������� ��������� ������� ����� ���� ������ � 21. 
��� ���������� ������� ������� ������������ ��������� ��������(? : ).
* ������� ��������� ������������� ������, �������� 3�3�3 � ��������� �� �������� ������ ������� � ��� ������ �������� 
������������� ������� �� ����� �������� ����������� ������ ������������� ����[1][1][1].
* *�������� ���������, ����������� ��������� �� ������� �������, � ���������� ��� �� ��������� 
� ���������������� � ������ cpp �����.����������� extern.
*/

int a{};
int b{};
int c{};
int d{};

int* aaa = nullptr;
int* ccc = &aaa;


void Task1()
{
	std::cout << "=================== Task 1 ===================" << std::endl;

	std::cout << "Enter 1 number: ";
	std::cin >> a;
	std::cout << "Enter 2 number: ";
	std::cin >> b;
	std::cout << "Enter 3 number: ";
	std::cin >> c;

	while (d == 0) {
		std::cout << "Enter 4 number (not 0): ";
		std::cin >> d;
	}

	float result = a * (b + (static_cast<float>(c) / d));

	std::cout << "Result is: " << result << std::endl << std::endl;

}

void Task2()
{
	std::cout << "=================== Task 2 ===================" << std::endl;

	std::cout << "Enter integer number: ";
	std::cin >> a;

	b = a <= 21 ? 21 - a : (a - 21) << 1;

	std::cout << "Result is: " << b << std::endl << std::endl;
}

void Task3()
{
	std::cout << "=================== Task 3 ===================" << std::endl;

	int myArray[3][3][3]{};
	int* ptrArray = &myArray[0][0][0];
	ptrArray += sizeof(int) * 3 + 1;
	*ptrArray = 1;

	std::cout << "Result is: " << *ptrArray << std::endl << std::endl;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				std::cout << myArray[i][j][k];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}


}

