﻿#include "Lesson5PCH.h"

/*
1. Написать функцию которая выводит массив double чисел на экран. Параметры функции это сам массив и его размер. Вызвать эту функцию из main.
2. Задать целочисленный массив, состоящий из элементов 0 и 1. Например: [ 1, 1, 0, 0, 1, 0, 1, 1, 0, 0 ]. Написать функцию, заменяющую в принятом массиве 0 на 1, 1 на 0. 
   Выводить на экран массив до изменений и после.
3. Задать пустой целочисленный массив размером 8. Написать функцию, которая с помощью цикла заполнит его значениями 1 4 7 10 13 16 19 22. Вывести массив на экран.
4. Написать функцию, которой на вход подаётся одномерный массив и число n (может быть положительным, или отрицательным), 
   при этом метод должен циклически сместить все элементы массива на n позиций.
5. Написать функцию, которой передается не пустой одномерный целочисленный массив, она должна вернуть истину если в массиве есть место, 
   в котором сумма левой и правой части массива равны. Примеры: checkBalance([1, 1, 1, || 2, 1]) → true, checkBalance ([2, 1, 1, 2, 1]) → false, checkBalance ([10, || 1, 2, 3, 4]) → true. 
   Абстрактная граница показана символами ||, эти символы в массив не входят.
*/

int main()
{
	setlocale(LC_ALL, "");

	Tasks tasks;

	tasks.Task1();
	tasks.Task2();
	tasks.Task3();	
	tasks.Task4();
	tasks.Task5();

	return 0;
}

