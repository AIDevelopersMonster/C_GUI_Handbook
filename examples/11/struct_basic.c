#include <stdio.h>

int main() {
    // Объявление структуры Person
    struct Person {
        char name[50]; // Массив символов для имени
        int age;       // Целое число для возраста
        float height;  // Число с плавающей точкой для роста
    };

    // Инициализация переменной структуры
    struct Person user = {"Alice", 30, 1.75f};

    // Доступ к членам структуры через оператор точки '.'
    printf("User Name: %s\n", user.name);
    printf("User Age: %d\n", user.age);
    printf("User Height: %.2f meters\n", user.height);

    return 0;
}