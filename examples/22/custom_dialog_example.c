#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.

/**
 * @brief Callback-функция, вызываемая при нажатии кнопки в главном окне.
 * Отвечает за создание, настройку и отображение кастомного GtkDialog.
 *
 * @param widget Указатель на кнопку, которая была нажата.
 * @param window Указатель на главное окно (родительское окно для диалога).
 */
static void on_button_clicked(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog;       // Указатель на диалоговое окно.
    gint result;             // Переменная для хранения результата (какая кнопка была нажата).
    GtkWidget *content_area; // Область содержимого диалога, куда мы добавим нашу метку.
    GtkWidget *label;        // Метка для отображения текста в диалоге.

    // Создаем новый GtkDialog с предопределенными кнопками.
    // Параметры:
    // 1. "Кастомный диалог": Заголовок диалогового окна.
    // 2. GTK_WINDOW(window): Родительское окно.
    // 3. GTK_DIALOG_MODAL: Флаг, делающий диалог модальным. Это означает, что
    //    пользователь не сможет взаимодействовать с родительским окном,
    //    пока этот диалог открыт.
    // 4. "_OK": Текст первой кнопки. Подчеркивание `_` используется для создания мнемонического доступа
    //    (например, Alt+O, если это поддерживается системой).
    // 5. GTK_RESPONSE_OK: Значение, которое `gtk_dialog_run()` вернет, если будет нажата эта кнопка.
    // 6. "_Отмена": Текст второй кнопки.
    // 7. GTK_RESPONSE_CANCEL: Значение, возвращаемое при нажатии этой кнопки.
    // 8. NULL: Обозначает конец списка кнопок.
    dialog = gtk_dialog_new_with_buttons("Кастомный диалог",
                                         GTK_WINDOW(window),
                                         GTK_DIALOG_MODAL,
                                         "_OK",
                                         GTK_RESPONSE_OK,
                                         "_Отмена",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);

    // Получаем область содержимого диалога.
    // Это GtkBox, куда можно добавлять любые виджеты, формируя пользовательский интерфейс диалога.
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Создаем метку с вопросом.
    label = gtk_label_new("Вы хотите продолжить?");
    // Добавляем метку в область содержимого диалога.
    gtk_container_add(GTK_CONTAINER(content_area), label);

    // Отображаем все виджеты в диалоге (метку и кнопки).
    gtk_widget_show_all(dialog);

    // Запускаем диалог и получаем ответ пользователя.
    // Эта функция блокирует выполнение программы до закрытия диалога.
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    // Анализируем результат, чтобы определить, какая кнопка была нажата.
    if (result == GTK_RESPONSE_OK) {
        g_print("Пользователь нажал OK\n");
    } else if (result == GTK_RESPONSE_CANCEL) {
        g_print("Пользователь нажал Отмена\n");
    } else {
        // Может быть GTK_RESPONSE_NONE, если диалог был закрыт другим способом (например, кнопкой закрытия окна).
        g_print("Диалог был закрыт без явного выбора OK/Отмена\n");
    }

    // Уничтожаем диалог после его использования.
    // Это освобождает ресурсы, которые он занимал.
    gtk_widget_destroy(dialog);
}

/**
 * @brief Главная функция программы.
 *
 * Инициализирует GTK, создает основное окно с кнопкой,
 * которая при нажатии отображает кастомный GtkDialog.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    GtkWidget *window; // Указатель на главное окно.
    GtkWidget *button; // Указатель на кнопку.

    gtk_init(&argc, &argv); // Инициализация библиотеки GTK.

    // 1. Создание главного окна.
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Пример Кастомного Диалога");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Подключаем сигнал "destroy" окна.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 2. Создание кнопки.
    button = gtk_button_new_with_label("Открыть диалог");
    // Подключаем сигнал "clicked" кнопки к нашей функции on_button_clicked,
    // передавая главное окно в качестве пользовательских данных.
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), window);

    // 3. Добавление кнопки в окно.
    gtk_container_add(GTK_CONTAINER(window), button);

    // 4. Отображение всех виджетов и запуск главного цикла GTK.
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}