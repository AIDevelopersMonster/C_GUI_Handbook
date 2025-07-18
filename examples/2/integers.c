#include <stdio.h> // Включаем стандартную библиотеку ввода/вывода (Standard Input/Output).
                   // Она необходима для использования функции printf().

void main (void)   // Объявление главной функции программы.
                   // 'void' в скобках означает, что функция не принимает аргументов.
                   // 'void' перед main означает, что функция ничего не возвращает.
{
int a;             // Объявляем целочисленную переменную 'a'. Она может хранить целые числа (без дробной части).
int b = 5;         // Объявляем целочисленную переменную 'b' и сразу инициализируем (присваиваем) ей значение 5.
int c;             // Объявляем целочисленную переменную 'c'.

a = 7;             // Присваиваем переменной 'a' значение 7.

c = a + b;         // Выполняем арифметическую операцию сложения:
                   // Складываем значения переменных 'a' (7) и 'b' (5),
                   // и результат (12) присваиваем переменной 'c'.

printf ("The sum of adding %d and %d is %d\n", a, b, c);
                   // Выводим результат на консоль.
                   // %d - это спецификатор формата, используемый для вывода целых чисел.
                   // Первый %d будет заменен значением 'a', второй - 'b', третий - 'c'.
                   // \n - это символ новой строки, который переводит курсор на следующую строку после вывода текста.
}