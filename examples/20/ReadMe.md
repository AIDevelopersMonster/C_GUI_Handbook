# Глава 20: Деревья и Таблицы (GtkTreeView)

В этой главе мы осваиваем **`GtkTreeView`** — мощный и гибкий виджет GTK, предназначенный для отображения данных как в **табличной** (строки и столбцы), так и в **иерархической** (древовидной) структуре. `GtkTreeView` не хранит данные самостоятельно, а выступает в роли "представления", визуализируя информацию из внешней **модели данных**.

Мы рассмотрим, как работать с `GtkTreeView` в двух основных сценариях, используя разные модели данных:

1.  **`GtkListStore`**: Для простых табличных данных.
2.  **`GtkTreeStore`**: Для иерархических (древовидных) данных.

-----

## 🔹 Ключевые компоненты `GtkTreeView`

Для эффективной работы с `GtkTreeView` важно понимать его основные составляющие:

  * **`GtkTreeView`**: Сам виджет, который вы видите на экране. Он является *представлением* данных, но не хранит их.
  * **`GtkTreeModel`**: Это базовый интерфейс, который определяет, как виджет `GtkTreeView` взаимодействует с данными. `GtkListStore` и `GtkTreeStore` являются реализациями этого интерфейса.
  * **`GtkListStore`**: Используется как **модель данных** для **табличной** структуры. Это простой список строк, где каждая строка имеет фиксированное количество столбцов разных типов.
  * **`GtkTreeStore`**: Используется как **модель данных** для **иерархической (древовидной)** структуры. В отличие от `GtkListStore`, `GtkTreeStore` позволяет каждой строке иметь дочерние элементы, формируя ветвистое дерево.
  * **`GtkTreeViewColumn`**: Определяет отдельный **столбец** в `GtkTreeView`. Он включает заголовок столбца и правила, по которым данные из модели отображаются в этом столбце.
  * **`GtkCellRenderer`**: Это не виджет, а объект, ответственный за **отрисовку (рендеринг)** содержимого отдельной ячейки в `GtkTreeViewColumn`. Например, `GtkCellRendererText` отображает текст, а `GtkCellRendererPixbuf` — изображения.

-----

## 🔹 Функции GTK, которые мы используем

| Функция                           | Назначение                                                    |
| :-------------------------------- | :------------------------------------------------------------ |
| `gtk_init()`                      | Инициализирует библиотеку GTK.                                |
| `gtk_main()`                      | Запускает основной цикл обработки событий GTK.                 |
| `gtk_main_quit()`                 | Останавливает основной цикл GTK.                              |
| `gtk_window_new()`                | Создаёт новое окно верхнего уровня.                           |
| `gtk_window_set_title()`          | Устанавливает заголовок окна.                                 |
| `gtk_window_set_default_size()`   | Устанавливает размер окна по умолчанию.                       |
| `gtk_window_set_position()`       | Устанавливает позицию окна на экране.                         |
| `g_signal_connect()`              | Подключает callback-функцию к сигналу виджета.                |
| `gtk_scrolled_window_new()`       | Создаёт прокручиваемое окно (для содержимого, которое может превышать размер виджета). |
| `gtk_scrolled_window_set_policy()`| Устанавливает политику отображения полос прокрутки.         |
| `gtk_container_add()`             | Добавляет виджет в контейнер.                                 |
| `gtk_widget_show_all()`           | Делает видимым виджет и все его дочерние элементы.            |
| `gtk_list_store_new()`            | Создаёт новую модель данных `GtkListStore`.                   |
| `gtk_list_store_append()`         | Добавляет новую строку в `GtkListStore`.                      |
| `gtk_list_store_set()`            | Устанавливает значения ячеек в строке `GtkListStore`.         |
| `gtk_tree_store_new()`            | Создаёт новую модель данных `GtkTreeStore`.                   |
| `gtk_tree_store_append()`         | Добавляет новую строку в `GtkTreeStore` (может быть дочерней).|
| `gtk_tree_store_set()`            | Устанавливает значения ячеек в строке `GtkTreeStore`.         |
| `gtk_tree_view_new_with_model()`  | Создаёт `GtkTreeView`, привязывая его к модели данных.       |
| `gtk_tree_view_append_column()`   | Добавляет столбец в `GtkTreeView`.                             |
| `gtk_tree_view_column_new_with_attributes()` | Создаёт новый столбец с атрибутами для рендерера.     |
| `gtk_tree_view_column_set_sort_column_id()` | Включает сортировку по столбцу при клике на заголовок. |
| `gtk_tree_view_set_expander_column()` | Устанавливает столбец, в котором будут отображаться кнопки разворачивания/сворачивания для дерева. |
| `gtk_tree_view_column_set_resizable()` | Позволяет пользователю изменять размер столбца.        |
| `gtk_cell_renderer_text_new()`    | Создаёт новый рендерер для отображения текста.                |
| `g_object_unref()`                | Уменьшает счётчик ссылок на объект (для освобождения памяти). |

-----

## 📁 Исходные файлы в этой главе

  * `treeview_liststore_example.c` — Пример создания табличного `GtkTreeView` с использованием `GtkListStore`.
  * `treeview_treestore_example.c` — Пример создания древовидного `GtkTreeView` с использованием `GtkTreeStore`.

-----

## ✅ `treeview_liststore_example.c` — Табличный `GtkTreeView`

