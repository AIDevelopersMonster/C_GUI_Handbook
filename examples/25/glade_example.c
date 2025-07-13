#include <gtk/gtk.h> // Подключаем библиотеку GTK.

/**
 * @brief Структура для хранения указателей на виджеты и других данных,
 * которые должны быть доступны в функциях обратного вызова.
 */
typedef struct {
    GtkWidget *entry_input;  // Указатель на поле ввода GtkEntry.
    GtkWidget *label_output; // Указатель на метку GtkLabel для вывода.
} AppData;

/**
 * @brief Обработчик сигнала 'clicked' для кнопки 'btn_copy'.
 * Копирует текст из поля ввода в метку.
 *
 * @param button Указатель на объект GtkButton, который сгенерировал сигнал.
 * @param user_data Пользовательские данные, приведенные к типу AppData*.
 */
void on_btn_copy_clicked(GtkButton *button, gpointer user_data) {
    // Приводим gpointer к нашему типу AppData*.
    AppData *app = (AppData *)user_data;

    // Получаем текст из поля ввода.
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(app->entry_input));

    // Устанавливаем полученный текст в метку.
    gtk_label_set_text(GTK_LABEL(app->label_output), text);

    g_print("Текст скопирован: %s\n", text); // Выводим в консоль для отладки.
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
    AppData app;         // Объявляем структуру для хранения данных приложения.

    gtk_init(&argc, &argv); // Инициализируем библиотеку GTK.

    // Проверяем, существует ли файл interface.glade.
    if (!g_file_test("interface.glade", G_FILE_TEST_EXISTS)) {
        g_critical("Ошибка: файл interface.glade не найден в текущей директории.");
        g_critical("Убедитесь, что вы создали его с помощью Glade и сохранили.");
        return 1;
    }
    
    // Создаем новый объект GtkBuilder и загружаем в него интерфейс из файла "interface.glade".
    // Если файл не найден или содержит ошибки, builder будет NULL, и GtkBuilder выведет ошибки.
    builder = gtk_builder_new_from_file("interface.glade");

    // Если builder не смог загрузить файл, выходим.
    if (!builder) {
        g_critical("Не удалось загрузить Glade-файл: interface.glade. Проверьте его синтаксис.");
        return 1;
    }

    // Получаем указатель на главное окно по его ID "main_window".
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    if (!window) {
        g_critical("Ошибка: не удалось получить виджет 'main_window' из Glade-файла.");
        return 1;
    }

    // Получаем указатели на поле ввода и метку по их ID.
    app.entry_input = GTK_WIDGET(gtk_builder_get_object(builder, "entry_input"));
    app.label_output = GTK_WIDGET(gtk_builder_get_object(builder, "label_output"));

    // Проверяем, что все нужные виджеты были найдены.
    if (!app.entry_input || !app.label_output) {
        g_critical("Ошибка: не удалось получить один или несколько виджетов (entry_input, label_output).");
        g_critical("Убедитесь, что их ID правильно заданы в Glade-файле.");
        return 1;
    }

    // Подключаем все сигналы, определенные в Glade-файле, к соответствующим функциям в коде.
    // Передаем адрес нашей структуры 'app' в качестве пользовательских данных.
    gtk_builder_connect_signals(builder, &app);

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