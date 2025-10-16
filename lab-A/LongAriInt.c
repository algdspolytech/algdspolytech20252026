#include "LongArfInt.h"

int check_validness(long_int *number) {
    if (number->tail != NULL && number->head == NULL)
        return -1;
    if (number->head != NULL && number->tail == NULL)
        return -1;
    if (number->head == NULL && number->tail == NULL)
        return -1;
    digit *tmp = number->head;
    digit *tmp2 = number->head->next;
    while (tmp2 != NULL) {
        if (tmp2->exp + 1 != tmp->exp)
            return -1;
        if (tmp->exp < 0)
            return -1;
        tmp2 = tmp2->next;
        tmp = tmp->next;
    }
    return 1;
}

digit *new_digit(short content, short exp) {
    digit *tmp = (digit *) malloc(sizeof(digit));
    if (tmp == NULL) {
        printf("\nMemory allocation for digit failed\n");
        free(tmp);
        return NULL;
    }
    if (content > 10 || content < 0) {
        printf("\nInvalid digit");
        free(tmp);
        return NULL;
    }

    if (exp < 0) {
        printf("\nInvalid exponent");
        free(tmp);
        return NULL;
    }
    tmp->content = content;
    tmp->exp = exp;
    tmp->next = NULL;
    tmp->prev = NULL;
    return tmp;
}

void init_long_int(long_int *number) {
    number->head = NULL;
    number->tail = NULL;
    number->sign = 1;
}

void clear_long_int(long_int *number) {
    digit *current = number->head;
    while (current != NULL) {
        digit *next = current->next;
        free(current);
        current = next;
    }
    number->head = NULL;
    number->tail = NULL;
    number->sign = 1;
    number = NULL;
}

void *app_end_digit(long_int *number, short content, short exp) {
    digit *tmp = new_digit(content, exp);
    if (tmp == NULL) {
        printf("\n Error in creation of digit\n");
        return NULL;
    }
    if (number->head == NULL && number->tail == NULL) {
        number->head = tmp;
        number->tail = tmp;
    } else if (number->head != NULL && number->tail != NULL) {
        if (number->tail->exp > exp) {
            number->tail->next = tmp;
            tmp->prev = number->tail;
            number->tail = tmp;
        } else {
            printf("\n digit can't be inputed in end\n");
            free(tmp);
            return NULL;
        }
    } else {
        printf("\n long_int currupted\n");
        clear_long_int(number);
        free(tmp);
        return NULL;
    }
}

long_int read_long_int() {
    long_int number;
    init_long_int(&number);
    int exponent = SHRT_MAX;
    char ch = getchar();

    if (ch == '-')
        number.sign = -1;
    else if (ch == '+')
        number.sign = 1;
    else if (ch >= '0' && ch <= '9')
        app_end_digit(&number, ch - '0', exponent--);
    else {
        printf("\nInvalid character\n");
        clear_long_int(&number);
        return number;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch >= '0' && ch <= '9') {
            app_end_digit(&number, ch - '0', exponent--);
        } else {
            printf("\nInvalid character\n");
            clear_long_int(&number);
            return number;
        }

        if (exponent == -1) {
            printf("\nNumber is too long\n");
            clear_long_int(&number);
            return number;
        }
    }

    int shift = SHRT_MAX - exponent;

    digit *tmp = number.head;
    while (tmp != NULL) {
        tmp->exp = --shift;
        tmp = tmp->next;
    }
    return number;
}

void *add_strt_digit(long_int *number, short content, short exp) {
    digit *tmp = new_digit(content, exp);
    if (tmp == NULL) {
        printf("\n Error in creation of digit\n");
        return NULL;
    }
    if (number->head == NULL && number->tail == NULL) {
        number->head = tmp;
        number->tail = tmp;
    } else if (number->head != NULL && number->tail != NULL) {
        if (number->head->exp < exp) {
            number->head->prev = tmp;
            tmp->next = number->head;
            number->head = tmp;
        } else {
            printf("\n digit can't be inputed in head\n");
            free(tmp);
            return NULL;
        }
    }
        else {
            printf("\n long_int currupted\n");
            clear_long_int(number);
            free(tmp);
            return NULL;
        }
    }



long_int copy_long_int(long_int *orig) {
    if ((orig->head != NULL && orig->tail != NULL)) {
        long_int copy;
        init_long_int(&copy);
        copy.sign = orig->sign;

        digit *current = orig->head;
        while (current != NULL) {
            app_end_digit(&copy, current->content, current->exp);
            current = current->next;
        }

        return copy;
    }
    if (orig->head == NULL && orig->tail == NULL)
        return *orig;
    else {
        printf("\n Error in creation of long_int\n");
        clear_long_int(orig);
        return *orig;
    }
}


