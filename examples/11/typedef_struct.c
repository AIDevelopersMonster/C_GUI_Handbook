#include <stdio.h>

int main() {
    // Объявление структуры Point и создание псевдонима Point для нее
    typedef struct {
        int x;
        int y;
    } Point; // 'Point' теперь является псевдонимом для этой анонимной структуры

    Point p1 = {1, 2};
    Point p2 = {3, 4};
    printf("Point p1: (%d, %d)\n", p1.x, p1.y);

    return 0;
}