#include <stdio.h>

int main() {
    enum Color { RED, GREEN, BLUE }; // RED=0, GREEN=1, BLUE=2

    enum Color favorite_color = GREEN; // Присваиваем одно из именованных значений
    printf("Favorite color (enum value): %d\n", favorite_color); // Выведет 1

    if (favorite_color == RED) {
        printf("Color is Red\n");
    } else if (favorite_color == GREEN) {
        printf("Color is Green\n");
    }

    return 0;
}