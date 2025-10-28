#include "weather_journal.h"
#include "data_parser.h"
#include <stdio.h>
#include <windows.h>

void setup_console() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

void show_welcome() {
    printf("=== Анализатор погодных данных ===\n");
    printf("Сортировка и анализ температурных данных\n\n");
}

void display_negative_temperatures(const WeatherJournal* journal) {
    if (!journal || journal->count == 0) {
        printf("Нет данных для отображения.\n");
        return;
    }

    printf("Дни с отрицательной температурой:\n");
    printf("---------------------------------\n");

    WeatherNode* current = journal->head;
    int found_negative = 0;

    while (current) {
        if (current->temp_value < 0) {
            printf("%04d-%02d-%02d: %6.1f°C\n",
                current->date.year, current->date.month, current->date.day,
                current->temp_value);
            found_negative = 1;
        }
        current = current->next;
    }

    if (!found_negative) {
        printf("Дни с отрицательной температурой отсутствуют.\n");
    }
    printf("\n");
}

int main() {
    setup_console();
    show_welcome();

    WeatherJournal* journal = WJ_create();
    if (!journal) {
        printf("Ошибка инициализации журнала данных.\n");
        return 1;
    }

    if (DP_read_data_file(journal, "weather_data.txt") != 0) {
        printf("Ошибка загрузки файла weather_data.txt\n");
        WJ_destroy(journal);
        return 1;
    }

    printf("Успешно загружено записей: %d\n", journal->count);
    printf("Из них с отрицательной температурой: %d\n\n", WJ_count_negative_days(journal));

    display_negative_temperatures(journal);

    double search_temp;
    printf("Введите температуру для поиска: ");
    if (scanf("%lf", &search_temp) == 1) {
        WeatherNode* found = WJ_find_temperature(journal, search_temp);
        if (found) {
            printf("Найден день: %04d-%02d-%02d с температурой %.1f°C\n",
                found->date.year, found->date.month, found->date.day,
                found->temp_value);
        }
        else {
            printf("Дни с температурой %.1f°C не обнаружены.\n", search_temp);
        }
    }
    else {
        printf("Ошибка ввода температуры.\n");
    }

    WJ_destroy(journal);
    return 0;
}