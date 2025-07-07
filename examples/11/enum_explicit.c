#include <stdio.h>

int main() {
    enum Status { OK = 0, WARNING = 1, ERROR = 100, CRITICAL }; // CRITICAL будет 101

    enum Status current_status = ERROR;
    printf("Current status (enum value): %d\n", current_status); // Выведет 100

    enum Status another_status = CRITICAL;
    printf("Another status (enum value): %d\n", another_status); // Выведет 101

    return 0;
}