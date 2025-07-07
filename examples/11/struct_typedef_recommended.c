#include <stdio.h>

int main() {
    // Объявление и псевдоним для структуры Complex
    typedef struct {
        float real; // Действительная часть
        float imag; // Мнимая часть
    } Complex; // 'Complex' теперь является типом

    Complex z1 = {1.0, 2.5};
    Complex z2;
    z2.real = 3.0;
    z2.imag = -1.5;

    printf("Complex z1: %.1f + %.1fi\n", z1.real, z1.imag);
    printf("Complex z2: %.1f + %.1fi\n", z2.real, z2.imag);

    return 0;
}