#include <stdio.h>
#include <string.h> // Для strcpy

int main() {
    union Data {
        int i;        // Целое число
        float f;      // Число с плавающей точкой
        char str[20]; // Массив символов (строка)
    };

    union Data data; // Объявление переменной объединения

    // Присваиваем значение int
    data.i = 10;
    printf("Data as int: %d\n", data.i);
    // Если теперь мы попытаемся прочитать data.f или data.str, то получим мусор,
    // так как область памяти была переписана для int.

    // Присваиваем значение float (перезаписывает предыдущее значение int)
    data.f = 2.5f;
    printf("Data as float: %.1f\n", data.f);

    // Присваиваем значение string (перезаписывает предыдущее значение float)
    strcpy(data.str, "Hello Union!"); // Для строк используем strcpy
    printf("Data as string: %s\n", data.str);

    return 0;
}