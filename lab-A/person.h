#ifndef PERSON_H
#define PERSON_H

#include <time.h>

#define MAX_NAME_LEN 50
#define MAX_DATE_LEN 11  // DD.MM.YYYY + нулевой символ
#define MAX_LINE_LEN 200

// Структура для хранения даты рождения
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Структура для хранения информации о человеке
typedef struct Person {
    char last_name[MAX_NAME_LEN];
    char first_name[MAX_NAME_LEN];
    char middle_name[MAX_NAME_LEN];
    Date birth_date;
    struct Person* next;
} Person;

// Прототипы функций
int compare_dates(const Date* d1, const Date* d2);
int parse_date(const char* date_str, Date* date);
void format_date(const Date* date, char* buffer);
Person* create_person(const char* last_name, const char* first_name,
    const char* middle_name, const Date* birth_date);
Person* insert_sorted(Person* head, Person* new_person);
Person* load_from_file(const char* filename);
void print_list(const Person* head);
Person* find_by_birth_date(const Person* head, const Date* target_date);
int count_by_birth_date(const Person* head, const Date* target_date);
void free_list(Person* head);

// Функция основной программы
void run_main_program();

#endif // PERSON_H