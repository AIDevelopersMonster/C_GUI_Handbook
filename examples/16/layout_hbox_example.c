#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.

/**
 * @brief Единая callback-функция для обработки нажатий на несколько кнопок.
 *
 * Эта функция демонстрирует, как получить текст нажатой кнопки и вывести его
 * в консоль, что полезно для отладки или для выполнения разных действий
 * в зависимости от того, какая кнопка была нажата.
 *
 * @param widget Указатель на GtkWidget, который испустил сигнал (GtkButton).
 * @param data   Универсальный указатель на пользовательские данные (в данном случае NULL).
 */
static void on_generic_button_clicked(GtkWidget *widget, gpointer data) {
    // gtk_button_get_label() - функция для получения текста (метки) с кнопки.
    // GTK_BUTTON(widget) - приведение типа GtkWidget* к GtkButton*.
    const char *button_label = gtk_button_get_label(GTK_BUTTON(widget));
    g_print("Нажата кнопка: %s\n", button_label);
}

/**
 * @brief Главная функция программы.
 *
 * Инициализирует GTK, создает окно, горизонтальный контейнер GtkBox,
 * добавляет в него несколько кнопок с различными параметрами компоновки,
 * подключает обработчики событий и запускает главный цикл GTK.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    // 1. Инициализация GTK.
    gtk_init(&argc, &argv);

    // 2. Создание главного окна.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkBox Горизонтальный Пример");
    gtk_window_set_default_size(GTK_WINDOW(window), 450, 100); // Окно пошире для горизонтального расположения
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Подключение сигнала "destroy" окна для его закрытия.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 3. Создание горизонтального контейнера GtkBox.
    // GTK_ORIENTATION_HORIZONTAL - виджеты будут располагаться слева направо.
    // 5 - отступ в 5 пикселей между каждым дочерним виджетом.
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    // 4. Создание трёх кнопок.
    GtkWidget *button1 = gtk_button_new_with_label("Кнопка 1");
    GtkWidget *button2 = gtk_button_new_with_label("Кнопка 2");
    GtkWidget *button3 = gtk_button_new_with_label("Кнопка 3");

    // 5. Подключение одной и той же функции обработчика к каждой кнопке.
    g_signal_connect(button1, "clicked", G_CALLBACK(on_generic_button_clicked), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_generic_button_clicked), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_generic_button_clicked), NULL);

    // 6. Добавление кнопок в GtkBox с разными параметрами pack_start/pack_end.
    // Эти параметры контролируют, как виджеты будут распределять доступное пространство.

    // Кнопка 1: pack_start, не расширяется (FALSE), не заполняет (FALSE), без доп. отступа (0).
    // Она займет только свой минимальный размер и будет прижата к левому краю.
    gtk_box_pack_start(GTK_BOX(hbox), button1, FALSE, FALSE, 0);

    // Кнопка 2: pack_start, расширяется (TRUE), заполняет (TRUE), без доп. отступа (0).
    // Она будет пытаться занять максимально доступное пространство между кнопкой 1 и 3.
    gtk_box_pack_start(GTK_BOX(hbox), button2, TRUE, TRUE, 0);

    // Кнопка 3: pack_end, не расширяется (FALSE), но заполняет (TRUE), без доп. отступа (0).
    // Она будет прижата к правому краю. Параметр 'fill' здесь означает, что если ей выделено
    // немного больше места (из-за общего отступа бокса), она заполнит это место.
    gtk_box_pack_end(GTK_BOX(hbox), button3, FALSE, TRUE, 0);

    // 7. Добавление GtkBox в окно.
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // 8. Отображение всех виджетов.
    gtk_widget_show_all(window);

    // 9. Запуск главного цикла событий GTK.
    gtk_main();

    return 0; // Успешное завершение программы.
}