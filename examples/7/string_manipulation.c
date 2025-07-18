// string_manipulation.c
// Пример 7.2: Демонстрация работы со строками в C с использованием fgets() и функций из <string.h>.

#include <stdio.h>  // Для функций ввода-вывода, таких как printf и fgets.
#include <string.h> // Для строковых функций, таких как strlen и strcspn.

int main() {
    // Объявляем символьный массив 'name' размером 50 символов.
    // Этого достаточно для хранения строки до 49 символов плюс завершающий нулевой символ '\0'.
    char name[50];

    printf("Введите ваше имя: "); // Запрос ввода у пользователя.

    // fgets() - безопасная функция для чтения строки.
    // Она считывает строку из стандартного ввода (stdin)
    // до символа новой строки '\n' или до (sizeof(name) - 1) символов,
    // записывая их в массив 'name'.
    // Важно: fgets() включает символ '\n' (если он был введен) в строку.
    fgets(name, sizeof(name), stdin);

    // Удаляем символ новой строки ('\n'), который мог быть прочитан fgets().
    // strcspn(name, "\n") находит индекс первого вхождения символа '\n' в строке 'name'.
    // Если '\n' найден, мы заменяем его на нулевой символ '\0',
    // что корректно завершает строку в этом месте.
    // Это критически важно для корректной работы других строковых функций и вывода.
    name[strcspn(name, "\n")] = 0;

    // Выводим приветствие с введенным именем.
    // %s - спецификатор формата для вывода строки.
    printf("Привет, %s!\n", name);

    // strlen(name) - функция из <string.h>, которая возвращает длину строки,
    // исключая завершающий нулевой символ '\0'.
    // %lu - спецификатор формата для вывода значения типа size_t,
    // который возвращает strlen.
    printf("Длина строки: %lu\n", strlen(name));

    // --- Демонстрация других строковых функций (дополнительно) ---

    // strcpy - копирование строки.
    char copied_name[50];
    // strcpy(назначение, источник)
    // Копирует содержимое 'name' в 'copied_name', включая '\0'.
    strcpy(copied_name, name);
    printf("Скопированное имя: %s\n", copied_name);

    // strcmp - сравнение строк.
    char another_name[50];
    strcpy(another_name, "Alice"); // Задаем другую строку для сравнения

    // strcmp возвращает 0, если строки идентичны.
    // Отрицательное значение, если s1 < s2.
    // Положительное значение, если s1 > s2.
    if (strcmp(name, another_name) == 0) {
        printf("Имена одинаковые.\n");
    } else {
        printf("Имена разные.\n");
    }

    // strcat - конкатенация (объединение) строк.
    char full_message[100];
    strcpy(full_message, "Hello, "); // Инициализируем начальную часть
    // strcat(назначение, источник)
    // Добавляет содержимое 'name' в конец 'full_message'.
    strcat(full_message, name);
    strcat(full_message, "!"); // Добавляем восклицательный знак
    printf("Полное сообщение: %s\n", full_message);


    // --- Важное замечание о строковых литералах и указателях ---
    // char *msg = "Hello, world!";
    // Этот способ создает указатель на строковый литерал.
    // Строковые литералы часто хранятся в памяти, доступной только для чтения.
    // ПОПЫТКА ИЗМЕНИТЬ 'msg[0] = 'X';' ПРИВЕДЕТ К ОШИБКЕ ВЫПОЛНЕНИЯ ИЛИ КРАХУ ПРОГРАММЫ!
    // char *msg_ptr = "Это строка только для чтения!";
    // printf("Строковый литерал: %s\n", msg_ptr);


    // Возвращаем 0 для успешного завершения.
    return 0;
}
