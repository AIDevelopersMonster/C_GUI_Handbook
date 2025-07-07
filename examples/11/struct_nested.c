#include <stdio.h>

int main() {
    typedef struct {
        int day;
        int month;
        int year;
    } Date;

    typedef struct {
        char title[100];
        char author[50];
        Date publish_date; // Член структуры Date
    } Book;

    Book my_book = {"The C Programming Language", "Dennis Ritchie", {2, 4, 1978}};

    printf("Book: %s by %s, published on %d/%d/%d\n",
           my_book.title, my_book.author,
           my_book.publish_date.day, my_book.publish_date.month, my_book.publish_date.year);

    return 0;
}