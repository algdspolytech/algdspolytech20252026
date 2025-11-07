#define _CRT_SECURE_NO_WARNINGS
#include "polynom.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// управ памятью и доп функции
Monomial* create_monomial(coefficient_t coeff, degree_t deg) {
  Monomial* new_monomial = (Monomial*)malloc(sizeof(Monomial));
  if (new_monomial == NULL) {
    perror("Error: Memory allocation failed for Monomial");
    exit(EXIT_FAILURE);
  }
  new_monomial->coefficient = coeff;
  new_monomial->degree = deg;
  new_monomial->next = NULL;
  return new_monomial;
}

Polynomial* create_polynomial() {
  Polynomial* new_poly = (Polynomial*)malloc(sizeof(Polynomial));
  if (new_poly == NULL) {
    perror("Error: Memory allocation failed for Polynomial");
    exit(EXIT_FAILURE);
  }
  new_poly->head = NULL;
  return new_poly;
}

void free_polynomial(Polynomial* poly) {
  if (poly == NULL) return;
  Monomial* current = poly->head;
  Monomial* next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  free(poly);
}

// добавка монома, если степень уже есть, сложение коэф
void add_monomial_to_poly(Polynomial* poly, coefficient_t coeff, degree_t deg) {
  if (coeff == 0) return;

  Monomial* current = poly->head;

  // поиск монома с той же степенью для сложения
  while (current != NULL) {
    if (current->degree == deg) {
      current->coefficient += coeff;

      // если рез сложения равен 0, срочно нормализуем, чтоб удалить этот моном
      if (current->coefficient == 0) {
        normalize_polynomial(poly);
      }
      return;
    }
    current = current->next;
  }

  // если не найден, добавка нового монома в начало
  Monomial* new_monomial = create_monomial(coeff, deg);
  new_monomial->next = poly->head;
  poly->head = new_monomial;

  normalize_polynomial(poly);
}

// удаление членлв, коэф которых =0
void normalize_polynomial(Polynomial* poly) {
  if (poly == NULL || poly->head == NULL) return;

  Monomial* current = poly->head;
  Monomial* prev = NULL;

  while (current != NULL) {
    // удаление члена, если его коэф стал =0
    if (current->coefficient == 0) {
      if (prev == NULL) {
        // удаление головы
        poly->head = current->next;
        free(current);
        current = poly->head;
      } else {
        // удаление не-головы
        prev->next = current->next;
        free(current);
        current = prev->next;
      }
      continue;
    }
    prev = current;
    current = current->next;
  }
}

// сортировка по степеням от мл к ст
void sort_polynomial(Polynomial* poly) {
  if (poly == NULL || poly->head == NULL) return;

  Monomial *i, *j;

  // сортировка выбором по степени
  for (i = poly->head; i != NULL; i = i->next) {
    for (j = i->next; j != NULL; j = j->next) {
      if (i->degree > j->degree) {
        // обмен данными узлов (коэф и степени)
        coefficient_t temp_coeff = i->coefficient;
        degree_t temp_deg = i->degree;

        i->coefficient = j->coefficient;
        i->degree = j->degree;

        j->coefficient = temp_coeff;
        j->degree = temp_deg;
      }
    }
  }
}

// копия полинома
Polynomial* copy_polynomial(const Polynomial* source) {
  if (source == NULL) {
    return NULL;
  }
  Polynomial* copy = create_polynomial();
  Monomial* current = source->head;
  Monomial* last = NULL;

  while (current != NULL) {
    Monomial* new_monom =
        create_monomial(current->coefficient, current->degree);

    if (copy->head == NULL) {
      copy->head = new_monom;
      last = new_monom;
    } else {
      last->next = new_monom;
      last = new_monom;
    }
    current = current->next;
  }

  return copy;
}

// парсинг

// доп функ парсинга числа
int extract_number(const char** s) {
  int num = 0;
  int sign = 1;
  int is_num_present = 0;

  // 1. опр знака
  if (**s == '-') {
    sign = -1;
    (*s)++;
  } else if (**s == '+') {
    sign = 1;
    (*s)++;
  }

  // 2. чтение числа
  if (isdigit(**s)) {
    is_num_present = 1;
    while (isdigit(**s)) {
      num = num * 10 + (**s - '0');
      (*s)++;
    }
  }

  // 3. возврат реза
  if (is_num_present) {
    return num * sign;
  }

  // если числа не было, значит был +/-1
  return sign;
}

