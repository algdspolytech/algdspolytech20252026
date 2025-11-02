#include<stdio.h>
#include"queue_arr.h"
#include"queue_list.h"


int main() {
	printf("List Queue:\n");
	QueueList* ListQueue = create_queue_list();

	enqueue(ListQueue, 13);

	enqueue(ListQueue, 11);

	enqueue(ListQueue, 21);

	int status;
	printf("first element: %d\n", peak(ListQueue, &status));

	printf("dequeued: %d\n", dequeue(ListQueue, &status));


	destroy_queue(ListQueue);


	printf("\nArray Queue:\n");
	QueueArray* arrayQueue = create_queue_array(5);

	enqueue_array(arrayQueue, 44, &status);

	enqueue_array(arrayQueue, 31, &status);

	enqueue_array(arrayQueue, 35, &status);

	printf("first element: %d\n", peak_array(arrayQueue, &status));

	printf("Dequeued: %d\n", dequeue_array(arrayQueue, &status));


	destroy_queue_array(arrayQueue);

	return 0;
}

