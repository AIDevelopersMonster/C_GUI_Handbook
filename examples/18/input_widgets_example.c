#include <gtk/gtk.h> // Подключаем основную библиотеку GTK.
                       // Этот заголовочный файл содержит все необходимые определения
                       // для создания графических интерфейсов с помощью GTK.

/**
 * @brief Обработчик сигнала "changed" для GtkEntry.
 *
 * Эта функция вызывается каждый раз, когда текст в GtkEntry (однострочном поле ввода)
 * изменяется. Это может произойти при вводе символов, удалении текста или вставке.
 *
 * @param entry Указатель на GtkEntry, который испустил этот сигнал.
 * Мы используем его, чтобы получить текущий текст из поля.
 * @param user_data Универсальный указатель на пользовательские данные.
 * В этом примере он не используется (передается NULL).
 */
void on_entry_changed(GtkEntry *entry, gpointer user_data) {
    // Получаем текущий текст из поля ввода.
    // gtk_entry_get_text() возвращает указатель на внутреннюю строку GtkEntry.
    // Эту строку не нужно освобождать, но она становится недействительной,
    // если текст в поле снова изменится.
    const gchar *text = gtk_entry_get_text(entry);
    
    // Выводим измененный текст в консоль.
    g_print("Entry changed: %s\n", text);
}

/**
 * @brief Обработчик сигнала "value-changed" для GtkSpinButton.
 *
 * Эта функция вызывается всякий раз, когда числовое значение в GtkSpinButton
 * изменяется. Это может произойти как при кликах по стрелкам, так и при
 * ручном вводе числа пользователем.
 *
 * @param spin Указатель на GtkSpinButton, который испустил этот сигнал.
 * Используем его для получения текущего числового значения.
 * @param user_data Универсальный указатель на пользовательские данные (NULL).
 */
void on_spin_changed(GtkSpinButton *spin, gpointer user_data) {
    // Получаем текущее значение спиннера как целое число.
    // Если спиннер настроен на дробные числа, можно использовать gtk_spin_button_get_value().
    gint value = gtk_spin_button_get_value_as_int(spin);
    
    // Выводим новое значение в консоль.
    g_print("Spin value: %d\n", value);
}

/**
 * @brief Обработчик сигнала "toggled" для GtkCheckButton.
 *
 * Эта функция вызывается, когда состояние GtkCheckButton (чекбокса) меняется,
 * то есть когда пользователь отмечает или снимает отметку с флажка.
 *
 * @param check Указатель на GtkToggleButton (базовый класс для GtkCheckButton),
 * который испустил этот сигнал. Используем его, чтобы узнать
 * текущее состояние чекбокса.
 * @param user_data Универсальный указатель на пользовательские данные (NULL).
 */
void on_check_toggled(GtkToggleButton *check, gpointer user_data) {
    // Проверяем, активно ли (отмечено) текущее состояние чекбокса.
    // gtk_toggle_button_get_active() возвращает TRUE, если флажок установлен, и FALSE, если снят.
    gboolean active = gtk_toggle_button_get_active(check);
    
    // Выводим текущее состояние чекбокса в консоль.
    // Используем тернарный оператор для вывода "ON" или "OFF".
    g_print("Check toggled: %s\n", active ? "ON" : "OFF");
}

/**
 * @brief Главная функция программы, точка входа.
 *
 * Эта функция отвечает за инициализацию GTK, создание главного окна,
 * добавление в него всех элементов пользовательского ввода (GtkEntry, GtkSpinButton, GtkCheckButton)
 * и запуск основного цикла обработки событий GTK.
 *
 * @param argc Количество аргументов командной строки, переданных программе.
 * @param argv Массив строк аргументов командной строки.
 * GTK может использовать эти аргументы для своих внутренних настроек.
 * @return Код завершения программы (0 при успешном выполнении).
 */
