#include <gtk/gtk.h> // Подключаем основную библиотеку GTK. Этого заголовочного файла достаточно для большинства базовых функций.

// Callback-функция, которая будет вызвана при "активации" приложения.
// 'app' - указатель на объект GtkApplication, представляющий наше приложение.
// 'user_data' - пользовательские данные, которые мы можем передать (в данном случае NULL).
static void on_activate(GtkApplication *app, gpointer user_data) {
    // Создаём новое окно приложения. GtkApplicationWindow является основным окном для приложения.
    // Оно автоматически связывается с GtkApplication, что обеспечивает правильное управление жизненным циклом.
    GtkWidget *window = gtk_application_window_new(app);

    // Устанавливаем заголовок окна.
    // GTK_WINDOW(window) - это макрос приведения типа, который "приводит"
    // общий GtkWidget* к более специфичному GtkWindow*, позволяя использовать функции GtkWindow.
    gtk_window_set_title(GTK_WINDOW(window), "Пример GTK");

    // Устанавливаем размер окна по умолчанию (ширина, высота).
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);

    // Показываем все виджеты в окне (само окно и все его дочерние элементы, если они есть).
    // GTK-виджеты не видны по умолчанию; их нужно явно показать.
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    // Создаём новый объект GtkApplication.
    // "com.example.GTKApp" - уникальный ID приложения (рекомендуется использовать обратный домен).
    // G_APPLICATION_FLAGS_NONE - флаги приложения (пока без дополнительных флагов).
    GtkApplication *app = gtk_application_new("com.example.GTKApp", G_APPLICATION_DEFAULT_FLAGS);

    // Подключаем сигнал "activate" к нашей функции on_activate.
    // Сигнал "activate" испускается, когда приложение запускается и готово к отображению своих окон.
    // G_CALLBACK() преобразует указатель на функцию в нужный тип для g_signal_connect.
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    // Запускаем приложение GTK. Эта функция передаёт управление циклу обработки событий GTK.
    // Она блокирует выполнение программы до тех пор, пока приложение не завершится.
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    // Уменьшаем счётчик ссылок на объект GtkApplication.
    // Когда счётчик ссылок достигает нуля, объект освобождается.
    // Это важно для предотвращения утечек памяти, так как GtkApplication является GObject.
    g_object_unref(app);

    return status; // Возвращаем код завершения приложения.
}