#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.

/**
 * @brief Callback-функция для пункта меню "Открыть".
 *
 * @param widget Указатель на GtkMenuItem "Открыть".
 * @param data Дополнительные данные (NULL).
 */
static void on_open(GtkWidget *widget, gpointer data) {
    g_print("Открытие файла...\n"); // Просто выводим сообщение в консоль.
}

/**
 * @brief Callback-функция для пункта меню "Сохранить".
 *
 * @param widget Указатель на GtkMenuItem "Сохранить".
 * @param data Дополнительные данные (NULL).
 */
static void on_save(GtkWidget *widget, gpointer data) {
    g_print("Сохранение файла...\n"); // Просто выводим сообщение в консоль.
}

/**
 * @brief Callback-функция для пункта меню "Выход".
 * Завершает работу приложения.
 *
 * @param widget Указатель на GtkMenuItem "Выход".
 * @param data Дополнительные данные (NULL).
 */
static void on_quit(GtkWidget *widget, gpointer data) {
    g_print("Выход из приложения\n"); // Сообщение перед выходом.
    gtk_main_quit();                   // Завершаем главный цикл GTK.
}

/**
 * @brief Главная функция программы.
 *
 * Создает окно с более сложным меню, содержащим несколько пунктов
 * и разделитель.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    GtkWidget *window;       // Основное окно приложения.
    GtkWidget *vbox;         // Вертикальный контейнер для размещения элементов окна.
    GtkWidget *menubar;      // Горизонтальная панель меню.
    GtkWidget *file_menu;    // Подменю, которое будет содержать "Открыть", "Сохранить", "Выход".
    GtkWidget *file_item;    // Пункт "Файл" на GtkMenuBar, который открывает file_menu.
    GtkWidget *open_item;    // Пункт меню "Открыть".
    GtkWidget *save_item;    // Пункт меню "Сохранить".
    GtkWidget *separator;    // Разделитель между пунктами меню.
    GtkWidget *exit_item;    // Пункт меню "Выход".

    gtk_init(&argc, &argv); // **Инициализация GTK**.

    // 1. **Создание и настройка главного окна.**
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Меню с Несколькими Пунктами"); // Устанавливаем заголовок.
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200); // Устанавливаем размер.
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Центрируем.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Сигнал закрытия окна.

    // 2. **Создание и добавление основного контейнера в окно.**
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Вертикальный GtkBox.
    gtk_container_add(GTK_CONTAINER(window), vbox);  // Добавляем vbox в окно.

    // 3. **Создание панели меню и основного подменю.**
    menubar = gtk_menu_bar_new(); // Создаем панель меню.
    file_menu = gtk_menu_new();   // Создаем подменю "Файл".

    // 4. **Создание отдельных пунктов меню.**
    file_item = gtk_menu_item_new_with_label("Файл");    // Пункт для панели меню.
    open_item = gtk_menu_item_new_with_label("Открыть"); // Пункт для подменю.
    save_item = gtk_menu_item_new_with_label("Сохранить"); // Пункт для подменю.
    separator = gtk_separator_menu_item_new(); // **Создаем новый разделитель меню.**
                                               // Это специальный вид GtkMenuItem,
                                               // который отображается как горизонтальная линия.
    exit_item = gtk_menu_item_new_with_label("Выход");   // Пункт для подменю.

    // 5. **Добавление пунктов в подменю "Файл".**
    // Порядок вызовов `gtk_menu_shell_append` определяет порядок отображения пунктов.
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), separator); // **Добавляем разделитель.**
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_item);

    // 6. **Привязка подменю к пункту меню и добавление его в панель меню.**
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu); // Делаем 'file_item' раскрывающимся.
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_item);      // Добавляем 'file_item' в основную панель.

    // 7. **Размещение панели меню в окне.**
    // Панель меню всегда должна быть вверху.
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    // 8. **Подключение callback-функций к каждому пункту меню.**
    g_signal_connect(open_item, "activate", G_CALLBACK(on_open), NULL);
    g_signal_connect(save_item, "activate", G_CALLBACK(on_save), NULL);
    g_signal_connect(exit_item, "activate", G_CALLBACK(on_quit), NULL);

    // 9. **Отображение всех виджетов и запуск главного цикла GTK.**
    gtk_widget_show_all(window);
    gtk_main();

    return 0; // Успешное завершение.
}