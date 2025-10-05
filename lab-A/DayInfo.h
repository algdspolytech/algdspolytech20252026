#pragma once
#include<stdio.h>

typedef struct DayInfo
{
    int Date; 
    double Temp; 
    struct DayInfo* Next;
    struct Dayinfo* Back;
} DayInfo;

void AddToListSorted(DayInfo* Root, int Date, double Temperature);
char IsSorted(DayInfo* Root);
DayInfo* getItem(DayInfo* Root, int i);
void DrawStat(DayInfo* Root);
void DrawStatBelowTemperature(DayInfo* Root, double T);
int CheckTemperature(DayInfo* Root, double T, int i, char Draw);