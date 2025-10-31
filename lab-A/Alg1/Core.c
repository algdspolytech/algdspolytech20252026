#pragma warning (disable:4996)


#include "Header.h" 

#define _CRTDBG_MAP_ALLOC 



void PrintWorker(Worker* worker) {
    printf("%02d.%02d.%04d %s %s %lf\n", worker->day, worker->month, worker->year, worker->surname, worker->name, worker->hours);
}

int PrintStaff(Staff* head, double n) {
    int PrintedFlag = 0;
    Staff* current = head;
    Staff* help;
    double total = 0;

    while (current != NULL) {

        help = head;
        total = current->CurrWorker->hours;

        while (help != NULL) {
            if (IfSameWorker(help->CurrWorker, current->CurrWorker) && (help != current)) {
                total += help->CurrWorker->hours;
            }
            help = help->NextWorker;
        }

        if (total > n) {
            PrintedFlag = 1;
            printf("%s %s %02d.%02d.%04d \n", current->CurrWorker->surname, current->CurrWorker->name, current->CurrWorker->day, current->CurrWorker->month, current->CurrWorker->year);
        }
        current = current->NextWorker;
    }
    return PrintedFlag;
}

int IfSameWorker(Worker* w1, Worker* w2) {
    if ((strcmp(w1->surname, w2->surname) == 0) && (strcmp(w1->name, w2->name) == 0)) {
        return 1;
    }
    return 0;
}

int WorkerCmp(Worker* w1, Worker* w2) {

    if (w1->hours < w2->hours) {
        return 1;
    }

    else if (w1->hours == w2->hours) {

        if (strcmp(w1->surname, w2->surname) < 0) {
            return 1;
        }

        else if (strcmp(w1->surname, w2->surname) == 0) {

            if ((strcmp(w1->name, w2->name) < 0)) {
                return 1;
            }
            else if (strcmp(w1->name, w2->name) == 0) {

                if (w1->year < w2->year) {
                    return 1;
                }
                else if (w1->year == w2->year) {

                    if (w1->month < w2->month) {
                        return 1;
                    }
                    else if (w1->month == w2->month) {
                        if (w1->day < w2->day) {
                            return 1;
                        }
                    }

                }

            }
        }
    }

    return 0;
}

char* ReadTxt(const char* filename, int* lenght) {

    FILE* FPtxt = fopen(filename, "r");
    char* PA = (char*)malloc(sizeof(char));
    char x;
    int i = 0;
    while (fscanf(FPtxt, "%c", &x) != EOF) {
        PA = (char*)realloc(PA, (i + 1) * sizeof(char));
        *(PA + i) = x;
        i++;
    }
    *lenght = i;

    fclose(FPtxt);
    return PA;

}

int FromStr2Num(char* str, int len) {

    int res = 0;
    for (int i = 0; i < len; i++) {
        res *= 10;
        if ((str[i] < 48) || (str[i] > 57)) {
            return -1;
        }
        res += ((int)str[i] - 48);//ASCII
    }

    return res;

}

char* ReadOneData(char* lines, int lenght, int* i, int* LenInfoList, char EndChar) {

    if (lines == NULL || i == NULL || LenInfoList == NULL || lenght <= 0 || *i < 0) {
        return NULL;
    }
    int flag = 0;
    char* InfoList;
    *LenInfoList = 0;
    InfoList = (char*)malloc(sizeof(InfoList));
    if (InfoList == NULL) { return 0; }

    while (lines[*i] != EndChar) {
        if (lines[*i] == "\n") {
            return NULL;
        }
        (*LenInfoList)++;
        InfoList = (char*)realloc(InfoList, (*LenInfoList) * sizeof(char));
        if (InfoList == NULL) {
            return 0;
        }
        InfoList[(*LenInfoList) - 1] = lines[*i];
        (*i)++;
        if ((*i) == lenght) {
            break;
        }
    }//Читаем до разделителя или конца строки
    InfoList = (char*)realloc(InfoList, (*LenInfoList + 1) * sizeof(char));
    InfoList[(*LenInfoList)] = '\0';
    return InfoList;
}

