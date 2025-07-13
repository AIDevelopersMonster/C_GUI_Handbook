#include <gtk/gtk.h> // Подключаем библиотеку GTK.

/**
 * @brief Обработчик сигнала 'clicked' для кнопки 'btn_click_me'.
 * Эта функция будет автоматически вызвана, когда пользователь нажмет на кнопку.
 * Имя функции должно совпадать с тем, что указано в Glade для обработчика сигнала.
 *
 * @param button Указатель на объект GtkButton, который сгенерировал сигнал.
 * @param user_data Пользовательские данные (в данном случае NULL).
 */
void on_btn_click_me_clicked(GtkButton *button, gpointer user_data) {
    g_print("Кнопка 'Нажми меня!' была нажата!\n"); // Выводим сообщение в консоль.
}

/**
 * @brief Главная функция программы.
 * Инициализирует GTK, загружает интерфейс из Glade-файла,
 * подключает сигналы и запускает главный цикл GTK.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    GtkBuilder *builder; // Объявляем указатель на GtkBuilder.
    GtkWidget *window;   // Объявляем указатель на главное окно.

    gtk_init(&argc, &argv); // Инициализируем библиотеку GTK.

    // Создаем новый объект GtkBuilder и загружаем в него интерфейс из файла "interface.glade".
    // Если файл не найден или содержит ошибки, builder будет NULL, и GtkBuilder выведет ошибки.
    builder = gtk_builder_new_from_file("interface.glade");

    // Если builder не смог загрузить файл, выходим.
    if (!builder) {
        g_critical("Не удалось загрузить Glade-файл: interface.glade");
        return 1;
    }

    // Получаем указатель на главное окно по его ID, который мы задали в Glade ("main_window").
    // Важно привести тип к GTK_WIDGET(), так как gtk_builder_get_object возвращает GObject*.
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    // Подключаем все сигналы, определенные в Glade-файле, к соответствующим функциям в коде.
    // GtkBuilder сам ищет функции с именами, указанными в Glade.
    gtk_builder_connect_signals(builder, NULL); // NULL означает, что пользовательские данные не передаются.

    // Соединяем сигнал "destroy" главного окна с функцией завершения GTK.
    // Это гарантирует, что приложение закроется при закрытии окна.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Отображаем все виджеты в окне.
    gtk_widget_show_all(window);

    // Запускаем главный цикл GTK. Программа будет ожидать событий (нажатий кнопок и т.д.).
    gtk_main();

    // Освобождаем ресурсы GtkBuilder.
    // Важно освободить builder после того, как все виджеты и сигналы подключены,
    // так как builder больше не нужен, но виджеты остаются в памяти.
    g_object_unref(builder);

    return 0; // Возвращаем 0, показывая успешное завершение.
}