Polynomial* parse_polynomial(const char* str) {
  Polynomial* poly = create_polynomial();
  const char* s = str;

  if (str == NULL || *str == '\0') {
    return poly;
  }

  while (*s != '\0') {
    coefficient_t coeff = 0;
    degree_t deg = 0;
    int parsed_coeff = 0;
    int has_sign = 0;

    while (isspace(*s)) s++;
    if (*s == '\0') break;

    // 1. опр коэф M

    if (*s == '-' || *s == '+') {
      has_sign = 1;
    }

    // если моном начинается со знака и за ним идет число: M*x/M
    if (has_sign && isdigit(*(s + 1))) {
      coeff = extract_number(&s);
      parsed_coeff = 1;
    }
    // если моном начинается со знака и за ним идет 'x' (+/-x)
    else if (has_sign && *(s + 1) == 'x') {
      coeff = extract_number(&s);
      parsed_coeff = 1;
    }
    // если моном начинается с числа (M*x/M, только для 1го члена без знака)
    else if (isdigit(*s)) {
      coeff = extract_number(&s);
      parsed_coeff = 1;
    }
    // если моном начинается с 'x' (x/x^k)
    else if (*s == 'x') {
      coeff = 1;
      parsed_coeff = 1;
    } else {
      s++;  // переход к следующему, при не распозновании символа
      continue;
    }

    // 2. опр степени k

    if (*s == '*') {
      s++;  // пропуск *
    }

    if (*s == 'x') {
      s++;
      deg = 1;  // инициализация x^1
      if (*s == '^') {
        s++;
        deg = 0;  // сброс на 0 перед чтением степени
        while (isdigit(*s)) {
          deg = deg * 10 + (*s - '0');
          s++;
        }
      }
    } else {
      // моном const
      deg = 0;
    }

    // 3. добавка монома
    add_monomial_to_poly(poly, coeff, deg);

    // переход к некст моному (к знаку +/-)
    while (*s != '\0' && *s != '+' && *s != '-') {
      s++;
    }
  }

  normalize_polynomial(poly);
  return poly;
}

// операции

Polynomial* poly_add(const Polynomial* p1, const Polynomial* p2) {
  Polynomial* result = create_polynomial();
  Monomial* m1 = p1->head;
  Monomial* m2 = p2->head;

  // копи P1 в рез
  while (m1 != NULL) {
    add_monomial_to_poly(result, m1->coefficient, m1->degree);
    m1 = m1->next;
  }

  // сложение P2 с резом
  while (m2 != NULL) {
    add_monomial_to_poly(result, m2->coefficient, m2->degree);
    m2 = m2->next;
  }

  normalize_polynomial(result);  // удаление членов с коэф 0
  return result;
}

Polynomial* poly_multiply(const Polynomial* p1, const Polynomial* p2) {
  Polynomial* result = create_polynomial();
  Monomial* m1 = p1->head;

  while (m1 != NULL) {
    Monomial* m2 = p2->head;
    while (m2 != NULL) {
      coefficient_t new_coeff = m1->coefficient * m2->coefficient;
      degree_t new_deg = m1->degree + m2->degree;

      add_monomial_to_poly(result, new_coeff, new_deg);  // объед/добавка

      m2 = m2->next;
    }
    m1 = m1->next;
  }

  normalize_polynomial(result);
  return result;
}

Polynomial* poly_differentiate(const Polynomial* p) {
  Polynomial* result = create_polynomial();
  Monomial* current = p->head;

  while (current != NULL) {
    if (current->degree > 0) {
      // d/dx(M*x^k) = (M*k)*x^(k-1)
      coefficient_t new_coeff = current->coefficient * current->degree;
      degree_t new_deg = current->degree - 1;

      add_monomial_to_poly(result, new_coeff, new_deg);
    }
    // производная от degree=0 = 0
    current = current->next;
  }

  normalize_polynomial(result);
  return result;
}

// вывод форм

