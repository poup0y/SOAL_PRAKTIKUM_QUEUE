
#include "Queue.h"
#include <iostream>

using namespace std;

// Membuat queue kosong
void createQueue(Queue& q) {
    q.head = -1;
    q.tail = -1;
    q.nextNumber = 1;
    q.shifts = 0;
}

// Menghitung jumlah data
int countData(const Queue& q) {
    if (q.head == -1) {
        return 0;
    }

    return q.tail - q.head + 1;
}

// Menghitung ruang kosong
int spaceLeft(const Queue& q) {
    return 6 - countData(q);
}

// Menambahkan data
void enqueue(Queue& q, int nilai) {

    if (q.head == -1) {
        q.head = 0;
        q.tail = 0;
    } else {

        // Pemadatan jika tail sudah di indeks terakhir
        if (q.tail == 5 && q.head > 0) {

            int jumlah = countData(q);

            for (int i = 0; i < jumlah; i++) {
                q.data[i] = q.data[q.head + i];
                q.shifts++;
            }

            q.head = 0;
            q.tail = jumlah - 1;
        }

        q.tail++;
    }

    q.data[q.tail].nomor = q.nextNumber++;
    q.data[q.tail].nilai = nilai;
}

// Mengambil data tanpa menggeser
Record dequeue(Queue& q) {

    Record hasil = q.data[q.head];

    if (q.head == q.tail) {
        q.head = -1;
        q.tail = -1;
    } else {
        q.head++;
    }

    return hasil;
}

// Mengambil data berdasarkan posisi FIFO
Record atQueue(const Queue& q, int pos) {
    return q.data[q.head + pos];
}

// Menampilkan isi queue
void printQueue(const Queue& q) {

    cout << "\nUrutan FIFO: ";

    for (int i = 0; i < countData(q); i++) {
        Record r = atQueue(q, i);

        cout << r.nomor << ":" << r.nilai << " ";
    }

    if (countData(q) == 0) {
        cout << "(Kosong)";
    }

    cout << "\nIndeks fisik:\n";

    for (int i = 0; i < 6; i++) {

        if (q.head != -1 &&
            i >= q.head && i <= q.tail) {

            cout << "[" << q.data[i].nomor
                 << ":" << q.data[i].nilai << "] ";

        } else {
            cout << "[Kosong] ";
        }
    }

    cout << "\nHead: " << q.head;
    cout << "\nTail: " << q.tail;
    cout << "\nJumlah pergeseran: " << q.shifts << endl;
}

// Mengosongkan queue
void clearQueue(Queue& q) {
    q.head = -1;
    q.tail = -1;
}

// Mengambil jumlah pergeseran
long long shiftCount(const Queue& q) {
    return q.shifts;
}
