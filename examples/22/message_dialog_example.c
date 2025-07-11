#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.

/**
 * @brief Callback-функция, вызываемая при нажатии кнопки в главном окне.
 * Отвечает за создание и отображение GtkMessageDialog.
 *
 * @param widget Указатель на кнопку, которая была нажата.
 * @param window Указатель на главное окно (родительское окно для диалога),
 * переданный через параметр `data` при подключении сигнала.
 */
static void on_button_clicked(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog; // Декларация указателя на диалоговое окно.

    // Создаем новый GtkMessageDialog.
    // Параметры:
    // 1. GTK_WINDOW(window): Родительское окно для диалога.
    //    Это обеспечивает правильное позиционирование диалога и его уничтожение при закрытии родителя.
    // 2. GTK_DIALOG_DESTROY_WITH_PARENT: Флаг поведения диалога.
    //    Означает, что диалог будет автоматически уничтожен, если его родительское окно будет закрыто.
    // 3. GTK_MESSAGE_INFO: Тип сообщения. Определяет иконку, которая будет отображаться в диалоге (информационная).
    //    Другие варианты: GTK_MESSAGE_WARNING, GTK_MESSAGE_ERROR, GTK_MESSAGE_QUESTION.
    // 4. GTK_BUTTONS_OK: Набор кнопок, которые будут присутствовать в диалоге.
    //    Здесь будет только кнопка "OK". Другие: GTK_BUTTONS_OK_CANCEL, GTK_BUTTONS_YES_NO.
    // 5. "Это информационное сообщение.": Формат строки сообщения. Работает как printf.
    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "Это информационное сообщение.");

    // Запускаем диалог. Эта функция отображает диалог и блокирует
    // основное окно до тех пор, пока пользователь не закроет диалог (нажав кнопку).
    // Она возвращает значение GTK_RESPONSE_..., соответствующее нажатой кнопке.
    // В данном случае, поскольку есть только кнопка "OK", она вернет GTK_RESPONSE_OK.
    gtk_dialog_run(GTK_DIALOG(dialog));

    // Уничтожаем диалог после того, как он был закрыт.
    // Это освобождает выделенные для него ресурсы.
    gtk_widget_destroy(dialog);
}

/**
 * @brief Главная функция программы.
 *
 * Инициализирует GTK, создает основное окно с кнопкой,
 * которая при нажатии отображает GtkMessageDialog.
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
    gtk_window_set_title(GTK_WINDOW(window), "Пример MessageDialog");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Подключаем сигнал "destroy" окна к функции gtk_main_quit.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 2. Создание кнопки.
    button = gtk_button_new_with_label("Показать сообщение");
    // Подключаем сигнал "clicked" кнопки к нашей функции on_button_clicked.
    // В качестве пользовательских данных (data) передаем указатель на главное окно,
    // чтобы функция on_button_clicked могла использовать его как родителя для диалога.
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), window);

    // 3. Добавление кнопки в окно.
    gtk_container_add(GTK_CONTAINER(window), button);

    // 4. Отображение всех виджетов и запуск главного цикла GTK.
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}