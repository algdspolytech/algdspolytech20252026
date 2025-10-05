#include<stdio.h>
#include"DayInfo.h"

void AddToListSorted(DayInfo* Root, int Date, double Temperature)
{
    DayInfo* Ptr = Root->Next;
    if (Ptr == NULL)
    {
        DayInfo* New = malloc(sizeof(DayInfo));
        New->Date = Date;
        New->Temp = Temperature;
        New->Next = NULL;
        New->Back = Root;
        Root->Next = New;
        return;
    }
    while (Ptr->Next != NULL && Ptr->Temp < Temperature)
        Ptr = Ptr->Next;
    if (Ptr->Temp >= Temperature)
    {
        while (Ptr->Next != NULL && Ptr->Date < Date && Temperature == Ptr->Temp)
            Ptr = Ptr->Next;
        if (Ptr->Next != NULL || Ptr->Temp != Temperature || Ptr->Date > Date)
        {
            DayInfo* New = malloc(sizeof(DayInfo));
            New->Date = Ptr->Date;
            New->Temp = Ptr->Temp;
            Ptr->Date = Date;
            Ptr->Temp = Temperature;
            New->Next = Ptr->Next;
            New->Back = Ptr;
            Ptr->Next = New;
            if (New->Next != NULL)
                New->Next->Back = New;
        }
    }
    if (Ptr->Next == NULL)
    {
        DayInfo* New = malloc(sizeof(DayInfo));
        New->Date = Date;
        New->Temp = Temperature;
        New->Next = NULL;
        New->Back = Ptr;
        Ptr->Next = New;
    }
}


char IsSorted(DayInfo* Root)
{
    if (Root->Next == NULL)
        return 1;
    for (DayInfo* Ptr = Root->Next; Ptr->Next != NULL; Ptr = Ptr->Next)
        if (Ptr->Next->Temp == Ptr->Temp)
        {
            if (Ptr->Next->Date < Ptr->Date)
                return 0;
        }
        else if (Ptr->Next->Temp < Ptr->Temp)
            return 0;
    return 1;
}



DayInfo* getItem(DayInfo* Root, int i)
{
    DayInfo* Ptr = Root;
    for (int k = 0; k < i; k++)
        if (Ptr == NULL)
            k = i;
        else
            Ptr = Ptr->Next;
    return Ptr;
}



void DrawStat(DayInfo* Root)
{
    if (Root != NULL)
    { 
        if(Root->Back != NULL)
            printf("%02d.%02d.%04d %6.2lf\n", (Root->Date) % 100, ((Root->Date) % 10000 - (Root->Date) % 100) / 100, (Root->Date - (Root->Date) % 10000) / 10000, Root->Temp);
        DrawStat(Root->Next);
    }
}


void DrawStatBelowTemperature(DayInfo* Root, double T)
{
    if (Root != NULL)
    {
        if (Root->Back != NULL && Root->Temp < T)
            printf("%02d.%02d.%04d %6.2lf\n", (Root->Date) % 100, ((Root->Date) % 10000 - (Root->Date) % 100) / 100, (Root->Date - (Root->Date) % 10000) / 10000, Root->Temp);
        DrawStatBelowTemperature(Root->Next, T);
    }
}

int CheckTemperature(DayInfo* Root, double T, int i, char Draw)
{

    if (Root != NULL)
    {
        if (Root->Back != NULL && Root->Temp == T)
        {
            if(Draw)
                printf("%02d.%02d.%04d %6.2lf\n", (Root->Date) % 100, ((Root->Date) % 10000 - (Root->Date) % 100) / 100, (Root->Date - (Root->Date) % 10000) / 10000, Root->Temp);
            i++;
        }
        return CheckTemperature(Root->Next, T, i, Draw);
    }
    else
        return i;
}