#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.

/**
 * @brief Callback-функция, вызываемая при нажатии кнопки "Открыть файл".
 * Открывает GtkFileChooserDialog для выбора файла.
 *
 * @param widget Указатель на кнопку.
 * @param window Указатель на родительское окно.
 */
static void on_open_button_clicked(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog; // Указатель на файловый диалог.
    gint res;          // Результат закрытия диалога.

    // Создаем новый GtkFileChooserDialog для открытия файла.
    // Параметры:
    // 1. "Открыть файл": Заголовок диалогового окна.
    // 2. GTK_WINDOW(window): Родительское окно для диалога.
    // 3. GTK_FILE_CHOOSER_ACTION_OPEN: Режим работы диалога - открытие существующего файла.
    // 4. "_Отмена": Текст кнопки отмены и ее GTK_RESPONSE_CANCEL.
    // 5. "_Открыть": Текст кнопки подтверждения и ее GTK_RESPONSE_ACCEPT.
    // 6. NULL: Завершает список кнопок.
    dialog = gtk_file_chooser_dialog_new("Открыть файл",
                                         GTK_WINDOW(window),
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Отмена", GTK_RESPONSE_CANCEL,
                                         "_Открыть", GTK_RESPONSE_ACCEPT,
                                         NULL);

    // Запускаем диалог и получаем его результат.
    // gtk_dialog_run() блокирует выполнение до выбора пользователя.
    res = gtk_dialog_run(GTK_DIALOG(dialog));

    // Проверяем, нажал ли пользователь "Открыть".
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename; // Переменная для хранения пути к файлу.
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog); // Приводим к типу GtkFileChooser.

        // Получаем выбранный путь к файлу.
        filename = gtk_file_chooser_get_filename(chooser);
        g_print("Выбран файл: %s\n", filename); // Выводим путь в консоль.
        g_free(filename); // Освобождаем память, выделенную для строки filename.
    }

    // Уничтожаем диалог после его использования, независимо от результата.
    gtk_widget_destroy(dialog);
}

/**
 * @brief Главная функция программы.
 * Создает основное окно с кнопкой для вызова диалога открытия файла.
 *
 * @param argc Аргументы командной строки.
 * @param argv Аргументы командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *vbox; // Добавим vbox для лучшего расположения

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Выбор файла");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); // Отступ 10 пикселей
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10); // Отступ от краев
    gtk_container_add(GTK_CONTAINER(window), vbox);

    button = gtk_button_new_with_label("Открыть файл...");
    // Передаем window как пользовательские данные, чтобы использовать его как родителя.
    g_signal_connect(button, "clicked", G_CALLBACK(on_open_button_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}