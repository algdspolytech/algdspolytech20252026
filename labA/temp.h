#ifndef TEMP_H
#define TEMP_H

typedef struct {
    int year;
    int month;
    int day;
} WeatherDate;

typedef struct WeatherNode {
    WeatherDate date;
    double temp_value;
    struct WeatherNode* next;
    struct WeatherNode* prev;
} WeatherNode;

typedef struct {
    WeatherNode* head;
    WeatherNode* tail;
    int count;
} WeatherJournal;

#endif