#pragma once
#ifndef LABD_H
#define LABD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int deadline;
} Wagon;

void swap(Wagon* a, Wagon* b);
void siftDownMaxHeap(Wagon* heap, int size, int i);
void siftUpMaxHeap(Wagon* heap, int i);
void heapPush(Wagon* heap, int* size, Wagon w);
Wagon heapPop(Wagon* heap, int* size);
int comp(const void* a, const void* b);
int minUnfinished(Wagon* wagons, int n);

#endif