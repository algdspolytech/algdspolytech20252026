#include "weather_journal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN_TEMP -100.0
#define MAX_TEMP 100.0

WeatherJournal* WJ_create() {
    WeatherJournal* journal = (WeatherJournal*)malloc(sizeof(WeatherJournal));
    if (journal) {
        journal->head = NULL;
        journal->tail = NULL;
        journal->count = 0;
    }
    return journal;
}

void WJ_destroy(WeatherJournal* journal) {
    if (!journal) return;

    WeatherNode* current = journal->head;
    while (current) {
        WeatherNode* next = current->next;
        free(current);
        current = next;
    }
    free(journal);
}

int WJ_validate_date(const WeatherDate* date) {
    if (date->year < 1900 || date->year > 2100) return 0;
    if (date->month < 1 || date->month > 12) return 0;
    if (date->day < 1 || date->day > 31) return 0;

    int days_in_month[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
    return date->day <= days_in_month[date->month - 1];
}

int WJ_check_temperature(double temp) {
    return temp >= MIN_TEMP && temp <= MAX_TEMP;
}

int WJ_compare_nodes(const WeatherNode* a, const WeatherNode* b) {
    if (a->temp_value != b->temp_value) {
        return (a->temp_value > b->temp_value) ? 1 : -1;
    }

    if (a->date.year != b->date.year) return a->date.year - b->date.year;
    if (a->date.month != b->date.month) return a->date.month - b->date.month;
    return a->date.day - b->date.day;
}

int WJ_insert_sorted(WeatherJournal* journal, WeatherDate date, double temp) {
    if (!journal || !WJ_validate_date(&date) || !WJ_check_temperature(temp)) {
        return 0;
    }

    WeatherNode* new_node = (WeatherNode*)malloc(sizeof(WeatherNode));
    if (!new_node) return 0;

    new_node->date = date;
    new_node->temp_value = temp;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (journal->count == 0) {
        journal->head = new_node;
        journal->tail = new_node;
        journal->count = 1;
        return 1;
    }

    WeatherNode* current = journal->head;
    WeatherNode* previous = NULL;

    WeatherNode temp_node = { date, temp, NULL, NULL };

    while (current && WJ_compare_nodes(&temp_node, current) > 0) {
        previous = current;
        current = current->next;
    }

    if (!previous) {
        new_node->next = journal->head;
        journal->head->prev = new_node;
        journal->head = new_node;
    }
    else if (!current) {
        previous->next = new_node;
        new_node->prev = previous;
        journal->tail = new_node;
    }
    else {
        previous->next = new_node;
        new_node->prev = previous;
        new_node->next = current;
        current->prev = new_node;
    }

    journal->count++;
    return 1;
}

WeatherNode* WJ_find_temperature(const WeatherJournal* journal, double temp) {
    if (!journal) return NULL;

    WeatherNode* current = journal->head;
    while (current) {
        if (current->temp_value == temp) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void WJ_show_negative_temps(const WeatherJournal* journal) {
    if (!journal) return;

    WeatherNode* current = journal->head;
    while (current) {
        if (current->temp_value < 0) {
            printf("%04d-%02d-%02d: %6.1f°C\n",
                current->date.year, current->date.month, current->date.day,
                current->temp_value);
        }
        current = current->next;
    }
}

int WJ_count_negative_days(const WeatherJournal* journal) {
    if (!journal) return 0;

    int negative_count = 0;
    WeatherNode* current = journal->head;
    while (current) {
        if (current->temp_value < 0) {
            negative_count++;
        }
        current = current->next;
    }
    return negative_count;
}