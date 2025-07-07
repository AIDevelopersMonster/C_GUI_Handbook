#include <stdio.h>
#include <string.h> // Для strcpy

int main() {
    // Пример использования struct и union вместе (таггированное объединение)
    typedef enum { INT_TYPE, FLOAT_TYPE, STRING_TYPE } DataType;

    typedef struct {
        DataType type; // Индикатор, какой тип данных активен в union
        union {
            int i_val;
            float f_val;
            char s_val[50];
        } value; // Имя для поля union
    } MyVariant;

    MyVariant v1;
    v1.type = INT_TYPE;
    v1.value.i_val = 123;
    printf("Variant 1 (int): %d\n", v1.value.i_val);

    MyVariant v2;
    v2.type = STRING_TYPE;
    strcpy(v2.value.s_val, "Variant String");
    printf("Variant 2 (string): %s\n", v2.value.s_val);

    return 0;
}