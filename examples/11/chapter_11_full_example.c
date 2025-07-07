#include <stdio.h> // Для printf
#include <string.h> // Для strcpy

// Используем typedef для создания псевдонима Item для нашей структуры
typedef struct {
    int id;
    char name[20];
    float price;
} Item;

// Используем enum для категорий товаров
enum Category { ELECTRONICS, BOOKS, CLOTHING, FOOD };

// Структура для товара с использованием enum и вложенной структуры
typedef struct {
    Item details; // Вложенная структура Item
    enum Category category;
    int quantity;
} InventoryItem;

int main() {
    // Создаем экземпляр Item
    Item item1 = {1, "Laptop", 1200.50f};
    printf("Item Details: ID: %d, Name: %s, Price: %.2f\n", item1.id, item1.name, item1.price);

    // Создаем экземпляр InventoryItem
    InventoryItem inv_item;
    inv_item.details.id = 101;
    strcpy(inv_item.details.name, "Novel 'C Master'");
    inv_item.details.price = 25.99f;
    inv_item.category = BOOKS; // Используем enum константу
    inv_item.quantity = 50;

    printf("\nInventory Item Details:\n");
    printf("  ID: %d\n", inv_item.details.id);
    printf("  Name: %s\n", inv_item.details.name);
    printf("  Price: %.2f\n", inv_item.details.price);
    printf("  Category (enum value): %d\n", inv_item.category);
    printf("  Quantity in Stock: %d\n", inv_item.quantity);

    // Пример использования typedef для базового типа
    typedef int counter_t;
    counter_t total_count = 1000;
    printf("\nTotal Count: %d\n", total_count);

    return 0;
}