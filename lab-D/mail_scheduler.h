#ifndef MAIL_SCHEDULER_H
#define MAIL_SCHEDULER_H

#define MAX_TELEGRAMS 1000

typedef struct {
    int l; 
    int d; 
    int w; 
    int id; 
} Telegram;

// Функции

int read_telegrams_from_file(const char* filename, Telegram* telegrams, int* K);
int calculate_optimal_schedule(Telegram* telegrams, int num_telegrams, int K, int* sorted_order);
int write_result_to_file(int* sorted_order, int schedule_size, const char* filename);

#endif // MAIL_SCHEDULER_H