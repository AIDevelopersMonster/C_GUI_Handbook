#include <stdio.h>
#include <string.h> // Не забудьте включить для работы со строковыми функциями

int main() {
    char str1[50] = "Hello"; // Объявляем массив достаточного размера
    char str2[] = "World";

    strcat(str1, " "); // Добавляем пробел к str1
    strcat(str1, str2); // Добавляем str2 к str1

    printf("Result: %s\n", str1); // Вывод: "Hello World"
    printf("Length: %zu\n", strlen(str1)); // Вывод: "Length: 11" (5 + 1 + 5)

    return 0;
}