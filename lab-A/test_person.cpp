#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>

extern "C" {
#include "person.h"
}

// Вспомогательная функция для создания тестового файла
void create_test_file(const char* filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

// Тест 1: Сравнение дат - разные годы
TEST(PersonTest, CompareDatesDifferentYears_no1) {
    Date d1 = { 15, 5, 1990 };
    Date d2 = { 15, 5, 2000 };
    EXPECT_LT(compare_dates(&d1, &d2), 0);
    EXPECT_GT(compare_dates(&d2, &d1), 0);
}

// Тест 2: Сравнение дат - одинаковые даты
TEST(PersonTest, CompareDatesEqual_no2) {
    Date d1 = { 15, 5, 1990 };
    Date d2 = { 15, 5, 1990 };
    EXPECT_EQ(compare_dates(&d1, &d2), 0);
}

// Тест 3: Парсинг корректной даты
TEST(PersonTest, ParseValidDate_no3) {
    Date date;
    EXPECT_TRUE(parse_date("15.05.2000", &date));
    EXPECT_EQ(date.day, 15);
    EXPECT_EQ(date.month, 5);
    EXPECT_EQ(date.year, 2000);
}

// Тест 4: Парсинг некорректной даты
TEST(PersonTest, ParseInvalidDate_no4) {
    Date date;
    EXPECT_FALSE(parse_date("32.01.2000", &date));
    EXPECT_FALSE(parse_date("15.13.2000", &date));
    EXPECT_FALSE(parse_date("15-05-2000", &date));
}

// Тест 5: Создание и вставка в пустой список
TEST(PersonTest, InsertToEmptyList_no5) {
    Person* list = NULL;
    Date date = { 15, 5, 1990 };

    Person* person = create_person("Иванов", "Иван", "Иванович", &date);
    ASSERT_NE(person, nullptr);

    list = insert_sorted(list, person);
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(list, person);
    EXPECT_EQ(list->next, nullptr);

    free_list(list);
}

// Тест 6: Вставка в начало списка (новая дата меньше первой)
TEST(PersonTest, InsertAtBeginning_no6) {
    Person* list = NULL;
    Date date1 = { 15, 5, 1990 };
    Date date2 = { 10, 5, 1985 };

    Person* person1 = create_person("Иванов", "Иван", "Иванович", &date1);
    Person* person2 = create_person("Петров", "Петр", "Петрович", &date2);

    list = insert_sorted(list, person1);
    list = insert_sorted(list, person2);

    EXPECT_EQ(list, person2);
    EXPECT_EQ(list->next, person1);

    free_list(list);
}

// Тест 7: Вставка в конец списка (новая дата больше последней)
TEST(PersonTest, InsertAtEnd_no7) {
    Person* list = NULL;
    Date date1 = { 15, 5, 1990 };
    Date date2 = { 10, 5, 1995 };

    Person* person1 = create_person("Иванов", "Иван", "Иванович", &date1);
    Person* person2 = create_person("Петров", "Петр", "Петрович", &date2);

    list = insert_sorted(list, person1);
    list = insert_sorted(list, person2);

    EXPECT_EQ(list, person1);
    EXPECT_EQ(list->next, person2);

    free_list(list);
}

// Тест 8: Загрузка из файла - корректный файл
TEST(PersonTest, LoadFromValidFile_no8) {
    const char* test_file = "test_data.txt";
    create_test_file(test_file,
        "Иванов Иван Иванович 15.05.1990\n"
        "Петров Петр Петрович 10.05.1985\n"
        "Сидоров Сидор Сидорович 20.08.1993\n");

    Person* list = load_from_file(test_file);
    ASSERT_NE(list, nullptr);

    EXPECT_STREQ(list->last_name, "Петров");
    EXPECT_STREQ(list->next->last_name, "Иванов");
    EXPECT_STREQ(list->next->next->last_name, "Сидоров");

    free_list(list);
    remove(test_file);
}

// Тест 9: Загрузка из файла - пустой файл
TEST(PersonTest, LoadFromEmptyFile_no9) {
    const char* test_file = "empty.txt";
    create_test_file(test_file, "");

    Person* list = load_from_file(test_file);
    EXPECT_EQ(list, nullptr);

    remove(test_file);
}

// Тест 10: Загрузка из файла - несуществующий файл
TEST(PersonTest, LoadFromNonExistentFile_no10) {
    Person* list = load_from_file("non_existent_file.txt");
    EXPECT_EQ(list, nullptr);
}

// Тест 11: Поиск по дате рождения - найдено
TEST(PersonTest, FindByBirthDateFound_no11) {
    Person* list = NULL;
    Date date1 = { 15, 5, 1990 };
    Date date2 = { 10, 5, 1990 };
    Date search_date = { 15, 5, 1990 };

    Person* person1 = create_person("Иванов", "Иван", "Иванович", &date1);
    Person* person2 = create_person("Петров", "Петр", "Петрович", &date2);

    list = insert_sorted(list, person1);
    list = insert_sorted(list, person2);

    Person* found = find_by_birth_date(list, &search_date);
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(found->last_name, "Иванов");

    free_list(list);
}

// Тест 12: Поиск по дате рождения - не найдено
TEST(PersonTest, FindByBirthDateNotFound_no12) {
    Person* list = NULL;
    Date date1 = { 15, 5, 1990 };
    Date search_date = { 20, 5, 1990 };

    Person* person1 = create_person("Иванов", "Иван", "Иванович", &date1);
    list = insert_sorted(list, person1);

    Person* found = find_by_birth_date(list, &search_date);
    EXPECT_EQ(found, nullptr);

    free_list(list);
}

// Тест 13: Подсчет людей с заданной датой рождения
TEST(PersonTest, CountByBirthDate_no13) {
    Person* list = NULL;
    Date date1 = { 15, 5, 1990 };
    Date date2 = { 15, 5, 1990 };
    Date date3 = { 10, 5, 1990 };
    Date search_date = { 15, 5, 1990 };

    Person* person1 = create_person("Иванов", "Иван", "Иванович", &date1);
    Person* person2 = create_person("Петров", "Петр", "Петрович", &date2);
    Person* person3 = create_person("Сидоров", "Сидор", "Сидорович", &date3);

    list = insert_sorted(list, person1);
    list = insert_sorted(list, person2);
    list = insert_sorted(list, person3);

    int count = count_by_birth_date(list, &search_date);
    EXPECT_EQ(count, 2);

    free_list(list);
}

// Тест 14: Форматирование даты
TEST(PersonTest, FormatDate_no14) {
    Date date = { 5, 12, 2000 };
    char buffer[MAX_DATE_LEN];

    format_date(&date, buffer);
    EXPECT_STREQ(buffer, "05.12.2000");
}

// Тест 15: Освобождение памяти пустого списка
TEST(PersonTest, FreeEmptyList_no15) {
    Person* list = NULL;
    free_list(list); // Не должно падать
    SUCCEED();
}

// Тестовая точка входа для Google Test
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Если передан аргумент "--run-main", запускаем основную программу
    if (argc > 1 && strcmp(argv[1], "--run-main") == 0) {
        run_main_program();
        return 0;
    }

    return RUN_ALL_TESTS();
}