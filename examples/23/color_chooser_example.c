#include <gtk/gtk.h>

/**
 * @brief Callback-функция, вызываемая при нажатии кнопки "Выбрать цвет".
 * Открывает GtkColorChooserDialog для выбора цвета.
 *
 * @param widget Указатель на кнопку.
 * @param window Указатель на родительское окно.
 */
static void on_color_button_clicked(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog;
    gint res;
    GdkRGBA color; // Структура для хранения цвета (Red, Green, Blue, Alpha).

    // Создаем новый GtkColorChooserDialog.
    // Параметры:
    // 1. "Выбор цвета": Заголовок диалога.
    // 2. GTK_WINDOW(window): Родительское окно.
    // 3. GTK_DIALOG_MODAL: Делает диалог модальным.
    // 4. "_Отмена": Кнопка отмены.
    // 5. GTK_RESPONSE_CANCEL: Ответ при нажатии кнопки отмены.
    // 6. "_OK": Кнопка подтверждения.
    // 7. GTK_RESPONSE_OK: Ответ при нажатии кнопки OK.
    // 8. NULL: Конец списка кнопок.
    dialog = gtk_color_chooser_dialog_new("Выбор цвета",
                                          GTK_WINDOW(window));

    // Можно установить начальный цвет диалога.
    // gdk_rgba_parse(&color, "rgb(100, 150, 200)"); // Пример: парсим строку
    // gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(dialog), &color);

    // Запускаем диалог и получаем его результат.
    res = gtk_dialog_run(GTK_DIALOG(dialog));

    // Проверяем, нажал ли пользователь "OK".
    if (res == GTK_RESPONSE_OK) {
        // Получаем выбранный цвет.
        gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(dialog), &color);

        // Выводим компоненты цвета в консоль.
        // Значения GdkRGBA находятся в диапазоне от 0.0 до 1.0.
        g_print("Выбран цвет: R=%.2f, G=%.2f, B=%.2f, A=%.2f\n",
                color.red, color.green, color.blue, color.alpha);
        // Если нужно в 0-255: (guint8)(color.red * 255), (guint8)(color.green * 255), etc.
        g_print("В формате 0-255: R=%d, G=%d, B=%d\n",
                (guint8)(color.red * 255), (guint8)(color.green * 255), (guint8)(color.blue * 255));
    }

    // Уничтожаем диалог.
    gtk_widget_destroy(dialog);
}

/**
 * @brief Главная функция программы.
 * Создает основное окно с кнопкой для вызова диалога выбора цвета.
 *
 * @param argc Аргументы командной строки.
 * @param argv Аргументы командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *vbox;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Выбор цвета");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    button = gtk_button_new_with_label("Выбрать цвет...");
    g_signal_connect(button, "clicked", G_CALLBACK(on_color_button_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}