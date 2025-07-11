#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.
                       // Этот заголовочный файл содержит все необходимые определения
                       // для создания графических интерфейсов с помощью GTK.

/**
 * @brief Обработчик события "changed" для GtkComboBoxText.
 *
 * Эта функция вызывается каждый раз, когда пользователь выбирает новый элемент
 * из выпадающего списка GtkComboBoxText.
 *
 * @param widget Указатель на GtkComboBox, который испустил сигнал.
 * Здесь мы приводим его к GtkComboBoxText*, чтобы использовать
 * специфичную для него функцию gtk_combo_box_text_get_active_text().
 * @param data Пользовательские данные (в данном примере NULL),
 * передаваемые при подключении сигнала.
 */
void on_combo_changed(GtkComboBox *widget, gpointer data) {
    // Получаем активный (выбранный) текст из GtkComboBoxText.
    // gtk_combo_box_text_get_active_text() возвращает новую строку,
    // которую необходимо освободить с помощью g_free(), когда она больше не нужна,
    // так как эта строка выделяется динамически.
    gchar *text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));

    // Проверяем, что текст не NULL. Это может произойти, если список пуст
    // или если что-то пошло не так при получении текста.
    if (text != NULL) {
        g_print("Вы выбрали: %s\n", text); // Выводим выбранный текст в консоль.
        g_free(text);                      // Освобождаем память, выделенную для строки.
    }
}

/**
 * @brief Главная функция программы.
 *
 * Инициализирует GTK, создает главное окно, добавляет в него GtkComboBoxText
 * с предопределенными текстовыми значениями и запускает основной цикл событий GTK.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    // 1. Инициализация GTK.
    // Это первый и обязательный вызов в любой GTK-программе.
    // Он подготавливает библиотеку к работе и обрабатывает специфические
    // для GTK аргументы командной строки.
    gtk_init(&argc, &argv);

    // 2. Создание главного окна приложения.
    // gtk_window_new(GTK_WINDOW_TOPLEVEL) создает независимое окно на рабочем столе.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    // Устанавливаем заголовок окна.
    gtk_window_set_title(GTK_WINDOW(window), "Пример GtkComboBoxText");
    
    // Устанавливаем размер окна по умолчанию (ширина, высота в пикселях).
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);
    
    // Центрируем окно на экране при его первом появлении.
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Подключение сигнала "destroy" к функции gtk_main_quit.
    // Это обеспечивает корректное завершение приложения при закрытии окна.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 3. Создание GtkComboBoxText.
    // Это упрощенный выпадающий список, предназначенный для работы с простыми текстовыми строками.
    // GTK автоматически управляет внутренней моделью данных для этого виджета.
    GtkWidget *combo = gtk_combo_box_text_new();

    // 4. Добавление элементов в GtkComboBoxText.
    // gtk_combo_box_text_append_text() добавляет новую строку в конец списка.
    // Можно добавлять сколько угодно строк.
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "C");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Python");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Rust");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Java");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Go");

    // 5. Установка активного элемента по умолчанию.
    // gtk_combo_box_set_active() устанавливает элемент с заданным индексом
    // как выбранный (индексация начинается с 0). Здесь выбираем первый элемент, "C".
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

    // 6. Подключение обработчика события "changed".
    // Сигнал "changed" испускается GtkComboBox (и его наследниками, такими как GtkComboBoxText)
    // каждый раз, когда выбранный элемент в списке изменяется.
    g_signal_connect(combo, "changed", G_CALLBACK(on_combo_changed), NULL);

    // 7. Размещение GtkComboBox в контейнере.
    // Создаем GtkBox для размещения ComboBox в окне. Используем вертикальную компоновку
    // с отступом в 10 пикселей между дочерними виджетами.
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // Устанавливаем внешний отступ (границу) вокруг всего GtkBox в 20 пикселей.
    gtk_container_set_border_width(GTK_CONTAINER(box), 20);
    
    // Добавляем GtkComboBox в GtkBox.
    // TRUE, TRUE, 10:
    //   - expand (TRUE): ComboBox может занимать дополнительное пространство.
    //   - fill (TRUE): ComboBox будет заполнять выделенное пространство (в данном случае по горизонтали).
    //   - padding (10): дополнительный отступ вокруг ComboBox внутри GtkBox (сверх spacing GtkBox).
    gtk_box_pack_start(GTK_BOX(box), combo, TRUE, TRUE, 10);
    
    // Добавляем GtkBox (содержащий ComboBox) в главное окно.
    gtk_container_add(GTK_CONTAINER(window), box);

    // 8. Отображение всех виджетов.
    // По умолчанию виджеты создаются невидимыми. Эта функция делает видимыми
    // главное окно и все виджеты, которые в него добавлены.
    gtk_widget_show_all(window);

    // 9. Запуск главного цикла событий GTK.
    // Передает управление библиотеке GTK. Программа переходит в режим ожидания
    // и обработки пользовательских событий, пока не будет вызвана gtk_main_quit().
    gtk_main();

    // 10. Завершение программы.
    return 0;
}