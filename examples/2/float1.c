#include <stdio.h> // Включаем стандартную библиотеку ввода/вывода.
                   // Необходима для функции printf().

void main (void)   // Главная функция программы.
{
float a;           // Объявляем переменную 'a' типа float.
                   // 'float' используется для хранения чисел с плавающей точкой (дробных чисел).
float b = 4.678;   // Объявляем переменную 'b' типа float и инициализируем ее значением 4.678.
float c;           // Объявляем переменную 'c' типа float.

a = 3.234;         // Присваиваем переменной 'a' значение 3.234.

c = a + b;         // Складываем значения переменных 'a' (3.234) и 'b' (4.678),
                   // и результат (7.912) присваиваем переменной 'c'.
                   // Операция выполняется с плавающей точкой.

printf ("The sum of adding %f and %f is %f\n", a, b, c);
                   // Выводим результат на консоль.
                   // %f - это спецификатор формата, используемый для вывода чисел с плавающей точкой (float).
                   // Первый %f будет заменен значением 'a', второй - 'b', третий - 'c'.
}
