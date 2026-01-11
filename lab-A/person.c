#define _CRT_SECURE_NO_WARNINGS
#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


// Сравнение двух дат
int compare_dates(const Date* d1, const Date* d2) {
    if (d1->year != d2->year) {
        return d1->year - d2->year;
    }
    if (d1->month != d2->month) {
        return d1->month - d2->month;
    }
    return d1->day - d2->day;
}

// Парсинг даты из строки формата DD.MM.YYYY
int parse_date(const char* date_str, Date* date) {
    int day, month, year;
    char separator1, separator2;

    if (sscanf(date_str, "%2d%c%2d%c%4d",
        &day, &separator1, &month, &separator2, &year) != 5) {
        return 0;
    }

    if (separator1 != '.' || separator2 != '.') {
        return 0;
    }

    // Проверка корректности даты
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
        return 0;
    }

    // Проверка дней в месяце (упрощенная)
    int days_in_month[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day > days_in_month[month - 1]) {
        return 0;
    }

    date->day = day;
    date->month = month;
    date->year = year;
    return 1;
}

// Форматирование даты в строку
void format_date(const Date* date, char* buffer) {
    sprintf(buffer, "%02d.%02d.%04d", date->day, date->month, date->year);
}

// Создание нового элемента списка
Person* create_person(const char* last_name, const char* first_name,
    const char* middle_name, const Date* birth_date) {
    Person* new_person = (Person*)malloc(sizeof(Person));
    if (!new_person) {
        return NULL;
    }

    strncpy(new_person->last_name, last_name, MAX_NAME_LEN - 1);
    new_person->last_name[MAX_NAME_LEN - 1] = '\0';

    strncpy(new_person->first_name, first_name, MAX_NAME_LEN - 1);
    new_person->first_name[MAX_NAME_LEN - 1] = '\0';

    strncpy(new_person->middle_name, middle_name, MAX_NAME_LEN - 1);
    new_person->middle_name[MAX_NAME_LEN - 1] = '\0';

    new_person->birth_date = *birth_date;
    new_person->next = NULL;

    return new_person;
}

// Вставка элемента в отсортированный список
Person* insert_sorted(Person* head, Person* new_person) {
    // Если список пустой или новый элемент должен быть первым
    if (head == NULL || compare_dates(&new_person->birth_date, &head->birth_date) < 0) {
        new_person->next = head;
        return new_person;
    }

    // Поиск места для вставки
    Person* current = head;
    Person* prev = NULL;

    while (current != NULL && compare_dates(&new_person->birth_date, &current->birth_date) >= 0) {
        prev = current;
        current = current->next;
    }

    // Вставка между prev и current
    if (prev != NULL) {
        prev->next = new_person;
    }
    new_person->next = current;

    return head;
}

// Загрузка данных из файла в отсортированный список
Person* load_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    Person* head = NULL;
    char line[MAX_LINE_LEN];

    while (fgets(line, sizeof(line), file)) {
        // Удаление символа новой строки
        line[strcspn(line, "\n")] = '\0';

        char last_name[MAX_NAME_LEN];
        char first_name[MAX_NAME_LEN];
        char middle_name[MAX_NAME_LEN];
        char date_str[MAX_DATE_LEN];
        Date birth_date;

        // Парсинг строки
        if (sscanf(line, "%49s %49s %49s %10s",
            last_name, first_name, middle_name, date_str) != 4) {
            continue; // Пропустить некорректные строки
        }

        // Парсинг даты
        if (!parse_date(date_str, &birth_date)) {
            continue; // Пропустить некорректные даты
        }

        // Создание и вставка элемента
        Person* new_person = create_person(last_name, first_name, middle_name, &birth_date);
        if (new_person) {
            head = insert_sorted(head, new_person);
        }
    }

    fclose(file);
    return head;
}

// Вывод списка на экран
void print_list(const Person* head) {
    printf("\nСписок людей (отсортирован по дате рождения):\n");
    printf("%-20s %-12s\n", "Фамилия", "Дата рождения");
    printf("----------------------------------------\n");

    const Person* current = head;
    char date_str[MAX_DATE_LEN];

    while (current) {
        format_date(&current->birth_date, date_str);
        printf("%-20s %-12s\n", current->last_name, date_str);
        current = current->next;
    }
}

// Поиск первого человека с заданной датой рождения
Person* find_by_birth_date(const Person* head, const Date* target_date) {
    const Person* current = head;

    while (current) {
        if (compare_dates(&current->birth_date, target_date) == 0) {
            return (Person*)current;
        }
        current = current->next;
    }

    return NULL;
}

// Подсчет количества людей с заданной датой рождения
int count_by_birth_date(const Person* head, const Date* target_date) {
    const Person* current = head;
    int count = 0;

    while (current) {
        if (compare_dates(&current->birth_date, target_date) == 0) {
            count++;
        }
        current = current->next;
    }

    return count;
}

// Освобождение памяти списка
void free_list(Person* head) {
    Person* current = head;

    while (current) {
        Person* next = current->next;
        free(current);
        current = next;
    }
}

// Основная программа
void run_main_program() {
    setlocale(LC_ALL, "RUSSIAN");

    char filename[100];
    printf("Введите имя файла с данными: ");
    if (scanf("%99s", filename) != 1) {
        printf("Ошибка ввода имени файла\n");
        return;
    }

    // Загрузка данных из файла
    Person* person_list = load_from_file(filename);
    if (!person_list) {
        printf("Ошибка: не удалось загрузить файл или файл пустой.\n");
        return;
    }

    // Вывод отсортированного списка
    print_list(person_list);

    // Ввод даты для поиска
    char search_date_str[MAX_DATE_LEN];
    Date search_date;

    printf("\nВведите дату рождения для поиска (в формате DD.MM.YYYY): ");
    if (scanf("%10s", search_date_str) != 1) {
        printf("Ошибка ввода даты\n");
        free_list(person_list);
        return;
    }

    if (!parse_date(search_date_str, &search_date)) {
        printf("Ошибка: некорректный формат даты.\n");
        free_list(person_list);
        return;
    }

    // Поиск и вывод результатов
    int count = count_by_birth_date(person_list, &search_date);

    if (count == 0) {
        printf("\nВ списке нет людей, родившихся %s.\n", search_date_str);
    }
    else {
        printf("\nНайдено %d человек(а), родившихся %s:\n", count, search_date_str);
        printf("%-20s %-15s %-15s %-12s\n",
            "Фамилия", "Имя", "Отчество", "Дата рождения");
        printf("------------------------------------------------------------\n");

        Person* current = person_list;
        char date_str[MAX_DATE_LEN];

        while (current) {
            if (compare_dates(&current->birth_date, &search_date) == 0) {
                format_date(&current->birth_date, date_str);
                printf("%-20s %-15s %-15s %-12s\n",
                    current->last_name, current->first_name,
                    current->middle_name, date_str);
            }
            current = current->next;
        }
    }

    // Освобождение памяти
    free_list(person_list);
}