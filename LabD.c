#include "LabD.h"

void swap(Wagon* a, Wagon* b) {
    Wagon t = *a;
    *a = *b;
    *b = t;
}

void siftDownMaxHeap(Wagon* heap, int size, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < size && heap[l].time > heap[largest].time) {
        largest = l;
    }
    if (r < size && heap[r].time > heap[largest].time) {
        largest = r;
    }
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        siftDownMaxHeap(heap, size, largest);
    }
}

void siftUpMaxHeap(Wagon* heap, int i) {
    if (i > 0 && heap[(i - 1) / 2].time < heap[i].time) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        siftUpMaxHeap(heap, (i - 1) / 2);
    }
}

void heapPush(Wagon* heap, int* size, Wagon w) {
    heap[*size] = w;
    (*size)++;
    siftUpMaxHeap(heap, *size - 1);
}

Wagon heapPop(Wagon* heap, int* size) {
    Wagon root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    siftDownMaxHeap(heap, *size, 0);
    return root;
}

int comp(const void* a, const void* b) {
    return ((Wagon*)a)->deadline - ((Wagon*)b)->deadline;
}

int minUnfinished(Wagon* wagons, int n) {
    if (n <= 0) {
        return 0;
    }

    qsort(wagons, n, sizeof(Wagon), comp);

    Wagon* heap = (Wagon*)malloc(n * sizeof(Wagon));
    int heapSize = 0;
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        heapPush(heap, &heapSize, wagons[i]);
        currentTime += wagons[i].time;

        if (currentTime > wagons[i].deadline) {
            Wagon removed = heapPop(heap, &heapSize);
            currentTime -= removed.time;
        }
    }

    free(heap);
    return n - heapSize;
}