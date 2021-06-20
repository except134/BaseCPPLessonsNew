#include "Lesson7PCH.h"

// �������� ������ �� 2� cpp ������ � �������������(main.cpp, mylib.cpp, mylib.h) 
// �� ������ ������ mylib �������� 3 �������: ��� ������������� �������(���� float), 
// ������ ��� �� ����� � �������� ���������� ������������� � ������������� ���������.��������� ��� 3 - � ������� �� main ��� ������ � ��������.

void Tasks::Task1()
{
	std::cout << "=================== ������ 1 ===================" << std::endl << std::endl;

	std::cout << "����������� � ������ 5." << std::endl;

	std::cout << std::endl << std::endl;
}

// ������� ������������(����� ��������� define), �����������, ������ �� ���������� �� �����(��������� � ����������) 
// � �������� �� ����(������������) �� ����������� �� ������� ���������(�������������) � ���������� true ��� false, 
// ������� �� ����� �true� ��� �false�.

#define TASK2_MACROS(a, b) a>=0 && a<b ? true : false

void Tasks::Task2()
{
	std::cout << "=================== ������ 2 ===================" << std::endl << std::endl;

	std::cout << "������� ����� ��� ��������: ";
	int num;
	std::cin >> num;

	std::cout << "������� ������������ �����: ";
	int numMax;
	std::cin >> numMax;

	bool result = TASK2_MACROS(num, numMax);

	std::cout << "����� " << num << (result ? " ������" : " �� ������") << " � �������� 0-" << numMax-1;

	std::cout << std::endl << std::endl;
}

// ������� ������ ���� int.����� ��� ������ �������� ����� ��������� ������������� #define.
// ��������������� ��� ����� ���� � ����������.�������� ��� ���� ���� ������� ����������(�������� ���������).
// ���������� ������������ ��������� ��� ������������ SwapINT(a, b).��������� �� �� ����� ����������.

#define ARR_SIZE 5

#define SwapINT(a, b) std::swap(a, b)

void Tasks::Task3PrintArray(int* arr, int sz)
{
	for (int i = 0; i < sz; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

void Tasks::Task3SortArray(int* arr, int sz)
{
	for (int i = 0; i < sz - 1; i++) {
		for (int j = 0; j < sz - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				SwapINT(arr[j], arr[j + 1]);
			}
		}
	}
}

void Tasks::Task3()
{
	std::cout << "=================== ������ 3 ===================" << std::endl << std::endl;

	int arr[ARR_SIZE];

	std::cout << "������� ����a ����� ������ ��� ������� �� " << ARR_SIZE << " ���������: " << std::endl;

	for (int i = 0; i < ARR_SIZE; i++) {
		std::cout << "������� ����� " << i+1 << ": ";
		std::cin >> arr[i];
	}

	std::cout << "������ �� ����������: ";
	Task3PrintArray(arr, ARR_SIZE);

	Task3SortArray(arr, ARR_SIZE);

	std::cout << "������ ����� ����������: ";
	Task3PrintArray(arr, ARR_SIZE);

	std::cout << std::endl << std::endl;
}

// �������� ��������� ��������� � ���������� ������.�������� ��� ��� ���������� ������������ � ������� ��������� pragma pack.
// �������� ����������� ���������� ����� ����.��������������� ��.�������� �� �� ����� � �� ������ � ������� sizeof.��������� ��� ��������� � ��������� ����.

std::stringstream Tasks::Task4OutString(Employer* employer)
{
	std::stringstream ss;
	ss << "\tID       = " << employer->id << std::endl;
	ss << "\t���      = " << employer->name << std::endl;
	ss << "\t�������  = " << employer->age << std::endl;
	ss << "\t�������� = " << employer->salary << std::endl;
	return ss;
}

void Tasks::Task4()
{
	std::cout << "=================== ������ 4 ===================" << std::endl << std::endl;

	std::unique_ptr<Employer> employer = std::make_unique<Employer>();
	employer->id = 1;
	employer->name = "My Name";
	employer->age = 33;
	employer->salary = 1234.56;

	std::cout << "������ ��������� ���������: " << sizeof(Employer) << " �����" << std::endl;

	std::cout << "���������� ��������� ���������: " << std::endl;
	std::cout << Task4OutString(employer.get()).str();

	std::fstream fout("emloyer.txt", std::ios::trunc | std::ios::out);
	fout << Task4OutString(employer.get()).str();
	fout.close();

	std::cout << std::endl << std::endl;
}

// �������� ������� 1 ������� ���� ��������� �� ������ ������(������ ������� ����� ����� �� ������).
// �������� ������ �� 2� cpp ������ � �������������(main.cpp, mylib.cpp, mylib.h) 
// �� ������ ������ mylib �������� 3 �������: ��� ������������� �������(���� float), 
// ������ ��� �� ����� � �������� ���������� ������������� � ������������� ���������.��������� ��� 3 - � ������� �� main ��� ������ � ��������.

namespace nsTask5
{
	std::mt19937 Generator((unsigned int)(std::chrono::high_resolution_clock::now().time_since_epoch().count() ^ (size_t)(new char)));

	float GenerateRandomFloat(float m, float s)
	{
		std::normal_distribution<float> distr(m, s); 
		return distr(Generator);
	}

	void InitializeArray(float* var, size_t sz)
	{
		for (int i = 0; i < sz; i++) {
			var[i] = GenerateRandomFloat(0, 1);
		}
	}

	void PrintArray(float* var, size_t sz) 
	{
		for (int i = 0; i < sz; i++) {
			std::cout << var[i] << " ";
		}
		std::cout << std::endl;
	}
	
	void CalculateArray(float* var, size_t sz) 
	{
		int negnums = 0, notnegnums = 0;
		for (int i = 0; i < sz; i++) {
			var[i] < 0 ? negnums++ : notnegnums++;
		}

		std::cout << "������������� ��������� " << notnegnums << ", ������������� " << negnums << std::endl;
	}
}

void Tasks::Task5()
{
	std::cout << "=================== ������ 5 ===================" << std::endl << std::endl;

	const int Size = 10;
	float arr[Size];

	std::cout << "�������������� ������ ���������� float ������� �� " << Size << " ���������." << std::endl;
	nsTask5::InitializeArray(arr, Size);

	std::cout << "���������� ������: ";
	nsTask5::PrintArray(arr, Size);

	std::cout << "������������ ������������� � ������������� �������� �������: " << std::endl;
	nsTask5::CalculateArray(arr, Size);

	std::cout << std::endl << std::endl;
}
