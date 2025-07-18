// chapter9_example1.c
// Этот файл демонстрирует базовый ввод/вывод в C с использованием функций printf и scanf.

#include <stdio.h> // Это строка включает стандартную библиотеку ввода-вывода (Standard Input/Output).
                   // Она содержит функции, такие как printf (для вывода на экран) и scanf (для чтения ввода).

int main() { // Это основная функция программы. Выполнение любой программы на C начинается здесь.
             // 'int' означает, что функция вернет целочисленное значение (обычно 0 при успешном выполнении).

    int age; // Объявляем целочисленную переменную с именем 'age'.
             // Здесь будет храниться возраст, введенный пользователем.

    printf("Введите ваш возраст: "); // Выводит на консоль сообщение "Введите ваш возраст: ".
                                   // 'printf' используется для форматированного вывода.

    scanf("%d", &age); // Считывает целочисленное значение, введенное пользователем, и сохраняет его в переменной 'age'.
                       // '%d' - это спецификатор формата для чтения целого числа.
                       // '&age' - это "адрес" переменной 'age'. 'scanf' нужен адрес, чтобы знать, куда сохранить введенное значение.

    printf("Ваш возраст: %d\n", age); // Выводит на консоль сообщение "Ваш возраст: " с введенным значением возраста.
                                     // '%d' здесь используется для вывода значения целочисленной переменной 'age'.
                                     // '\n' - это символ новой строки, который перемещает курсор на следующую строку после вывода.

    return 0; // Возвращает 0, чтобы показать, что программа завершилась успешно.
              // Это стандартная практика для функции 'main'.
}