int main(int argc, char *argv[]) {
    // 1. Инициализация GTK.
    // Это первый и обязательный вызов в любой GTK-программе.
    // Он подготавливает библиотеку к работе, обрабатывает специфические
    // для GTK аргументы командной строки и устанавливает базовые параметры.
    gtk_init(&argc, &argv);

    // 2. Создание главного окна приложения.
    // GtkWidget* - это универсальный указатель на любой виджет в GTK.
    // gtk_window_new(GTK_WINDOW_TOPLEVEL) создает новое окно верхнего уровня,
    // которое является независимым окном на рабочем столе.
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    // Устанавливаем заголовок окна.
    gtk_window_set_title(GTK_WINDOW(window), "Пример Полей Ввода");
    
    // Устанавливаем размер окна по умолчанию (ширина, высота в пикселях).
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    
    // Центрируем окно на экране при его первом появлении.
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Подключение сигнала "destroy" к функции gtk_main_quit.
    // Сигнал "destroy" испускается, когда пользователь пытается закрыть окно.
    // gtk_main_quit() останавливает главный цикл событий GTK, что приводит к
    // корректному завершению работы программы. Это критически важно для
    // предотвращения "зависания" приложения после закрытия окна.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 3. Создание вертикального контейнера GtkBox.
    // Мы будем использовать GtkBox для размещения всех наших элементов ввода
    // вертикально, друг под другом.
    // GTK_ORIENTATION_VERTICAL - указывает на вертикальную компоновку.
    // 10 - это 'spacing', фиксированный отступ в 10 пикселей между каждым
    //      дочерним виджетом внутри этого GtkBox.
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // Добавляем созданный GtkBox в главное окно.
    // GtkWindow является контейнером, который может содержать только один дочерний виджет.
    // В данном случае этим виджетом будет наш vbox.
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // 4. Создание GtkEntry (однострочного текстового поля).
    GtkWidget *entry = gtk_entry_new();
    // Устанавливаем текст-заполнитель (placeholder text), который отображается,
    // когда поле пустое и не в фокусе. Он исчезает при вводе текста.
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Введите ваше имя...");
    // Добавляем GtkEntry в начало (верх) нашего вертикального GtkBox.
    // FALSE, FALSE, 0: виджет не будет растягиваться, не будет заполнять всю ширину,
    // и не будет иметь дополнительного отступа (используется spacing GtkBox).
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    // Подключаем наш обработчик on_entry_changed к сигналу "changed" GtkEntry.
    g_signal_connect(entry, "changed", G_CALLBACK(on_entry_changed), NULL);

    // 5. Создание GtkSpinButton (числового спиннера).
    // GtkSpinButton работает совместно с GtkAdjustment, который определяет
    // диапазон значений и шаг.
    // gtk_adjustment_new(value, lower, upper, step_increment, page_increment, page_size)
    //   - 0: начальное значение
    //   - 0: нижний предел (минимум)
    //   - 100: верхний предел (максимум)
    //   - 1: шаг при нажатии на стрелки (один клик)
    //   - 10: шаг при нажатии PageUp/PageDown
    //   - 0: размер страницы (обычно 0 для SpinButton)
    GtkAdjustment *adj = gtk_adjustment_new(0, 0, 100, 1, 10, 0);
    
    // Создаем GtkSpinButton, привязывая его к созданному GtkAdjustment.
    //   - adj: наш объект GtkAdjustment
    //   - 1.0: скорость "взбирания" значения при удержании кнопки (обычно 1.0)
    //   - 0: количество знаков после запятой для отображения (0 означает целые числа)
    GtkWidget *spin = gtk_spin_button_new(adj, 1.0, 0);
    // Добавляем GtkSpinButton в вертикальный GtkBox.
    gtk_box_pack_start(GTK_BOX(vbox), spin, FALSE, FALSE, 0);
    // Подключаем наш обработчик on_spin_changed к сигналу "value-changed" GtkSpinButton.
    g_signal_connect(spin, "value-changed", G_CALLBACK(on_spin_changed), NULL);

    // 6. Создание GtkCheckButton (флажка/чекбокса).
    // Создаем чекбокс с текстовой меткой.
    GtkWidget *check = gtk_check_button_new_with_label("Я согласен с условиями");
    // Устанавливаем начальное состояние чекбокса.
    // FALSE означает, что чекбокс изначально не будет отмечен.
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), FALSE);
    // Добавляем GtkCheckButton в вертикальный GtkBox.
    gtk_box_pack_start(GTK_BOX(vbox), check, FALSE, FALSE, 0);
    // Подключаем наш обработчик on_check_toggled к сигналу "toggled" GtkCheckButton.
    g_signal_connect(check, "toggled", G_CALLBACK(on_check_toggled), NULL);

    // 7. Отображение всех виджетов в окне.
    // По умолчанию виджеты создаются невидимыми. gtk_widget_show_all() делает
    // видимым само окно и все виджеты, которые в него добавлены.
    gtk_widget_show_all(window);

    // 8. Запуск главного цикла обработки событий GTK.
    // Эта функция передает управление библиотеке GTK. Программа переходит в
    // режим ожидания событий (кликов мышью, нажатий клавиш, системных сообщений).
    // Этот цикл продолжается до тех пор, пока не будет вызвана функция gtk_main_quit().
    gtk_main();

    // Возвращаем 0, что является стандартным кодом успешного завершения программы.
    return 0;
}