char* poly_to_string(const Polynomial* poly) {
  if (poly == NULL) {
    return _strdup("0");
  }

  // 1. создание нового пустого полинома для принудильного объед
  Polynomial* final_poly = create_polynomial();
  Monomial* current_source = poly->head;

  while (current_source != NULL) {
    add_monomial_to_poly(final_poly, current_source->coefficient,
                         current_source->degree);
    current_source = current_source->next;
  }

  // 2. норм, сорт и подготовка к выводу
  normalize_polynomial(final_poly);  // удаление нулевых членов
  sort_polynomial(final_poly);       // сорт степеней от мл к ст
  Monomial* current = final_poly->head;

  // если полином пуст после норм, возврат 0
  if (current == NULL) {
    free_polynomial(final_poly);
    return _strdup("0");
  }

  // 3. резерв памяти и буфер для формата
  size_t required_size = 1;
  Monomial* temp = current;
  while (temp != NULL) {
    required_size += 30;  // 30 символов на моном
    temp = temp->next;
  }

  char* result_str = (char*)malloc(required_size);
  if (result_str == NULL) {
    perror("Error: Memory allocation failed for result string");
    free_polynomial(final_poly);
    return _strdup("");
  }
  result_str[0] = '\0';

  int is_first = 1;
  char monom_buffer[30];

  // 4. формат мономов
  while (current != NULL) {
    coefficient_t M = current->coefficient;
    degree_t k = current->degree;
    monom_buffer[0] = '\0';

    // знак + для не 1го + члена
    if (!is_first && M > 0) {
      strcat(result_str, "+");
    }

    // формат самого монома
    if (k == 0) {
      sprintf(monom_buffer, "%d", M);  // const (x^0) -> M
    } else if (k == 1) {
      // x^1 -> x, -x, M*x
      if (M == 1) {
        sprintf(monom_buffer, "%s", "x");
      } else if (M == -1) {
        sprintf(monom_buffer, "%s", "-x");
      } else {
        sprintf(monom_buffer, "%d*x", M);
      }
    } else {
      // x^k -> x^k, -x^k, M*x^k
      if (M == 1) {
        sprintf(monom_buffer, "x^%u", k);
      } else if (M == -1) {
        sprintf(monom_buffer, "-x^%u", k);
      } else {
        sprintf(monom_buffer, "%d*x^%u", M, k);
      }
    }

    // добавка монома
    strcat(result_str, monom_buffer);
    is_first = 0;

    current = current->next;
  }

  free_polynomial(final_poly);
  return result_str;
}

// обработка файла вход
void process_file(const char* input_filename, const char* output_filename) {
  FILE* fin = fopen(input_filename, "r");
  FILE* fout = fopen(output_filename, "w");
  char line1[1024];
  char line2[1024];

  if (fin == NULL || fout == NULL) {
    fprintf(stderr, "Error: Input file '%s' not found or cannot be opened.\n",
            input_filename);
    if (fin) fclose(fin);
    if (fout) fclose(fout);
    return;
  }

  printf("Input file '%s' found. Processing data...\n", input_filename);

  if (fgets(line1, sizeof(line1), fin) == NULL ||
      fgets(line2, sizeof(line2), fin) == NULL) {
    fprintf(stderr,
            "Error reading two lines from input file. Ensure the file is not "
            "empty.\n");
    fclose(fin);
    fclose(fout);
    return;
  }

  // удаление символов новой строки
  line1[strcspn(line1, "\n\r")] = 0;
  line2[strcspn(line2, "\n\r")] = 0;

  // 1. парсинг
  Polynomial* p1 = parse_polynomial(line1);
  Polynomial* p2 = parse_polynomial(line2);

  // 2. операции
  Polynomial* p_sum = poly_add(p1, p2);
  Polynomial* p_product = poly_multiply(p1, p2);
  Polynomial* p_deriv = poly_differentiate(p1);

  // 3. формат вывод
  char* sum_str = poly_to_string(p_sum);
  char* product_str = poly_to_string(p_product);
  char* deriv_str = poly_to_string(p_deriv);

  fprintf(fout, "%s\n", sum_str);
  fprintf(fout, "%s\n", product_str);
  fprintf(fout, "%s\n", deriv_str);

  // освобождение памяти
  free(sum_str);
  free(product_str);
  free(deriv_str);
  free_polynomial(p1);
  free_polynomial(p2);
  free_polynomial(p_sum);
  free_polynomial(p_product);
  free_polynomial(p_deriv);

  fclose(fin);
  fclose(fout);
  printf("Processing complete. Results written to '%s'.\n", output_filename);
}