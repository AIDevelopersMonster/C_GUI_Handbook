#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.

// Перечисление для удобства определения индексов столбцов в GtkListStore.
// Это делает код более читабельным и менее подверженным ошибкам.
enum {
    COL_NAME,       // Столбец для имени (G_TYPE_STRING)
    COL_AGE,        // Столбец для возраста (G_TYPE_INT)
    COL_OCCUPATION, // Столбец для профессии (G_TYPE_STRING)
    NUM_COLS        // Общее количество столбцов
};

/**
 * @brief Главная функция программы.
 *
 * Инициализирует GTK, создает окно, GtkListStore (модель данных),
 * наполняет его данными, создает GtkTreeView, настраивает его колонки
 * и запускает главный цикл событий GTK.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // 1. Создание главного окна.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Пример GtkTreeView (ListStore)");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 2. Создание GtkListStore (модели данных).
    // gtk_list_store_new() создает новую модель данных.
    // Первый аргумент: NUM_COLS - общее количество столбцов.
    // Остальные аргументы: типы данных для каждого столбца.
    GtkListStore *store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING);
    GtkTreeIter iter; // Итератор для указания на текущую строку.

    // 3. Добавление данных в GtkListStore.
    // Каждая пара gtk_list_store_append() и gtk_list_store_set() добавляет одну строку.
    
    // Первая строка: Алиса, 30, Инженер
    gtk_list_store_append(store, &iter); // Добавляем новую строку и получаем итератор.
    gtk_list_store_set(store, &iter,
                       COL_NAME, "Алиса",      // Устанавливаем имя
                       COL_AGE, 30,           // Устанавливаем возраст
                       COL_OCCUPATION, "Инженер", // Устанавливаем профессию
                       -1);                   // -1 означает конец списка аргументов.

    // Вторая строка: Боб, 25, Дизайнер
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       COL_NAME, "Боб",
                       COL_AGE, 25,
                       COL_OCCUPATION, "Дизайнер",
                       -1);

    // Третья строка: Анна, 35, Врач
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       COL_NAME, "Анна",
                       COL_AGE, 35,
                       COL_OCCUPATION, "Врач",
                       -1);
    
    // Четвертая строка: Чарли, 28, Программист
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       COL_NAME, "Чарли",
                       COL_AGE, 28,
                       COL_OCCUPATION, "Программист",
                       -1);


    // 4. Создание GtkTreeView с созданной моделью данных.
    // GtkTreeView - это виджет-представление, которое отображает данные из GtkTreeModel.
    GtkWidget *view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));

    // Отключаем автоматический инкремент счетчика ссылок на модель.
    // GtkTreeView сам увеличивает счетчик ссылок при связывании,
    // поэтому мы можем безопасно уменьшить наш.
    g_object_unref(store); 

    // 5. Добавление столбцов (колонок) в GtkTreeView.
    // Для каждого столбца в таблице мы создаем GtkTreeViewColumn.
    // GtkTreeViewColumn связывает столбец модели с рендерером, который отображает данные.
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // --- Колонка "Имя" ---
    // Создаем рендерер для отображения текста.
    renderer = gtk_cell_renderer_text_new();
    // Создаем столбец с заголовком "Имя".
    // "text", COL_NAME: связываем свойство "text" рендерера с данными из столбца COL_NAME модели.
    column = gtk_tree_view_column_new_with_attributes("Имя", renderer, "text", COL_NAME, NULL);
    // Добавляем столбец в GtkTreeView.
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    // Включение сортировки по нажатию на заголовки колонок.
    gtk_tree_view_column_set_sort_column_id(column, COL_NAME);


    // --- Колонка "Возраст" ---
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Возраст", renderer, "text", COL_AGE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    gtk_tree_view_column_set_sort_column_id(column, COL_AGE); // Включение сортировки.


    // --- Колонка "Профессия" ---
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Профессия", renderer, "text", COL_OCCUPATION, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    gtk_tree_view_column_set_sort_column_id(column, COL_OCCUPATION); // Включение сортировки.

    // 6. Размещение GtkTreeView в окне.
    // Чтобы GtkTreeView можно было прокручивать, его обычно помещают в GtkScrolledWindow.
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), view);
    // Устанавливаем политику прокрутки (всегда показывать полосы прокрутки)
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // Добавляем GtkScrolledWindow в главное окно.
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    // 7. Отображение всех виджетов.
    gtk_widget_show_all(window);

    // 8. Запуск главного цикла событий GTK.
    gtk_main();

    return 0;
}