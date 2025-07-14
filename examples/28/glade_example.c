#include <gtk/gtk.h>
#include <libgen.h>
#include <unistd.h>
#include <limits.h>

// Структура для хранения виджетов
typedef struct {
    GtkWidget *entry_input;
    GtkWidget *label_output;
    GtkWidget *button;
} AppData;

// Загрузка CSS из файла style.css
static void load_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    char exe_path[PATH_MAX], css_path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len != -1) {
        exe_path[len] = '\0';
        char *dir = dirname(exe_path);
        snprintf(css_path, sizeof(css_path), "%s/style.css", dir);
        if (gtk_css_provider_load_from_path(provider, css_path, NULL))
            g_print("CSS успешно загружен: %s\\n", css_path);
        else
            g_warning("Ошибка загрузки CSS: %s", css_path);
        gtk_style_context_add_provider_for_screen(
            screen,
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );
    } else {
        g_warning("Не удалось определить путь к исполняемому файлу.");
    }
    g_object_unref(provider);
}

// Обработчик нажатия кнопки
void on_btn_copy_clicked(GtkButton *button, gpointer user_data) {
    AppData *app = (AppData *)user_data;
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(app->entry_input));
    gtk_label_set_text(GTK_LABEL(app->label_output), text);
}

// Главная функция
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    load_css();

    GtkBuilder *builder = gtk_builder_new_from_file("interface.glade");
    if (!builder) {
        g_critical("Не удалось загрузить Glade-файл.");
        return 1;
    }

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry_input"));
    GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(builder, "label_output"));
    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "my_button"));

    if (!window || !entry || !label || !button) {
        g_critical("Не удалось получить виджеты.");
        g_object_unref(builder);
        return 1;
    }

    // Назначаем CSS-имена
    gtk_widget_set_name(window, "main_window");
    gtk_widget_set_name(entry, "entry_input");
    gtk_widget_set_name(label, "label_output");
    gtk_widget_set_name(button, "my_button");

    AppData app = { entry, label, button };

    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_copy_clicked), &app);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    g_object_unref(builder);
    return 0;
}
