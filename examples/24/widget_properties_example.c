#include <gtk/gtk.h>

// Глобальные указатели для доступа к виджетам из callback-функций
GtkWidget *entry_widget;
GtkWidget *toggle_button;
GtkWidget *label_status;

/**
 * @brief Callback-функция, вызываемая при изменении текста в GtkEntry.
 * Обновляет текст метки статуса.
 *
 * @param entry Указатель на GtkEntry.
 * @param user_data Не используется.
 */
static void on_entry_changed(GtkEditable *entry, gpointer user_data) {
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry_widget));
    char status_text[100];
    g_snprintf(status_text, sizeof(status_text), "Введено символов: %zu", strlen(text));
    gtk_label_set_text(GTK_LABEL(label_status), status_text);
}

/**
 * @brief Callback-функция, вызываемая при нажатии кнопки-переключателя.
 * Динамически меняет чувствительность (доступность) и видимость GtkEntry.
 *
 * @param widget Указатель на кнопку.
 * @param user_data Не используется.
 */
static void on_toggle_button_clicked(GtkWidget *widget, gpointer user_data) {
    gboolean is_sensitive = gtk_widget_get_sensitive(entry_widget);
    gboolean is_visible = gtk_widget_get_visible(entry_widget);

    // Переключаем чувствительность
    gtk_widget_set_sensitive(entry_widget, !is_sensitive);

    // Переключаем видимость (например, скрываем/показываем при каждом втором нажатии)
    // Для демонстрации, сделаем видимость зависимой от чувствительности
    gtk_widget_set_visible(entry_widget, !is_visible);

    // Обновляем текст кнопки-переключателя
    if (gtk_widget_get_sensitive(entry_widget)) {
        gtk_button_set_label(GTK_BUTTON(toggle_button), "Сделать неактивным и скрыть");
    } else {
        gtk_button_set_label(GTK_BUTTON(toggle_button), "Сделать активным и показать");
    }

    // Обновляем текст метки статуса
    gtk_label_set_text(GTK_LABEL(label_status), "Поле ввода изменено!");
}

/**
 * @brief Главная функция программы.
 * Создает окно с GtkEntry, кнопкой и меткой для демонстрации свойств.
 *
 * @param argc Аргументы командной строки.
 * @param argv Аргументы командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *vbox;

    gtk_init(&argc, &argv);

    // 1. Создание главного окна
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Настройка Свойств Виджетов");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 250);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15); // Отступ 15px
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 15);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // 2. Создание GtkEntry (поле ввода)
    entry_widget = gtk_entry_new();
    // Устанавливаем текст-заполнитель
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_widget), "Введите текст здесь...");
    // Устанавливаем максимальную длину текста
    gtk_entry_set_max_length(GTK_ENTRY(entry_widget), 20); // Ограничение на 20 символов
    // Подключаем сигнал изменения текста для обновления статуса
    g_signal_connect(entry_widget, "changed", G_CALLBACK(on_entry_changed), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), entry_widget, FALSE, FALSE, 0);

    // 3. Создание кнопки-переключателя
    toggle_button = gtk_button_new_with_label("Сделать неактивным и скрыть");
    g_signal_connect(toggle_button, "clicked", G_CALLBACK(on_toggle_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), toggle_button, FALSE, FALSE, 0);

    // 4. Создание метки для отображения статуса
    label_status = gtk_label_new("Начните вводить или нажмите кнопку");
    gtk_label_set_justify(GTK_LABEL(label_status), GTK_JUSTIFY_CENTER); // Выравнивание текста
    gtk_box_pack_start(GTK_BOX(vbox), label_status, FALSE, FALSE, 0);

    // 5. Отображение всех виджетов и запуск главного цикла GTK
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}