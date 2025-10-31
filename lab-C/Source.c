#pragma warning (disable:4996)

#include "Header.h" 

#define _CRTDBG_MAP_ALLOC 

    

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

Node* DeQueue(Queue* Q) {
    if (Q->first == NULL) { return NULL; }

    Node* res = Q->first;

    Q->first = Q->first->next;

    if (Q->first == NULL) {
        Q->last = NULL;
    }

    res->next = NULL;
    return res;
}

void InQueue(Node* pN, Queue* Q) {
    pN->next = NULL;

    if (Q->first == NULL) {
        Q->first = pN;
        Q->last = pN;
    }

    else {
        Q->last->next = pN;
        Q->last = pN;
    }
}

int* FindTheWay(int* waylen, vertex* graph, int graphlen, int FromNum, int ToNum) {

    if (graph == NULL || graphlen <= 0 || FromNum <= 0 || ToNum <= 0) {
        return NULL;
    }

    Queue GraphQueue;
    Queue* pGraphQueue = &GraphQueue;
    pGraphQueue->first = NULL;
    pGraphQueue->last = NULL;

    Node* pCurrNode = (Node*)malloc(sizeof(Node));
    int* parents = (int*)malloc(graphlen * sizeof(int));
    int* visited = (int*)malloc(graphlen * sizeof(int));
    if ((parents == NULL) || (visited == NULL) || (pCurrNode == NULL)) { return NULL; }

    int currvert;
    *(waylen) = 0;
    for (int i = 0; i < graphlen; i++) {
        parents[i] = -1;
        visited[i] = 0;
    }
    
    pCurrNode->vert = graph[FromNum-1];
    pCurrNode->next = NULL;

    InQueue(pCurrNode, pGraphQueue);

    visited[FromNum - 1] = 1;
    parents[FromNum - 1] = -1;

    while (pGraphQueue->first != NULL) {

        pCurrNode = DeQueue(pGraphQueue);
        currvert = pCurrNode->vert.Vertnum;

        if (currvert == ToNum) {

            int buff = ToNum;
            *(waylen) = 0;

            while (buff != -1) {
                buff = parents[buff - 1];
                (*waylen)++;
            }

            int* way = (int*)malloc((*waylen) * sizeof(int));
            if ((way == NULL)) { return NULL; }

            buff = ToNum;
            for (int i = (*waylen) - 1; i >= 0; i--) {
                way[i] = buff;
                buff = parents[buff-1];
            }

            free(pCurrNode);
            free(parents);
            free(visited);
            return way;
        }

        for (int i = 0; i < pCurrNode->vert.NumOfNeigh; i++) {
            int num = pCurrNode->vert.NeighboursVert[i];

            if (!visited[num - 1]) {
                visited[num - 1] = 1;
                parents[num - 1] = currvert;

                Node* pBuffNode = (Node*)malloc(sizeof(Node));
                if ((pBuffNode == NULL)) { return NULL; }

                pBuffNode->vert = graph[num - 1];
                pBuffNode->next = NULL;

                InQueue(pBuffNode, pGraphQueue);
            }
        }
        free(pCurrNode);
    }

    free(parents);
    free(visited);
    return NULL;
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

vertex* ReadGraph(char* lines, int lenght, int* graphlen) {
    if (lines == NULL || lenght <= 0) {
        return NULL;
    }
    vertex* res = (vertex*)malloc(sizeof(vertex));
    if ((res == NULL)) { return NULL; }

    vertex curr;
    int* NeighboursVert;
    int NeighboursVertNum;
    char* buffstr;
    int buffstrlen;
    int breakfl = 0;
    char* num;
    int lnum = 0;
    int i = 0;
    *graphlen = 0;

    while ((i<lenght) && (!breakfl)) {

        lnum = 0;
        num = (char*)malloc(sizeof(char));
        if ((num == NULL)) { return NULL; }

        while (lines[i] != ':') {

            num = (char*)realloc(num, (lnum + 1) * sizeof(char));
            if ((num == NULL)) { return NULL; }

            num[lnum] = lines[i];
            lnum++;
            i++;
        }

        //x == ':'
        i++;
        //x == ' '
        if (lines[i] == ' ') {
            i++;;
        }
        //readvert
        NeighboursVert = (int*)malloc(sizeof(int));
        if ((NeighboursVert == NULL)) { return NULL; }
        NeighboursVertNum = 0;
        while (lines[i] != '\n') {

            buffstr = (char*)malloc(sizeof(char));
            buffstrlen = 0;

            while ((lines[i] != ' ') && (lines[i] != '\n')) {

                buffstr = (char*)realloc(buffstr, (buffstrlen + 1) * sizeof(char));
                if ((buffstr == NULL)) { return NULL; }

                buffstr[buffstrlen] = lines[i];
                buffstrlen++;
                i++;
                if (i>=lenght) { breakfl = 1;  break; };
            }

            NeighboursVert = (int*)realloc(NeighboursVert, (NeighboursVertNum + 1) * sizeof(int));
            if ((NeighboursVert == NULL)) { return NULL; }

            NeighboursVert[NeighboursVertNum] = FromStr2Num(buffstr, buffstrlen);
            NeighboursVertNum++;

            free(buffstr);

            //x == ' '
            if (lines[i] == ' ') {
                i++;
            }
            if (breakfl) {
                break;
            }
        }

        curr.NeighboursVert = NeighboursVert;
        curr.NumOfNeigh = NeighboursVertNum;

        *graphlen = FromStr2Num(num, lnum);
        curr.Vertnum = *graphlen;

        res = (vertex*)realloc(res, ((*graphlen)) * sizeof(vertex));
        if ((res == NULL)) { 
            return NULL; 
        }

        res[(*graphlen)-1] = curr;
        free(num);
        i++;
    }


    return res;
}

void FreeGraph(vertex* graph, int len) {
    for (int i = 0; i < len; i++) {
        free(graph[i].NeighboursVert);
    }
}

void PrintWay(int* way, int waylen) {
    if (waylen == 0) {
        printf("Нет Пути!");
    }
    else {
        printf("lenght = %d: ", waylen);
        for (int i = 0; i < waylen; i++) {
            if (i != waylen - 1) {
                printf("%d->", way[i]);
            }
            else {
                printf("%d", way[i]);
            }
        }
    }
}

/*int main() {

    setlocale(LC_CTYPE, "Russian");
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    const char* GraphFile = "GraphFile.txt";

    vertex* graph;
    char* lines;
    int lenlines;
    int graphlen;
    int* way;
    int waylen;
    
    lines = ReadTxt(GraphFile, &lenlines);
    graph = ReadGraph(lines, lenlines, &graphlen);
    way = FindTheWay(&waylen, graph, graphlen, 1, 8);

    FreeGraph(graph, graphlen);
    PrintWay(way,waylen);
    free(way);
    free(graph);
    free(lines);
}
*/