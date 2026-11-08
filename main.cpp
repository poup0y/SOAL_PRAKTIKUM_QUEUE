
#include "Queue.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <climits>

using namespace std;

int main() {
    Queue q;
    createQueue(q);

    string baris, perintah;

    cout << "====================================\n";
    cout << "    BUFFER PENCATATAN HASIL UKUR\n";
    cout << "====================================\n";

    cout << "TULIS k v1 ... vk\n";
    cout << "AMBIL k\n";
    cout << "LIHAT\n";
    cout << "RINGKAS\n";
    cout << "KOSONGKAN\n";
    cout << "SELESAI\n";

    while (true) {
        cout << "\nMasukkan perintah: ";

        if (!getline(cin, baris)) {
            break;
        }

        stringstream ss(baris);
        ss >> perintah;

        if (perintah == "TULIS") {
            int k;
            int nilai[6];

            if (!(ss >> k) || k < 1 || k > 6) {
                cout << "Ditolak: k harus 1-6.\n";
                continue;
            }

            bool lengkap = true;
            bool valid = true;

            for (int i = 0; i < k; i++) {
                if (!(ss >> nilai[i])) {
                    lengkap = false;
                    break;
                }

                if (nilai[i] < -1000 || nilai[i] > 1000) {
                    valid = false;
                }
            }

            if (!lengkap) {
                cout << "Ditolak: jumlah nilai tidak sesuai.\n";
                continue;
            }

            if (!valid) {
                cout << "Ditolak: nilai harus -1000 sampai 1000.\n";
                continue;
            }

            if (spaceLeft(q) < k) {
                cout << "Ditolak: ruang kosong tidak cukup.\n";
                cout << "Ruang tersedia: "
                     << spaceLeft(q) << endl;
                continue;
            }

            for (int i = 0; i < k; i++) {
                enqueue(q, nilai[i]);
            }

            cout << "Berhasil menambahkan "
                 << k << " rekaman.\n";
        }

        else if (perintah == "AMBIL") {
            int k;

            if (!(ss >> k) || k <= 0 || k > countData(q)) {
                cout << "Ditolak: jumlah data tidak mencukupi.\n";
                cout << "Data tersedia: "
                     << countData(q) << endl;
                continue;
            }

            for (int i = 0; i < k; i++) {
                Record r = dequeue(q);

                cout << "Diambil: "
                     << r.nomor << ":" << r.nilai << endl;
            }
        }

        else if (perintah == "LIHAT") {
            printQueue(q);
        }

        else if (perintah == "RINGKAS") {
            int jumlah = countData(q);

            long long total = 0;
            int minimum = INT_MAX;
            int maksimum = INT_MIN;

            for (int i = 0; i < jumlah; i++) {
                Record r = atQueue(q, i);

                total += r.nilai;

                if (r.nilai < minimum) {
                    minimum = r.nilai;
                }

                if (r.nilai > maksimum) {
                    maksimum = r.nilai;
                }
            }

            cout << "\n===== RINGKASAN DATA =====\n";
            cout << "Jumlah: " << jumlah << endl;
            cout << "Total: " << total << endl;

            if (jumlah == 0) {
                cout << "Minimum: TIDAK ADA\n";
                cout << "Maksimum: TIDAK ADA\n";
                cout << "Rata-rata: TIDAK ADA\n";
            } else {
                cout << "Minimum: " << minimum << endl;
                cout << "Maksimum: " << maksimum << endl;

                cout << "Rata-rata: "
                     << fixed << setprecision(2)
                     << (double) total / jumlah << endl;
            }

            cout << "Total pergeseran: "
                 << shiftCount(q) << endl;
        }

        else if (perintah == "KOSONGKAN") {
            clearQueue(q);

            cout << "Buffer berhasil dikosongkan.\n";
            cout << "Nomor dan penghitung pergeseran tetap dipertahankan.\n";
        }

        else if (perintah == "SELESAI") {
            cout << "Program selesai.\n";
            break;
        }

        else if (!perintah.empty()) {
            cout << "Perintah tidak dikenal.\n";
        }
    }

    return 0;
}
