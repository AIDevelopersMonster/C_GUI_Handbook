#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.

// Перечисление для удобства определения индексов столбцов в GtkTreeStore.
enum {
    COL_DISPLAY_TEXT, // Столбец для отображаемого текста
    NUM_COLS_TREE     // Общее количество столбцов в этой модели
};

/**
 * @brief Главная функция программы.
 *
 * Инициализирует GTK, создает окно, GtkTreeStore (модель данных дерева),
 * наполняет его иерархическими данными, создает GtkTreeView, настраивает
 * его колонки и запускает главный цикл событий GTK.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // 1. Создание главного окна.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Пример GtkTreeView (TreeStore)");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 2. Создание GtkTreeStore (модели данных для дерева).
    // gtk_tree_store_new() создает иерархическую модель.
    // Первый аргумент: NUM_COLS_TREE - количество столбцов.
    // Остальные аргументы: типы данных для каждого столбца.
    GtkTreeStore *treestore = gtk_tree_store_new(NUM_COLS_TREE, G_TYPE_STRING);
    GtkTreeIter parent_iter, child_iter; // Итераторы для родительских и дочерних узлов.

    // 3. Добавление данных в GtkTreeStore.
    // Данные добавляются иерархически.

    // --- Родительская категория: "Животные" ---
    // gtk_tree_store_append(treestore, &parent_iter, NULL): добавляет новый корневой узел
    // (NULL в качестве родителя) и устанавливает parent_iter на него.
    gtk_tree_store_append(treestore, &parent_iter, NULL); 
    // Устанавливаем текст для корневого узла.
    gtk_tree_store_set(treestore, &parent_iter, COL_DISPLAY_TEXT, "Животные", -1);

    // Дочерние элементы для "Животные":
    // gtk_tree_store_append(treestore, &child_iter, &parent_iter): добавляет новый дочерний узел
    // к узлу, на который указывает parent_iter, и устанавливает child_iter на него.
    gtk_tree_store_append(treestore, &child_iter, &parent_iter);
    gtk_tree_store_set(treestore, &child_iter, COL_DISPLAY_TEXT, "Собака", -1);

    gtk_tree_store_append(treestore, &child_iter, &parent_iter);
    gtk_tree_store_set(treestore, &child_iter, COL_DISPLAY_TEXT, "Кот", -1);
    
    gtk_tree_store_append(treestore, &child_iter, &parent_iter);
    gtk_tree_store_set(treestore, &child_iter, COL_DISPLAY_TEXT, "Птица", -1);

    // --- Еще одна родительская категория: "Растения" ---
    gtk_tree_store_append(treestore, &parent_iter, NULL);
    gtk_tree_store_set(treestore, &parent_iter, COL_DISPLAY_TEXT, "Растения", -1);

    // Дочерние элементы для "Растения":
    gtk_tree_store_append(treestore, &child_iter, &parent_iter);
    gtk_tree_store_set(treestore, &child_iter, COL_DISPLAY_TEXT, "Цветы", -1);
    
    // Подкатегория для "Цветы"
    GtkTreeIter sub_child_iter;
    gtk_tree_store_append(treestore, &sub_child_iter, &child_iter); // parent_iter теперь - "Цветы"
    gtk_tree_store_set(treestore, &sub_child_iter, COL_DISPLAY_TEXT, "Розы", -1);
    
    gtk_tree_store_append(treestore, &sub_child_iter, &child_iter);
    gtk_tree_store_set(treestore, &sub_child_iter, COL_DISPLAY_TEXT, "Тюльпаны", -1);

    gtk_tree_store_append(treestore, &child_iter, &parent_iter);
    gtk_tree_store_set(treestore, &child_iter, COL_DISPLAY_TEXT, "Деревья", -1);

    // 4. Создание GtkTreeView с созданной моделью GtkTreeStore.
    GtkWidget *tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(treestore));
    g_object_unref(treestore); // Уменьшаем счетчик ссылок на модель.

    // 5. Добавление колонки в GtkTreeView.
    // Для дерева обычно требуется только одна колонка для отображения иерархии.
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    // Заголовок столбца "Категории".
    // "text", COL_DISPLAY_TEXT: связываем свойство "text" рендерера с данными из столбца COL_DISPLAY_TEXT.
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Категории", renderer, "text", COL_DISPLAY_TEXT, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree), column);
    
    // Дополнительные настройки для GtkTreeView:
    // Разрешить сворачивание/разворачивание узлов.
    gtk_tree_view_set_expander_column(GTK_TREE_VIEW(tree), column);
    // Разрешить пользователю изменять размер колонок.
    gtk_tree_view_column_set_resizable(column, TRUE);
    // Автоматически развернуть все корневые узлы при запуске.
    // gtk_tree_view_expand_all(GTK_TREE_VIEW(tree));

    // 6. Размещение GtkTreeView в окне (через GtkScrolledWindow для прокрутки).
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), tree);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    // 7. Отображение всех виджетов.
    gtk_widget_show_all(window);

    // 8. Запуск главного цикла событий GTK.
    gtk_main();

    return 0;
}