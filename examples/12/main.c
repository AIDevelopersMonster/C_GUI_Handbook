#include <stdio.h>       // Стандартная библиотека ввода/вывода
#include "math_utils.h"  // Включаем собственный заголовочный файл с объявлениями функций

#define DEBUG // Определяем макрос DEBUG. Попробуйте закомментировать эту строку, чтобы увидеть разницу.

int main() {
#ifdef DEBUG // Если макрос DEBUG определен...
    printf("Debug mode is ON\n"); // ...этот вывод будет скомпилирован и показан
#endif

    int sum = add(5, 3);
    int product = multiply(4, 2);

    printf("Sum: %d, Product: %d\n", sum, product);
    return 0;
}