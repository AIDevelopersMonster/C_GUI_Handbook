
# Глава 28: Проект GTK с CSS-стилизацией

Это проект демонстрирует создание базового GTK-приложения с использованием Glade для описания пользовательского интерфейса и CSS для его стилизации. В процессе разработки были решены распространённые проблемы, связанные с загрузкой CSS, приоритетом стилей и сопоставлением ID виджетов.

## Содержание

- [1. Обзор проекта](#1-обзор-проекта)
- [2. Файлы проекта](#2-файлы-проекта)
  - [2.1. `style.css`](#21-stylecss)
  - [2.2. `glade_example.c`](#22-glade_examplec)
  - [2.3. `interface.glade`](#23-interfaceglade)
- [3. Инструкции по сборке и запуску](#3-инструкции-по-сборке-и-запуску)

---

## 1. Обзор проекта

Данный проект представляет собой простое GTK-приложение, которое:
- Отображает окно с полем ввода текста, кнопкой и меткой.
- Позволяет вводить текст в поле ввода.
- При нажатии кнопки "Скопировать" копирует текст из поля ввода в метку.
- Полностью стилизуется с помощью внешнего CSS-файла, который изменяет внешний вид окна, поля ввода, кнопки и метки.

Ключевым аспектом проекта является демонстрация правильного применения CSS-стилей к виджетам GTK, используя ID, определённые в Glade, и программно назначаемые имена виджетам для обеспечения надёжной стилизации.

---

## 2. Файлы проекта

Проект состоит из трёх основных файлов: `style.css`, `glade_example.c` и `interface.glade`.

### 2.1. `style.css`

Этот файл содержит все CSS-правила, которые определяют внешний вид вашего приложения.

```css
/* style.css */

/* Общий светло-серый фон для всех окон. */
window {
  background-color: #f5f5f5;
}

/* Светло-зеленый фон для главного окна, закругленные углы и внутренние отступы. */
#main_window {
  background-color: #eaf5ea;
  border-radius: 8px;
  padding: 10px;
}

/* Белый фон для поля ввода, тонкая серая рамка, отступы, закругленные углы и тёмно-серый текст. */
#entry_input {
  background-color: #ffffff;
  border: 1px solid #c0c0c0;
  padding: 6px;
  border-radius: 6px;
  color: #333;
}

/* Более тёмная зелёная рамка для поля ввода при фокусе. */
#entry_input:focus {
  border-color: #87c087;
}

/* Ярко-зелёный фон кнопки, белый текст, отступы, закругленные углы и жирный шрифт. */
#my_button {
  background: #87c087;
  color: white;
  padding: 6px 12px;
  border-radius: 6px;
  font-weight: bold;
}

/* Более тёмный зелёный фон кнопки при наведении. */
#my_button:hover {
  background: #76b176;
}

/* Тёмно-серый цвет текста метки, заданный размер шрифта и отступ сверху. */
#label_output {
  color: #444;
  font-size: 13px;
  padding-top: 6px;
}
````

**Комментарии к `style.css`:**

  - **Назначение:** Этот файл содержит все визуальные правила для элементов UI.
  - **Селекторы:** Используются селекторы по типу виджета (`window`) и по ID (`#main_window`, `#entry_input`, `#my_button`, `#label_output`).
  - **Псевдоклассы:** Применяются псевдоклассы `:focus` для поля ввода и `:hover` для кнопки для интерактивных состояний.
  - **Приоритет стилей:** В данной версии `!important` не используется, так как программная установка CSS-имён в C-коде обеспечивает достаточную надёжность применения стилей, а синтаксические ошибки отсутствуют.

### 2.2. `glade_example.c`

Этот C-код является сердцем приложения, который инициализирует GTK, загружает UI из Glade-файла, применяет CSS-стили и подключает логику работы.

```c
#include <gtk/gtk.h> // Основной заголовочный файл GTK.
#include <libgen.h>  // Для функции dirname(), которая извлекает путь к директории из полного пути.
#include <unistd.h>  // Для функции readlink(), используемой для получения пути к исполняемому файлу.
#include <limits.h>  // Для PATH_MAX, константы, определяющей максимальную длину пути.

// Структура для хранения указателей на важные виджеты.
// Это позволяет легко передавать их между функциями.
typedef struct {
    GtkWidget *entry_input;  // Поле ввода текста.
    GtkWidget *label_output; // Метка для вывода скопированного текста.
    GtkWidget *button;       // Кнопка для запуска копирования.
} AppData;

// Функция для загрузки CSS-файла.
// Она динамически определяет путь к style.css, который должен находиться в той же директории, что и исполняемый файл.
static void load_css(void) {
    // Создаем новый провайдер CSS.
    GtkCssProvider *provider = gtk_css_provider_new();
    // Получаем дисплей по умолчанию, необходимый для применения CSS к экрану.
    GdkDisplay *display = gdk_display_get_default();
    // Получаем экран по умолчанию.
    GdkScreen *screen = gdk_display_get_default_screen(display);

    char exe_path[PATH_MAX], css_path[PATH_MAX];
    // Получаем полный путь к исполняемому файлу.
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len != -1) {
        exe_path[len] = '\0'; // Убеждаемся, что строка нуль-терминирована.
        char *dir = dirname(exe_path); // Извлекаем директорию исполняемого файла.
        // Формируем полный путь к CSS-файлу.
        snprintf(css_path, sizeof(css_path), "%s/style.css", dir);

        // Загружаем CSS из файла.
        if (gtk_css_provider_load_from_path(provider, css_path, NULL))
            g_print("CSS успешно загружен: %s\n", css_path); // Сообщение об успешной загрузке.
        else
            g_warning("Ошибка загрузки CSS: %s", css_path); // Предупреждение об ошибке.

        // Применяем CSS-провайдер ко всему экрану с высоким приоритетом (приложение переопределяет системные стили).
        gtk_style_context_add_provider_for_screen(
            screen,
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );
    } else {
        g_warning("Не удалось определить путь к исполняемому файлу.");
    }
    // Освобождаем ресурс провайдера CSS.
    g_object_unref(provider);
}

// Обработчик нажатия кнопки.
// Копирует текст из поля ввода в метку.
void on_btn_copy_clicked(GtkButton *button, gpointer user_data) {
    AppData *app = (AppData *)user_data; // Приводим gpointer к нашему типу AppData.
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(app->entry_input)); // Получаем текст из поля ввода.
    gtk_label_set_text(GTK_LABEL(app->label_output), text); // Устанавливаем текст в метку.
}

// Главная функция программы.
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); // Инициализация GTK.
    load_css();             // Загрузка CSS-стилей.

    // Создание GtkBuilder и загрузка UI из Glade-файла.
    GtkBuilder *builder = gtk_builder_new_from_file("interface.glade");
    if (!builder) {
        g_critical("Не удалось загрузить Glade-файл."); // Критическая ошибка, если файл не найден/поврежден.
        return 1;
    }

    // Получение ссылок на виджеты по их ID из Glade-файла.
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry_input"));
    GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(builder, "label_output"));
    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "my_button"));

    // Проверка, что все необходимые виджеты были найдены.
    if (!window || !entry || !label || !button) {
        g_critical("Не удалось получить виджеты.");
        g_object_unref(builder);
        return 1;
    }

    // !!! ВАЖНОЕ ДОБАВЛЕНИЕ ДЛЯ РЕШЕНИЯ ПРОБЛЕМ СО СТИЛЯМИ !!!
    // Программное назначение CSS-имён (ID) виджетам.
    // Это гарантирует, что CSS-селекторы по ID (#) всегда найдут эти виджеты,
    // даже если Glade-файл каким-то образом не передал ID корректно при загрузке.
    gtk_widget_set_name(window, "main_window");
    gtk_widget_set_name(entry, "entry_input");
    gtk_widget_set_name(label, "label_output");
    gtk_widget_set_name(button, "my_button");

    // Инициализация структуры AppData для передачи в обработчик сигнала.
    AppData app = { entry, label, button };

    // Подключение сигнала "clicked" кнопки к обработчику on_btn_copy_clicked.
    g_signal_connect(button, "clicked", G_CALLBACK(on_btn_copy_clicked), &app);
    // Подключение сигнала "destroy" главного окна для выхода из приложения при его закрытии.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Отображение всех виджетов в окне.
    gtk_widget_show_all(window);
    // Запуск главного цикла GTK. Приложение ожидает событий.
    gtk_main();

    // Освобождение ресурсов GtkBuilder при завершении работы приложения.
    g_object_unref(builder);
    return 0; // Успешное завершение.
}
```

**Комментарии к `glade_example.c`:**

  - **`load_css()`:** Функция надёжно определяет путь к исполняемому файлу для нахождения `style.css`, что делает приложение более портативным. Использование `GTK_STYLE_PROVIDER_PRIORITY_APPLICATION` гарантирует высокий приоритет ваших стилей.
  - **`AppData`:** Структура `AppData` инкапсулирует указатели на виджеты для удобной передачи в обработчики сигналов.
  - **`gtk_widget_set_name()` (КЛЮЧЕВОЕ РЕШЕНИЕ):** Это важное добавление. Мы обнаружили, что иногда ID, заданные в Glade, могли быть не распознаны GTK-движком для применения CSS. Программная установка ID гарантирует, что виджеты будут иметь правильные CSS ID, к которым могут быть применены стили. Это надёжный способ устранить неочевидные проблемы со стилизацией.
  - **Обработчик сигналов:** Обработчик `on_btn_copy_clicked` и подключение сигнала `clicked` для кнопки `my_button` обеспечивают функциональность копирования текста.

### 2.3. `interface.glade`

Этот XML-файл, созданный с помощью Glade, определяет структуру и первоначальные свойства пользовательского интерфейса. Он является основой для создания виджетов, которые затем будут стилизованы с помощью CSS.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<interface>
  <requires lib="gtk+" version="3.24"/> <object class="GtkWindow" id="main_window"> <property name="default-width">400</property> <property name="default-height">200</property> <property name="title">Mint Style Demo</property> <child>
      <object class="GtkBox" id="main_vbox"> <property name="orientation">vertical</property> <property name="spacing">12</property> <property name="margin-start">16</property> <property name="margin-end">16</property>
        <property name="margin-top">16</property>
        <property name="margin-bottom">16</property>
        <child>
          <object class="GtkEntry" id="entry_input"> <property name="placeholder-text">Введите текст...</property> </object>
        </child>
        <child>
          <object class="GtkButton" id="my_button"> <property name="label">Скопировать</property> <signal name="clicked" handler="on_btn_copy_clicked" swapped="no"/> </object>
        </child>
        <child>
          <object class="GtkLabel" id="label_output"> <property name="label">Здесь появится текст</property> <property name="wrap">True</property> </object>
        </child>
      </object>
    </child>
  </object>
</interface>
```

**Комментарии к `interface.glade`:**

  - **Структура:** Определяет главное окно (`GtkWindow`), вертикальный контейнер (`GtkBox`) и три основных виджета: поле ввода (`GtkEntry`), кнопка (`GtkButton`) и метка (`GtkLabel`).
  - **ID виджетов:** Все ключевые виджеты имеют уникальные `id` (`main_window`, `entry_input`, `my_button`, `label_output`), которые используются в C-коде для получения ссылок на виджеты и в CSS для применения стилей.
  - **Свойства:** Настроены основные свойства, такие как размеры окна, отступы, текст заполнителя и текст меток.
  - **Сигналы:** Кнопка `my_button` имеет сигнал `clicked`, связанный с функцией `on_btn_copy_clicked` в C-коде, обеспечивая интерактивность.

-----

## 3\. Инструкции по сборке и запуску

Чтобы скомпилировать и запустить приложение:

1.  **Сохраните** все три файла (`style.css`, `glade_example.c`, `interface.glade`) в одной директории (например, `~/myprg/28/`).
2.  **Откройте терминал** и перейдите в эту директорию:
    ```bash
    cd ~/myprg/28/
    ```
3.  **Скомпилируйте** C-код с использованием `pkg-config` для автоматического подключения необходимых флагов GTK:
    ```bash
    gcc glade_example.c -o glade_example -rdynamic $(pkg-config --cflags --libs gtk+-3.0)
    ```
4.  **Запустите** скомпилированное приложение:
    ```bash
    ./glade_example
    ```

После запуска вы должны увидеть окно GTK с полностью применёнными стилями из `style.css`, а кнопка и поле ввода будут функциональны.

```
```