Worker* CreateWorker(char* lines, int lenght, int* i) {
    Worker* WorkerMan;
    int* pLenInfoList;
    char* InfoList;
    int LenInfoList = 0;
    pLenInfoList = &LenInfoList;

    WorkerMan = (Worker*)malloc(sizeof(Worker));
    if (WorkerMan == NULL) { return 0; }
    if ((lines == NULL) || (lenght == 0)) { 
        free(WorkerMan);
        return NULL;
    }

    InfoList = ReadOneData(lines, lenght, i, pLenInfoList, '.');
    WorkerMan->day = FromStr2Num(InfoList, LenInfoList);
    (*i)++;
    *pLenInfoList = 0;
    free(InfoList);

    InfoList = ReadOneData(lines, lenght, i, pLenInfoList, '.');
    WorkerMan->month = FromStr2Num(InfoList, LenInfoList);
    (*i)++;
    *pLenInfoList = 0;
    free(InfoList);

    InfoList = ReadOneData(lines, lenght, i, pLenInfoList, ' ');
    WorkerMan->year = (int)FromStr2Num(InfoList, LenInfoList);
    (*i)++;
    *pLenInfoList = 0;
    free(InfoList);

    InfoList = ReadOneData(lines, lenght, i, pLenInfoList, ' ');
    WorkerMan->surname = InfoList;
    (*i)++;
    *pLenInfoList = 0;

    InfoList = ReadOneData(lines, lenght, i, pLenInfoList, ' ');
    WorkerMan->name = InfoList;
    (*i)++;
    *pLenInfoList = 0;

    InfoList = ReadOneData(lines, lenght, i, pLenInfoList, '\n');
    WorkerMan->hours = (double)FromStr2Num(InfoList, LenInfoList);
    *pLenInfoList = 0;
    free(InfoList);

    return WorkerMan;
}

Staff* CreateStaff(char* lines, int lenght){
    Staff* head = NULL;
    Staff* tail = NULL;
    Staff* man = NULL;
    Worker* currWorker;
    int i = 0;
    if (lines == NULL) {
        return NULL;
    }
    while (i < lenght) {
        currWorker = CreateWorker(lines, lenght, &i);
        i++;
        if (currWorker == NULL) { return NULL; }
        man = (Staff*)malloc(sizeof(Staff));
        man->CurrWorker = currWorker;
        man->NextWorker = NULL;
        if (head == NULL) {
            head = man;
            tail = man;
        }
        else {
            tail->NextWorker = man;
            tail = man;
        }
    }
    return head;
}

void FreeStaff(Staff* head) {
    Staff* current = head;
    Staff* next;

    while (current != NULL) {
        next = current->NextWorker;
        if (current->CurrWorker != NULL) {
            if (current->CurrWorker->name != NULL)
                free((void*)current->CurrWorker->name);
            if (current->CurrWorker->surname != NULL)
                free((void*)current->CurrWorker->surname);
            free(current->CurrWorker);
        }

        free(current);
        current = next;
    }
}

Staff* InsertWorker(Staff* sorted, Staff* current) {
    
    Staff* now = sorted;

    if ((sorted == NULL) || WorkerCmp(current->CurrWorker, sorted->CurrWorker)) {
        current->NextWorker = sorted;
        return current;
    }

    now = sorted;
    while ((now->NextWorker != NULL) && WorkerCmp(now->NextWorker->CurrWorker, current->CurrWorker)) {
        now = now->NextWorker;
    }

    current->NextWorker = now->NextWorker;
    now->NextWorker = current;
    return sorted;

}

Staff* InsertSort(Staff* Head) {
    Staff* sorted = NULL;
    Staff* Curr = Head;
    Staff* Next;
    while (Curr != NULL) {
        Next = Curr->NextWorker;
        sorted = InsertWorker(sorted, Curr);
        Curr = Next;
    }
    return sorted;
}


/*int main() {

    setlocale(LC_CTYPE, "Russian");
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    const char* StaffFile = "StaffFile.txt";
    int lenght = 0;
    int i = 0;
    double n;
    char* lines;
    Staff* s1;
    Worker* w1;
    lines = ReadTxt(StaffFile, &lenght);
    scanf("%lf", &n);

    s1 = CreateStaff(lines,lenght);
    s1 = InsertSort(s1);
    PrintStaff(s1, n);
    FreeStaff(s1);
    free(lines);
}*/
