#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.

// Перечисление для удобства определения индексов столбцов в GtkListStore.
// Это делает код более читабельным и менее подверженным ошибкам,
// чем использование "магических" чисел.
enum {
    COLUMN_NAME, // Столбец для хранения названия опции (например, "Опция А").
    COLUMN_ID,   // Столбец для хранения числового идентификатора опции (например, 101).
    NUM_COLS     // Общее количество столбцов в модели. Всегда должен быть последним.
};

/**
 * @brief Обработчик события "changed" для GtkComboBox с GtkListStore.
 *
 * Эта функция вызывается, когда пользователь выбирает новый элемент
 * из выпадающего списка. Она демонстрирует, как получить данные
 * из связанной модели GtkListStore, используя итератор GtkTreeIter.
 *
 * @param widget Указатель на GtkComboBox, который испустил сигнал.
 * @param data Пользовательские данные (в данном примере NULL).
 */
void on_combo_liststore_changed(GtkComboBox *widget, gpointer data) {
    // 1. Получаем модель данных, связанную с GtkComboBox.
    // GtkComboBox работает с обобщенным интерфейсом GtkTreeModel.
    // Мы знаем, что в нашем случае это GtkListStore.
    GtkTreeModel *model = gtk_combo_box_get_model(widget);
    
    // 2. Объявляем итератор.
    // GtkTreeIter - это структура, которая действует как "указатель" на
    // конкретную строку в GtkTreeModel.
    GtkTreeIter iter;

    // 3. Получаем активный (выбранный) итератор в модели.
    // gtk_combo_box_get_active_iter() заполняет структуру 'iter'
    // данными о выбранной строке и возвращает TRUE, если элемент выбран (т.е. iter действителен).
    if (gtk_combo_box_get_active_iter(widget, &iter)) {
        gchar *name; // Переменная для хранения извлеченного имени.
        gint id;     // Переменная для хранения извлеченного ID.

        // 4. Получаем данные из модели по итератору и индексу столбца.
        // gtk_tree_model_get() позволяет извлечь значения из указанной строки модели.
        // Параметры:
        //   - model: наша модель данных (GtkListStore, приведенный к GtkTreeModel).
        //   - &iter: итератор, указывающий на текущую (выбранную) строку.
        //   - COLUMN_NAME: индекс первого столбца, значение которого хотим получить.
        //   - &name: адрес переменной, куда будет записано значение из COLUMN_NAME (строка).
        //   - COLUMN_ID: индекс второго столбца, значение которого хотим получить.
        //   - &id: адрес переменной, куда будет записано значение из COLUMN_ID (целое число).
        //   - -1: признак конца списка аргументов.
        gtk_tree_model_get(model, &iter,
                           COLUMN_NAME, &name,
                           COLUMN_ID, &id,
                           -1); // Завершает список аргументов

        // 5. Выводим полученные данные в консоль.
        g_print("Вы выбрали: %s (ID: %d)\n", name, id);
        
        // 6. Освобождаем строку 'name'.
        // gtk_tree_model_get() выделяет новую память для строковых значений,
        // поэтому их необходимо освобождать с помощью g_free() после использования.
        g_free(name); 
    }
}

