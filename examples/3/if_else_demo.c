/**
 * @file if_else_demo.c
 * @brief Демонстрация использования операторов if и else, а также цепочки if-else if-else.
 *
 * 'if' позволяет выполнять код, если условие истинно.
 * 'else' позволяет выполнять код, если условие в 'if' ложно.
 * 'else if' позволяет проверять дополнительные условия, если предыдущие были ложны.
 */

#include <stdio.h> // Подключение стандартной библиотеки ввода/вывода для функции printf.

int main() {       // Главная функция, с которой начинается выполнение программы.

    // --- Пример 1: Простой if-else для проверки возраста ---
    int age = 18;  // Объявляем переменную 'age' и инициализируем её значением 18.

    // Если 'age' больше или равен 18, выполнится первый блок.
    // Иначе (если 'age' меньше 18), выполнится блок 'else'.
    if (age >= 18) {
        printf("Пример 1: Возраст %d -> Доступ разрешён\n", age);
    } else {
        printf("Пример 1: Возраст %d -> Доступ запрещён\n", age);
    }

    // --- Пример 2: Цепочка if-else if-else для оценки ---
    int score = 85; // Объявляем переменную 'score' и инициализируем её значением 85.

    // Условия проверяются последовательно сверху вниз.
    // Как только находится истинное условие, соответствующий блок кода выполняется,
    // и остальная часть цепочки if-else if-else пропускается.
    if (score >= 90) { // Если score 90 или выше
        printf("Пример 2: Оценка %d -> Отлично!\n", score);
    } else if (score >= 70) { // Иначе, если score 70 или выше (но меньше 90)
        printf("Пример 2: Оценка %d -> Хорошо\n", score); // Этот блок будет выполнен, т.к. 85 >= 70
    } else if (score >= 50) { // Иначе, если score 50 или выше (но меньше 70)
        printf("Пример 2: Оценка %d -> Удовлетворительно\n", score);
    } else { // Иначе (если score меньше 50)
        printf("Пример 2: Оценка %d -> Неудовлетворительно\n", score);
    }

    // --- Пример 3: if без else ---
    int temperature = 28;
    if (temperature > 25) { // Если температура выше 25
        printf("Пример 3: Температура %d -> Жарко!\n", temperature);
    }
    // Если условие ложно, ничего не происходит (нет блока else).

    return 0; // Возвращаем 0, сигнализируя об успешном завершении программы.
}