В этом примере мы создадим простое окно с таблицей, отображающей данные о нескольких пользователях (Имя, Возраст, Профессия). Данные будут храниться в `GtkListStore`.

### 🔧 Как скомпилировать и запустить

1.  **Сохраните** код из `treeview_liststore_example.c` в файл с таким же названием.
2.  **Откройте терминал** и перейдите в директорию, где вы сохранили файл.
3.  **Скомпилируйте** программу:
    ```bash
    gcc treeview_liststore_example.c -o treeview_liststore_example `pkg-config --cflags --libs gtk+-3.0`
    ```
4.  **Запустите** скомпилированную программу:
    ```bash
    ./treeview_liststore_example
    ```

### 💻 Как устроено окно

1.  **Главное окно** (`GtkWindow`) создаётся и настраивается (заголовок, размер, позиция).
2.  **`GtkListStore`** создаётся с тремя столбцами (`G_TYPE_STRING` для имени, `G_TYPE_INT` для возраста, `G_TYPE_STRING` для профессии).
3.  В `GtkListStore` **добавляются данные** о нескольких пользователях с помощью `gtk_list_store_append()` и `gtk_list_store_set()`.
4.  **`GtkTreeView`** создаётся и связывается с `GtkListStore` (`gtk_tree_view_new_with_model()`). После этого `GtkListStore` можно безопасно "отпустить" с помощью `g_object_unref()`, так как `GtkTreeView` сам увеличивает счётчик ссылок на модель.
5.  Для каждого столбца таблицы (`Имя`, `Возраст`, `Профессия`) создаётся **`GtkTreeViewColumn`** с соответствующим заголовком и **`GtkCellRendererText`**. `GtkCellRendererText` привязывается к нужному столбцу модели через функцию `gtk_tree_view_column_new_with_attributes()`.
6.  Включена **сортировка** данных по клику на заголовки столбцов с помощью `gtk_tree_view_column_set_sort_column_id()`.
7.  `GtkTreeView` помещается в **`GtkScrolledWindow`**, чтобы обеспечить прокрутку, если данных будет слишком много.
8.  Все виджеты отображаются (`gtk_widget_show_all()`) и запускается основной цикл GTK (`gtk_main()`).

### 🖥 Ожидаемый результат

При запуске программы вы увидите окно с заголовком **"Пример GtkTreeView (ListStore)"**. Внутри окна будет таблица с тремя колонками: **"Имя"**, **"Возраст"**, **"Профессия"**. Таблица будет содержать данные четырёх пользователей: Алисы, Боба, Анны и Чарли. Вы сможете кликать по заголовкам столбцов, чтобы **сортировать** данные по соответствующей колонке, а также **изменять ширину** колонок.

-----

## 🚀 `treeview_treestore_example.c` — Древовидный `GtkTreeView`

В этом примере мы создадим окно с иерархическим списком, демонстрирующим древовидную структуру категорий и подкатегорий. Для этого будет использоваться модель данных `GtkTreeStore`.

### 🔧 Как скомпилировать и запустить

1.  **Сохраните** код из `treeview_treestore_example.c` в файл с таким же названием.
2.  **Откройте терминал** и перейдите в директорию, где вы сохранили файл.
3.  **Скомпилируйте** программу:
    ```bash
    gcc treeview_treestore_example.c -o treeview_treestore_example `pkg-config --cflags --libs gtk+-3.0`
    ```
4.  **Запустите** скомпилированную программу:
    ```bash
    ./treeview_treestore_example
    ```

### 💻 Как устроено окно

1.  **Главное окно** (`GtkWindow`) создаётся и настраивается.
2.  **`GtkTreeStore`** создаётся с одним столбцом (`G_TYPE_STRING`) для отображаемого текста.
3.  **Иерархические данные** добавляются в `GtkTreeStore`. Корневые узлы создаются с `NULL` в качестве родителя, а дочерние узлы — с итератором родительского узла. Например, "Собака" и "Кот" добавляются как дочерние элементы для "Животные", а "Розы" и "Тюльпаны" — для "Цветы".
4.  **`GtkTreeView`** создаётся и связывается с `GtkTreeStore`. Модель также "отпускается" с помощью `g_object_unref()`.
5.  Создаётся одна **`GtkTreeViewColumn`** с заголовком "Категории" и **`GtkCellRendererText`**, привязанным к текстовому столбцу модели.
6.  `gtk_tree_view_set_expander_column()` устанавливает столбец, который будет содержать элементы управления для разворачивания/сворачивания узлов дерева.
7.  `GtkTreeView` помещается в **`GtkScrolledWindow`** для обеспечения прокрутки.
8.  Все виджеты отображаются (`gtk_widget_show_all()`) и запускается основной цикл GTK (`gtk_main()`).

### 🖥 Ожидаемый результат

При запуске программы вы увидите окно с заголовком **"Пример GtkTreeView (TreeStore)"**. Внутри окна будет отображаться **древовидная структура** (иерархический список). Вы увидите корневые узлы, такие как **"Животные"** и **"Растения"**. Вы сможете **раскрывать** эти узлы (нажимая на маленькие треугольники), чтобы увидеть их дочерние элементы (например, "Собака", "Кот" под "Животными", а "Цветы" и "Деревья" под "Растениями"). Вы также сможете разворачивать "Цветы", чтобы увидеть "Розы" и "Тюльпаны".

-----

