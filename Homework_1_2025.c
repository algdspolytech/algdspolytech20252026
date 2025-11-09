#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Данные о человеке
typedef struct Human {
    char surname[50];
    char name[50];
    char patronymic[50];
    struct Human* next;
} Human;

// Функция для создания нового узла
Human* createNode(char* surname, char* name, char* patronymic) {
    Human* newHuman = (Human*)malloc(sizeof(Human));
    if (newHuman == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    strcpy(newHuman->surname, surname);
    strcpy(newHuman->name, name);
    strcpy(newHuman->patronymic, patronymic);
    newHuman->next = NULL;
    return newHuman;
}

// Функция сравнения для сортировки
int compareHumans(Human* a, Human* b) {
    int surname_cmp = strcmp(a->surname, b->surname);
    if (surname_cmp != 0) return surname_cmp;
    
    int name_cmp = strcmp(a->name, b->name);
    if (name_cmp != 0) return name_cmp;
    
    return strcmp(a->patronymic, b->patronymic);
}

// Функция вставки в отсортированный список
Human* insertSorted(Human* head, Human* newHuman) {
    if (head == NULL || compareHumans(newHuman, head) < 0) {
        newHuman->next = head;
        return newHuman;
    }
    
    Human* current = head;
    while (current->next != NULL && compareHumans(newHuman, current->next) >= 0) {
        current = current->next;
    }
    
    newHuman->next = current->next;
    current->next = newHuman;
    return head;
}

// Функция для проверки, начинается ли строка с префикса
int startsWith(const char* str, const char* prefix) {
    if (prefix == NULL || strlen(prefix) == 0) return 1;
    if (str == NULL) return 0;
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

// Функция поиска по начальным буквам
void searchByInitials(Human* head, char* surname_prefix, char* name_prefix, char* patronymic_prefix) {
    printf("\nРезультаты поиска для \"%s\" \"%s\" \"%s\":\n", 
           surname_prefix, name_prefix, patronymic_prefix);
    
    int found = 0;
    Human* current = head;
    
    while (current != NULL) {
        if (startsWith(current->surname, surname_prefix) &&
            startsWith(current->name, name_prefix) &&
            startsWith(current->patronymic, patronymic_prefix)) {
            printf("%s %s %s\n", current->surname, current->name, current->patronymic);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Люди с такими начальными буквами не найдены.\n");
    }
}

// Функция для вывода списка фамилий
void printSurnames(Human* head) {
    printf("Список фамилий:\n");
    Human* current = head;
    while (current != NULL) {
        printf("%s\n", current->surname);
        current = current->next;
    }
}

// Функция для освобождения памяти
void freeList(Human* head) {
    Human* current = head;
    while (current != NULL) {
        Human* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    FILE *file = fopen("C:/Users/polin/OneDrive/Документы/text_1.txt", "r"); // Упростила путь к файлу
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    Human* head = NULL;
    char line[200];

   
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
    
        
        char surname[50], name[50], patronymic[50];
        
        // Разбиваем строку на фамилию, имя и отчество
        int count = sscanf(line, "%49s %49s %49s", surname, name, patronymic);
        if (count == 3) {
            Human* newHuman = createNode(surname, name, patronymic);
            if (newHuman != NULL) {
                head = insertSorted(head, newHuman);
            }
        } else {
            printf("Предупреждение: пропущена строка с неверным форматом: %s\n", line);
        }
    }

    fclose(file);

    // Проверяем, есть ли данные в списке
    if (head == NULL) {
        printf("Файл пуст или данные не были считаны.\n");
        return 1;
    }

    // Вывод списка фамилий
    printSurnames(head);

    // Поиск по начальным буквам
    char surname_prefix[50], name_prefix[50], patronymic_prefix[50];
    
    printf("\nВведите начальные буквы фамилии: ");
    if (scanf("%49s", surname_prefix) != 1) {
        strcpy(surname_prefix, "");
    }
    
    printf("Введите начальные буквы имени: ");
    if (scanf("%49s", name_prefix) != 1) {
        strcpy(name_prefix, "");
    }
    
    printf("Введите начальные буквы отчества: ");
    if (scanf("%49s", patronymic_prefix) != 1) {
        strcpy(patronymic_prefix, "");
    }

    searchByInitials(head, surname_prefix, name_prefix, patronymic_prefix);

    // Освобождение памяти
    freeList(head);

    return 0;
}