#include <gtk/gtk.h>

/**
 * @brief Главная функция программы.
 * Демонстрирует настройку размеров и свойств расширения виджетов.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *button1, *button2, *button3;

    gtk_init(&argc, &argv);

    // 1. Создание главного окна
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Настройка Размеров и Расширения");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); // Начальный размер окна
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 2. Создание GtkBox для размещения кнопок по вертикали
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); // Отступ между элементами 10px
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10); // Внешний отступ 10px
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // 3. Кнопка 1: Фиксированный размер
    button1 = gtk_button_new_with_label("Фиксированный размер (150x50)");
    // Устанавливаем минимальный требуемый размер виджета.
    // Виджет никогда не будет меньше этих размеров, но может быть больше.
    gtk_widget_set_size_request(button1, 150, 50);
    // Не позволяем кнопке расширяться, она будет занимать только свой минимальный размер.
    gtk_widget_set_hexpand(button1, FALSE);
    gtk_widget_set_vexpand(button1, FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 0); // FALSE, FALSE - не расширять, не заполнять

    // 4. Кнопка 2: Расширение по горизонтали
    button2 = gtk_button_new_with_label("Расширение по горизонтали");
    gtk_widget_set_size_request(button2, 100, 40); // Минимальный размер
    gtk_widget_set_hexpand(button2, TRUE);       // Позволяем кнопке расширяться по горизонтали
    gtk_widget_set_vexpand(button2, FALSE);      // Не позволяем расширяться по вертикали
    gtk_box_pack_start(GTK_BOX(vbox), button2, TRUE, TRUE, 0); // TRUE, TRUE - расширять, заполнять

    // 5. Кнопка 3: Расширение по вертикали
    button3 = gtk_button_new_with_label("Расширение по вертикали");
    gtk_widget_set_size_request(button3, 80, 60); // Минимальный размер
    gtk_widget_set_hexpand(button3, FALSE);      // Не позволяем расширяться по горизонтали
    gtk_widget_set_vexpand(button3, TRUE);       // Позволяем кнопке расширяться по вертикали
    gtk_box_pack_start(GTK_BOX(vbox), button3, TRUE, TRUE, 0); // TRUE, TRUE - расширять, заполнять

    // 6. Отображение всех виджетов и запуск главного цикла GTK
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}