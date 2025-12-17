#pragma warning (disable:4996)

#include "Header.h" 

#define _CRTDBG_MAP_ALLOC

char* ReadTxt(const char* filename, int* lenght) {

    FILE* FPtxt = fopen(filename, "r");
    char* PA = (char*)malloc(sizeof(char));
    char x;
    int i = 0;
    while (fscanf(FPtxt, "%c", &x) != EOF) {
        PA = (char*)realloc(PA, (i + 1) * sizeof(char));
        if (PA == NULL) {
            fclose(FPtxt);
            return NULL;
        }
        *(PA + i) = x;
        i++;
    }
    *lenght = i;

    fclose(FPtxt);
    return PA;

}

void WriteTxt(const char* filename, edge* way, int waylen) {

    FILE* FPtxt = fopen(filename, "w");
    if (FPtxt == NULL) { return 0; }

    fprintf(FPtxt, "%d", waylen - 1);
    fprintf(FPtxt, "%c", '\n');

    for (int i = 0; i < waylen; i++) {
        if (i != waylen - 1) {
            fprintf(FPtxt, "%d ", way[i].vert2);
        }
        else {
            fprintf(FPtxt, "%d", way[i].vert2);
        }
    }

    fclose(FPtxt);
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

char* ReadNum(char* lines, int lenght, int* i, int* numlen, char endchar) {
    if ((lines == NULL) || (lenght == 0)){ return NULL; }

    char* buffstr = (char*)malloc(sizeof(char));
    if (buffstr == NULL) { return NULL; }

    while ((*i != lenght) && (lines[*i] != endchar)) {
        if ((lines[*i] < 48) || (lines[*i] > 57)) {
            free(buffstr);
            return NULL;//â ñòðîêå òîëüêî ÷èñëà äîëæíû áûòü
        }
        buffstr = (char*)realloc(buffstr, sizeof(char) * (*numlen + 1));
        if (buffstr == NULL) { return NULL; }
        buffstr[*numlen] = lines[*i];
        (*numlen)++;
        (*i)++;
    }
    return buffstr;
}

vertex* ReadGraph(char* lines, int lenght, int* graphlen, int* fromvert, int* tovert, int* k) {
    if ((lines == NULL) || (lenght == 0)) {
        fromvert = NULL;
        tovert = NULL;
        k = NULL;
        return NULL;
    }
    int i = 0;
    int numlen = 0;
    char* buffstr = ReadNum(lines, lenght, &i, &numlen, ' ');
    (*graphlen) = FromStr2Num(buffstr, numlen);
    i++;
    //' '
    numlen = 0;
    free(buffstr);

    buffstr = ReadNum(lines, lenght, &i, &numlen, ' ');
    (*fromvert) = FromStr2Num(buffstr, numlen);
    i++;
    //' '
    numlen = 0;
    free(buffstr);

    buffstr = ReadNum(lines, lenght, &i, &numlen, ' ');
    (*tovert) = FromStr2Num(buffstr, numlen);
    i++;
    //' '
    numlen = 0;
    free(buffstr);

    buffstr = ReadNum(lines, lenght, &i, &numlen, '\n');
    (*k) = FromStr2Num(buffstr, numlen);
    i++;
    //'\n'
    numlen = 0;
    free(buffstr);

    vertex* graph = (vertex*)malloc(sizeof(vertex) * (*graphlen));
    if (graph == NULL) { return NULL; }

    for (int j = 0; j < (*graphlen); j++) {
        graph[j].NeighboursVert = NULL;
        graph[j].NumOfNeigh = 0;
        graph[j].Vertnum = 0;
    }

    while (i < lenght) {

        int vert1 = 0;
        int vert2 = 0;

        buffstr = ReadNum(lines, lenght, &i, &numlen, ' ');
        vert1 = FromStr2Num(buffstr, numlen);
        i++;
        //' '
        numlen = 0;
        free(buffstr);

        buffstr = ReadNum(lines, lenght, &i, &numlen, '\n');
        vert2 = FromStr2Num(buffstr, numlen);
        i++;
        //'n'
        numlen = 0;
        free(buffstr);

        graph[vert1 - 1].Vertnum = vert1;
        if (graph[vert1 - 1].NumOfNeigh <= 0) {

            graph[vert1 - 1].NeighboursVert = (int*)malloc(sizeof(int));
            if (graph[vert1 - 1].NeighboursVert == NULL) { return NULL; }
            graph[vert1 - 1].NeighboursVert[0] = vert2;
            graph[vert1 - 1].NumOfNeigh = 1;

        }
        else {

            graph[vert1 - 1].NeighboursVert = (int*)realloc(graph[vert1 - 1].NeighboursVert, sizeof(int) * (graph[vert1 - 1].NumOfNeigh+1));
            if (graph[vert1 - 1].NeighboursVert == NULL) { return NULL; }
            graph[vert1 - 1].NeighboursVert[graph[vert1 - 1].NumOfNeigh] = vert2;
            graph[vert1 - 1].NumOfNeigh++;

        }

        graph[vert2 - 1].Vertnum = vert2;
        if (graph[vert2 - 1].NumOfNeigh <= 0) {

            graph[vert2 - 1].NeighboursVert = (int*)malloc(sizeof(int));
            if (graph[vert2 - 1].NeighboursVert == NULL) { return NULL; }
            graph[vert2 - 1].NeighboursVert[0] = vert1;
            graph[vert2 - 1].NumOfNeigh = 1;

        }
        else {

            graph[vert2 - 1].NeighboursVert = (int*)realloc(graph[vert2 - 1].NeighboursVert, sizeof(int) * (graph[vert2 - 1].NumOfNeigh + 1));
            if (graph[vert2 - 1].NeighboursVert == NULL) { return NULL; }
            graph[vert2 - 1].NeighboursVert[graph[vert2 - 1].NumOfNeigh] = vert1;
            graph[vert2 - 1].NumOfNeigh++;

        }
    }

    return graph;
}

int IsInWay(int prevcheckvert, int checkwert, edge* way, int currwaylen) {
    if ((prevcheckvert == 0) || (checkwert == 0) || (way == NULL) || (currwaylen == 0)) {
        return 0;
    }
    for (int i = 0; i < currwaylen; i++) {
        if (((checkwert == way[i].vert2) && (prevcheckvert == way[i].vert1)) || ((checkwert == way[i].vert1) && (prevcheckvert == way[i].vert2))) {
            return 1;
        }
    }
    return 0;
}

int FindWay(vertex* graph, int graphlen, int prevvert, int fromvert, int tovert, int k, edge** way, int* currwaylen) {
    if ((graph == NULL) || (graphlen == 0) || (fromvert == 0) || (fromvert > graphlen) || (tovert == 0) || (tovert > graphlen) || (k == 0) || (k > graphlen*graphlen)) { return 0; }

    *way = (edge*)realloc(*way,sizeof(edge) * ((*currwaylen) + 1));
    if (*way == NULL) { return 0; }

    (*way)[*currwaylen].vert1 = prevvert;
    (*way)[*currwaylen].vert2 = fromvert;
    (*currwaylen)++;

    if ((fromvert == tovert) && ((*currwaylen)-1 >= k)) {
        return 1;
    }
    else {
        for (int i = 0; i < graph[fromvert - 1].NumOfNeigh; i++) {
            if (!IsInWay(fromvert, graph[fromvert - 1].NeighboursVert[i], *way, *currwaylen)) {
                if (FindWay(graph, graphlen, fromvert, graph[fromvert - 1].NeighboursVert[i], tovert, k, way, currwaylen)) {
                    return 1;
                }
            }
        }
        (*way)[*currwaylen-1].vert1 = 0;
        (*way)[*currwaylen - 1].vert2 = 0;
        (*currwaylen)--;
        *way = (edge*)realloc(*way, sizeof(edge) * ((*currwaylen) + 1));
        if (*way == NULL) { return 0; }
        return 0;
    }
}