long_int summ_long_int(long_int *number_1, long_int *number_2) {
    digit *tmp_1, *tmp_2, *tmp_3;
    short sign = 1;
    volatile short raw_digit;
    long_int number_3;
    init_long_int(&number_3);

    if (check_validness(number_1) != 1) {
        printf("\nInvalid first term of sum\n");
        return number_3;
    }

    if (check_validness(number_2) != 1) {
        printf("\nInvalid second term of sum\n");
        return number_3;
    }

    int max_exp;

    if (number_1->sign == number_2->sign) {
        if (number_1->head->exp > number_2->head->exp) {
            max_exp = number_1->head->exp;
            tmp_1 = number_1->tail;
            tmp_2 = number_2->tail;
        } else {
            max_exp = number_2->head->exp;
            tmp_1 = number_2->tail;
            tmp_2 = number_1->tail;
        }
        number_3.sign = number_1->sign;
    } else {
        if (number_1->head->exp > number_2->head->exp || (number_1->head->exp == number_2->head->exp && number_1->head->content > number_2->head->content) ) {
            max_exp = number_1->head->exp;
            tmp_1 = number_1->tail;
            tmp_2 = number_2->tail;
            number_3.sign = number_1->sign;
        }
        else {
            max_exp = number_2->head->exp;
            tmp_1 = number_2->tail;
            tmp_2 = number_1->tail;
            number_3.sign = number_2->sign;
        }
        sign = -1;
    }

    if (max_exp > SHRT_MAX) {
        printf("Product of numbers is too long\n");
        return number_3;
    }


    short digit_overflow = 0;
    digit *placeholder = new_digit(0, 0);

    for (int iter = 0; iter < max_exp + 1; iter++) {
        raw_digit = tmp_1->content + sign * tmp_2->content + digit_overflow;
        if (raw_digit > 0 || raw_digit == 0) {
            add_strt_digit(&number_3, raw_digit % 10,
                           tmp_1->exp);
            digit_overflow = raw_digit / 10;
        } else {
            add_strt_digit(&number_3, (10 + tmp_1->content + sign * tmp_2->content + digit_overflow) % 10,
                           tmp_1->exp);
            digit_overflow = -1;
        }
        if (tmp_2->prev == NULL)
            tmp_2 = placeholder;
        else
            tmp_2 = tmp_2->prev;

        tmp_1 = tmp_1->prev;
    }


    while (number_3.head->content == 0 && number_3.head->exp != 0) {
        tmp_3 = number_3.head;
        number_3.head = tmp_3->next;
        number_3.head->prev = NULL;
        max_exp--;
    }
    if (digit_overflow != 0) {
        add_strt_digit(&number_3, digit_overflow, max_exp + 1);
    }

    if (number_3.head->exp == 0 && number_3.head->content == 0)
        number_3.sign = 1;

    free(placeholder);
    return number_3;
}


long_int mult_long_int(long_int *number_1, long_int *number_2) {
    long_int number_3;
    init_long_int(&number_3);

    if (check_validness(number_1) != 1) {
        printf("\nInvalid first term of multiplication\n");
        return number_3;
    }

    if (check_validness(number_2) != 1) {
        printf("\nInvalid second term of multiplication\n");
        return number_3;
    }

    int max_exp = number_1->head->exp + number_2->head->exp + 1;
    if (max_exp > SHRT_MAX) {
        printf("Product of numbers is too long\n");
        return number_3;
    }

    number_3.sign = number_1->sign * number_2->sign;

    for (int i = max_exp; i + 1 > 0; i--) {
        app_end_digit(&number_3, 0, i);
    }

    digit *tmp_1 = number_1->tail;

    for (int i = 0; i <= number_1->head->exp; i++) {
        int digit_1 = tmp_1->content;
        int digit_overflow = 0;

        digit *tmp_2 = number_2->tail;
        digit *tmp_3 = number_3.tail;

        for (int shift = 0; shift < i; shift++) {
            tmp_3 = tmp_3->prev;
        }

        for (int j = 0; j <= number_2->head->exp; j++) {
            if (tmp_3 == NULL) break;

            int digit_2 = tmp_2->content;
            int product = digit_1 * digit_2 + digit_overflow + tmp_3->content;

            tmp_3->content = product % 10;
            digit_overflow = product / 10;

            tmp_2 = tmp_2->prev;
            tmp_3 = tmp_3->prev;
        }

        while (digit_overflow > 0 && tmp_3 != NULL) {
            int sum = tmp_3->content + digit_overflow;
            tmp_3->content = sum % 10;
            digit_overflow = sum / 10;
            tmp_3 = tmp_3->prev;
        }

        if (digit_overflow > 0) {
            add_strt_digit(&number_3, digit_overflow, max_exp + 1);
            max_exp++;
        }

        tmp_1 = tmp_1->prev;
    }


    while (number_3.head->content == 0 && number_3.head->exp > 0) {
        digit *tmp = number_3.head;
        number_3.head = tmp->next;
        number_3.head->prev = NULL;
        free(tmp);
    }

    if (number_3.head->exp == 0 && number_3.head->content == 0) {
        number_3.sign = 1;
    }

    return number_3;
}


long_int power_long_int(long_int *base, int exponent) {
    if (check_validness(base) != 1) {
        printf("\nError in creation of base \n");
        clear_long_int(base);
        return *base;
    }
    long_int result;
    init_long_int(&result);

    if (exponent < 0) {
        printf("\nNegative exponent unsupported");
        return result;
    }


    app_end_digit(&result, 1, 0);
    result.sign = 1;

    if (exponent == 0) {
        return result;
    }

    if (exponent == 1) {
        result = copy_long_int(base);
        return result;
    }
    int sign = 1;
    if (base->sign == -1 && (exponent % 2 == 1))
        sign = -1;



    long_int temp_base = copy_long_int(base);

    while (exponent > 0) {
        if (exponent % 2 == 0) {
            temp_base = mult_long_int(&temp_base, &temp_base);
            exponent /= 2;
        } else {
            result = mult_long_int(&result, &temp_base);
            exponent--;
        }
    }
    clear_long_int(&temp_base);
    result.sign = sign;
    return result;
}

void *print_long_int(long_int *number) {
    if (check_validness(number) != 1) {
        printf("\nError in creation of digit \n");
        return NULL;
    }


    if (number->sign == -1)
        printf("-");

    digit *tmp = number->head;
    while (tmp != NULL) {
        printf("%d", tmp->content);
        tmp = tmp->next;
    }
    return;
}
