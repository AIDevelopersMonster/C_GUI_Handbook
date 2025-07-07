#include <stdio.h>

int main() {
    // Создаем псевдоним 'uint' для типа 'unsigned int'
    typedef unsigned int uint;

    uint a = 5; // Теперь 'uint' можно использовать как обычный тип данных
    uint b = 10;
    printf("a + b = %u\n", a + b);

    return 0;
}