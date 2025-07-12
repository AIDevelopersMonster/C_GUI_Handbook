#include <gtk/gtk.h>

/**
 * @brief Загружает и применяет CSS-стили из файла.
 *
 * @param css_file_path Путь к CSS-файлу.
 */
static void load_css(const char *css_file_path) {
    GtkCssProvider *provider = gtk_css_provider_new(); // Создаем новый провайдер CSS.
    GdkDisplay *display = gdk_display_get_default();   // Получаем дисплей по умолчанию.
    GdkScreen *screen = gdk_display_get_default_screen(display); // Получаем экран по умолчанию.

    GError *error = NULL;

    // Загружаем CSS-файл. Если возникает ошибка, она будет записана в 'error'.
    if (!gtk_css_provider_load_from_path(provider, css_file_path, &error)) {
        g_printerr("Ошибка загрузки CSS-файла: %s\n", error->message);
        g_clear_error(&error); // Освобождаем объект ошибки.
        g_object_unref(provider); // Освобождаем провайдер, если он не был добавлен.
        return;
    }

    // Добавляем провайдер CSS-стилей для всего экрана.
    // GTK_STYLE_PROVIDER_PRIORITY_APPLICATION: Высокий приоритет, переопределяет тему.
    // GTK_STYLE_PROVIDER_PRIORITY_USER: Приоритет стилей пользователя, обычно выше темы.
    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Уменьшаем счетчик ссылок на провайдер.
    // Поскольку провайдер уже добавлен к экрану, GTK будет держать на него ссылку.
    // Уменьшение счетчика здесь предотвратит утечку памяти, но объект останется живым.
    g_object_unref(provider);
}

/**
 * @brief Главная функция программы.
 * Создает окно с меткой и кнопкой, применяет к ним стили через CSS.
 *
 * @param argc Аргументы командной строки.
 * @param argv Аргументы командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    // Загружаем CSS-стили перед созданием виджетов, чтобы они сразу применились.
    load_css("style.css");

    // 1. Создание главного окна
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Стилизация через CSS");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 250);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20); // Отступ 20px
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // 2. Создание метки (GtkLabel)
    label = gtk_label_new("Пример стилизованного текста");
    // Метки автоматически применяют стиль 'label' из CSS
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // 3. Создание кнопки (GtkButton)
    button = gtk_button_new_with_label("Нажми меня!");
    // Кнопки автоматически применяют стиль 'button' из CSS
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // 4. Отображение всех виджетов и запуск главного цикла GTK
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}