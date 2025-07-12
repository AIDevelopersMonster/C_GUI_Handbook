#include <gtk/gtk.h>

/**
 * @brief Callback-функция, вызываемая при нажатии кнопки "Сохранить файл".
 * Открывает GtkFileChooserDialog для сохранения файла.
 *
 * @param widget Указатель на кнопку.
 * @param window Указатель на родительское окно.
 */
static void on_save_button_clicked(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog;
    gint res;
    char *filename;

    // Создаем GtkFileChooserDialog в режиме сохранения файла.
    // GTK_FILE_CHOOSER_ACTION_SAVE указывает на режим сохранения.
    dialog = gtk_file_chooser_dialog_new("Сохранить файл",
                                         GTK_WINDOW(window),
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "_Отмена", GTK_RESPONSE_CANCEL,
                                         "_Сохранить", GTK_RESPONSE_ACCEPT,
                                         NULL);

    // Устанавливаем рекомендованное имя файла по умолчанию.
    // Пользователь может изменить его.
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "НовыйДокумент.txt");

    // Устанавливаем режим подтверждения перезаписи.
    // GTK_FILE_CHOOSER_CONFIRMATION_CONFIRM: если файл существует, спросить пользователя.
    // GTK_FILE_CHOOSER_CONFIRMATION_ACCEPT: всегда принимать.
    // GTK_FILE_CHOOSER_CONFIRMATION_SELECT_IF_EXISTS: выбрать, если существует.
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);

    res = gtk_dialog_run(GTK_DIALOG(dialog));

    if (res == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        g_print("Файл будет сохранен как: %s\n", filename);
        // Здесь должна быть логика сохранения файла по полученному пути
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

/**
 * @brief Главная функция программы.
 * Создает основное окно с кнопкой для вызова диалога сохранения файла.
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
    gtk_window_set_title(GTK_WINDOW(window), "Сохранение файла");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    button = gtk_button_new_with_label("Сохранить файл...");
    g_signal_connect(button, "clicked", G_CALLBACK(on_save_button_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}