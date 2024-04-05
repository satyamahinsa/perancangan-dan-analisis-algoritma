#include <iostream>
#include <algorithm>
#include <limits.h>

#define jumlah_titik 4 // Jumlah titik dalam graf

using namespace std;

// Fungsi untuk menentukan titik pusat
int titik_pusat(int titik) {
    if (titik != 1) { // Jika titik bukan titik pusat
        return 1; // Kembalikan indeks titik pusat
    }
    return -1; // Kembalikan nilai -1 jika titik adalah titik pusat
}

// Fungsi untuk mencari rute terpendek menggunakan pendekatan brute force
void bruteForce(int graph[jumlah_titik][jumlah_titik]) {
    int min_rute = INT_MAX; // Variabel untuk menyimpan panjang rute terpendek
    int rute[jumlah_titik]; // Array untuk menyimpan rute

    // Inisialisasi rute awal
    for (int i = 0; i < jumlah_titik; i++) {
        rute[i] = i; // Setiap titik dikunjungi secara berurutan
    }

    char labels[] = {'A', 'B', 'C', 'D'}; // Label titik pada graph

    // Perulangan untuk mencoba semua kemungkinan rute
    do {
        int cost = 0; // Variabel untuk menyimpan panjang rute saat ini

        // Hitung panjang rute saat ini
        for (int i = 0; i < jumlah_titik - 1; i++) {
            cost += graph[rute[i]][rute[i + 1]]; // Tambahkan jarak antar titik
        }
        
        // Jika panjang rute saat ini lebih pendek dari rute terpendek yang sudah ditemukan
        if (cost < min_rute) {
            min_rute = cost; // Perbarui panjang rute terpendek
            // Tampilkan rute terpendek saat ini
            for (int i = 0; i < jumlah_titik - 1; i++) {
                cout << labels[rute[i]] << " -> ";

                // Cek apakah titik yang dikunjungi adalah titik pusat, jika ya, tambahkan titik pusat setelahnya
                int titik = titik_pusat(rute[i]);
                if (titik != -1)
                    cout << labels[titik] << " -> ";
            }
            cout << labels[rute[jumlah_titik - 1]] << endl; // Tampilkan titik terakhir
        }
    } while (next_permutation(rute + 1, rute + jumlah_titik)); // Coba semua kemungkinan rute yang ada

    // Tampilkan panjang rute terpendek
    cout << "Total jarak: " << min_rute << endl;
}

int main() {
    int graph[jumlah_titik][jumlah_titik] = {
        {0, 10, 30, 25}, // Baris 1: Jarak dari titik A ke titik lainnya
        {10, 0, 20, 15}, // Baris 2: Jarak dari titik B ke titik lainnya
        {30, 20, 0, 35}, // Baris 3: Jarak dari titik C ke titik lainnya
        {25, 15, 35, 0}  // Baris 4: Jarak dari titik D ke titik lainnya
    };

    bruteForce(graph);
    return 0;
}
