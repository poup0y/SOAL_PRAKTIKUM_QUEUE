
#ifndef QUEUE_H
#define QUEUE_H

struct Record {
    int nomor;
    int nilai;
};

struct Queue {
    Record data[6];
    int head;
    int tail;
    int nextNumber;
    long long shifts;
};

void createQueue(Queue& q);
int countData(const Queue& q);
int spaceLeft(const Queue& q);

void enqueue(Queue& q, int nilai);
Record dequeue(Queue& q);

Record atQueue(const Queue& q, int pos);

void printQueue(const Queue& q);
void clearQueue(Queue& q);

long long shiftCount(const Queue& q);

#endif
