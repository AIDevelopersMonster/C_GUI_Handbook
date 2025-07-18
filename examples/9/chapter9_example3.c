#include <stdio.h>  // Подключаем стандартную библиотеку ввода/вывода
#include <string.h> // Подключаем библиотеку для работы со строками (для strcspn)

int main() {
    // Объявляем символьный массив (строку) размером 20 символов.
    // Этого достаточно для 19 символов + завершающий нулевой символ '\0'.
    char name[20];

    printf("Введите имя: ");

    //  БЕЗОПАСНЫЙ ввод строки с помощью fgets
    // 1. name: указатель на буфер, куда будут записаны символы.
    // 2. sizeof(name): максимальное количество символов для чтения (включая '\0').
    //    fgets прочитает до (размер буфера - 1) символа ИЛИ до символа новой строки.
    // 3. stdin: файловый поток, откуда читать (стандартный ввод, т.е. клавиатура).
    // fgets возвращает NULL в случае ошибки или EOF.
    if (fgets(name, sizeof(name), stdin) != NULL) {
        // fgets сохраняет символ новой строки '\n', если он был прочитан и поместился в буфер.
        // Это часто нежелательно, поэтому удаляем его.
        name[strcspn(name, "\n")] = '\0'; // strcspn находит индекс первого '\n' и заменяет его на '\0'

        printf("Привет, %s!\n", name);
    } else {
        printf("Ошибка при чтении имени.\n");
    }

    return 0;
}