/**
 * @brief Главная функция программы.
 *
 * Инициализирует GTK, создает главное окно, GtkListStore (модель данных),
 * наполняет его данными, создает GtkComboBox, связывает его с GtkListStore
 * и GtkCellRendererText для отображения данных, и запускает главный цикл событий GTK.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив строк аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    // 1. Инициализация GTK.
    gtk_init(&argc, &argv);

    // 2. Создание главного окна.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Пример ComboBox с ListStore");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 3. Создание GtkListStore (модели данных).
    // gtk_list_store_new() создает новую пустую модель данных.
    // Первый аргумент: NUM_COLS - общее количество столбцов, которое мы определили в enum.
    // Следующие аргументы: типы данных для каждого столбца в порядке их определения.
    // COLUMN_NAME будет G_TYPE_STRING, COLUMN_ID будет G_TYPE_INT.
    GtkListStore *store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_INT);
    GtkTreeIter iter; // Итератор, который будет указывать на текущую строку при добавлении.

    // 4. Наполнение GtkListStore данными.
    // Для каждой записи в выпадающем списке мы выполняем следующие шаги:
    //   - gtk_list_store_append(store, &iter): добавляет новую пустую строку в конец
    //     GtkListStore и устанавливает 'iter' на эту новую строку.
    //   - gtk_list_store_set(store, &iter, column_idx, value, -1): устанавливает значения
    //     для столбцов в текущей строке (указанной 'iter').
    
    gtk_list_store_append(store, &iter); // Добавляем первую строку.
    gtk_list_store_set(store, &iter,
                       COLUMN_NAME, "Опция А", // Значение для COLUMN_NAME (строка)
                       COLUMN_ID, 101,        // Значение для COLUMN_ID (целое число)
                       -1);                   // -1 означает конец списка аргументов.

    gtk_list_store_append(store, &iter); // Добавляем вторую строку.
    gtk_list_store_set(store, &iter,
                       COLUMN_NAME, "Опция Б",
                       COLUMN_ID, 102,
                       -1);

    gtk_list_store_append(store, &iter); // Добавляем третью строку.
    gtk_list_store_set(store, &iter,
                       COLUMN_NAME, "Опция В",
                       COLUMN_ID, 103,
                       -1);

    gtk_list_store_append(store, &iter); // Добавляем четвертую строку.
    gtk_list_store_set(store, &iter,
                       COLUMN_NAME, "Опция Г",
                       COLUMN_ID, 104,
                       -1);

    // 5. Создание GtkComboBox с использованием GtkListStore в качестве модели.
    // gtk_combo_box_new_with_model() принимает GtkTreeModel*.
    // Мы приводим наш GtkListStore* к GtkTreeModel*, так как GtkListStore
    // реализует этот интерфейс.
    GtkWidget *combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(store));

    // 6. Создание GtkCellRendererText для отображения текстового столбца.
    // GtkCellRendererText - это не виджет, а объект, который знает, как отрисовать
    // текст внутри ячейки виджета. Он используется GtkComboBox (и GtkTreeView)
    // для визуализации данных из модели.
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    // 7. Добавление GtkCellRenderer в GtkComboBox и связывание его со столбцом модели.
    // GtkComboBox реализует интерфейс GtkCellLayout, что позволяет нам управлять
    // тем, как данные из модели будут отображаться.
    // gtk_cell_layout_pack_start(): добавляет рендерер в компоновку ячеек ComboBox.
    //   - GTK_CELL_LAYOUT(combo): приведение GtkComboBox* к GtkCellLayout*.
    //   - renderer: наш GtkCellRendererText.
    //   - TRUE: указывает, что рендерер должен расширяться, чтобы заполнить доступное
    //           пространство в ячейке.
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);

    // gtk_cell_layout_set_attributes(): связывает свойство рендерера ("text")
    // с конкретным столбцом в модели данных (COLUMN_NAME).
    // Это говорит ComboBox: "Для отображения текста в ComboBox используй данные
    // из столбца COLUMN_NAME нашей модели 'store'".
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer, "text", COLUMN_NAME, NULL);

    // 8. Установка активного элемента по умолчанию.
    // Устанавливаем второй элемент (индекс 1) как изначально выбранный ("Опция Б").
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 1); // 0-индексированный

    // 9. Подключение обработчика события "changed".
    // Подключаем наш обработчик on_combo_liststore_changed к сигналу "changed" GtkComboBox.
    g_signal_connect(combo, "changed", G_CALLBACK(on_combo_liststore_changed), NULL);

    // 10. Размещение GtkComboBox в контейнере.
    // Используем GtkBox для размещения ComboBox в окне, с вертикальной компоновкой и отступом.
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box), 20); // Внешняя граница GtkBox.
    
    // Добавляем GtkComboBox в GtkBox.
    // FALSE, FALSE, 0:
    //   - expand (FALSE): ComboBox не будет растягиваться, чтобы заполнить свободное пространство.
    //   - fill (FALSE): ComboBox будет иметь свой естественный размер.
    //   - padding (0): без дополнительного отступа (используется spacing GtkBox).
    gtk_box_pack_start(GTK_BOX(box), combo, FALSE, FALSE, 0);
    
    // Добавляем GtkBox (содержащий ComboBox) в главное окно.
    gtk_container_add(GTK_CONTAINER(window), box);

    // 11. Отображение всех виджетов.
    gtk_widget_show_all(window);

    // 12. Запуск главного цикла событий GTK.
    gtk_main();

    // 13. Освобождение GtkListStore.
    // g_object_unref() уменьшает счетчик ссылок на объект 'store'.
    // GtkComboBox увеличивает счетчик ссылок на модель при ее установке.
    // Когда GtkComboBox уничтожается (например, при закрытии окна), он уменьшает этот счетчик.
    // Здесь мы уменьшаем ссылку, которая была получена при создании ListStore.
    // Когда счетчик ссылок достигает нуля, объект ListStore будет автоматически уничтожен.
    g_object_unref(store); 

    return 0; // Возвращаем код успешного завершения программы.
}