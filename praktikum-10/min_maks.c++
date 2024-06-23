// #include <iostream>
// #include <vector>
// using namespace std;

// // Struktur untuk menyimpan nilai minimum dan maksimum
// struct MinMax {
//     int minimum;
//     int maximum;
// };

// // Fungsi untuk menemukan nilai minimum dan maksimum dari sebuah array
// MinMax findMinMax(const vector<int>& arr, int low, int high) {
//     MinMax result, left, right;
//     int mid;

//     // Jika hanya ada satu elemen dalam array
//     if (low == high) {
//         result.minimum = arr[low];
//         result.maximum = arr[low];
//         return result;
//     }

//     // Jika terdapat dua elemen dalam array
//     if (high == low + 1) {
//         if (arr[low] < arr[high]) {
//             result.minimum = arr[low];
//             result.maximum = arr[high];
//         } else {
//             result.minimum = arr[high];
//             result.maximum = arr[low];
//         }
//         return result;
//     }

//     // Jika terdapat lebih dari dua elemen dalam array, bagi menjadi dua bagian
//     mid = (low + high) / 2;
//     left = findMinMax(arr, low, mid);
//     right = findMinMax(arr, mid + 1, high);

//     // Gabungkan hasil dari dua bagian
//     result.minimum = min(left.minimum, right.minimum);
//     result.maximum = max(left.maximum, right.maximum);
//     return result;
// }

// int main() {
//     vector<int> arr = {7, 3, 9, 2, 11, 5}; // Contoh array
//     int n = arr.size();

//     // Cari nilai minimum dan maksimum dalam array
//     MinMax result = findMinMax(arr, 0, n - 1);

//     // Tampilkan hasil
//     cout << "Nilai Minimum: " << result.minimum << endl;
//     cout << "Nilai Maksimum: " << result.maximum << endl;
//     return 0;
// }

#include <iostream>
#include <vector>
using namespace std;

// Struktur untuk menyimpan nilai minimum dan maksimum
struct MinMax {
    int minimum;
    int maximum;
};

// Fungsi untuk menemukan nilai minimum dan maksimum dari sebuah array dengan membandingkan dalam pasangan
MinMax findMinMax(const vector<int>& arr) {
    MinMax result;
    int n = arr.size();
    int i;

    // Inisialisasi nilai minimum dan maksimum
    if (n % 2 == 0) {
        if (arr[0] < arr[1]) {
            result.minimum = arr[0];
            result.maximum = arr[1];
        } else {
            result.minimum = arr[1];
            result.maximum = arr[0];
        }
        i = 2; // Mulai dari indeks 2 jika jumlah elemen genap
    } else {
        result.minimum = result.maximum = arr[0];
        i = 1; // Mulai dari indeks 1 jika jumlah elemen ganjil
    }

    // Memproses elemen dalam pasangan
    while (i < n - 1) {
        if (arr[i] < arr[i + 1]) {
            if (arr[i] < result.minimum) result.minimum = arr[i];
            if (arr[i + 1] > result.maximum) result.maximum = arr[i + 1];
        } else {
            if (arr[i + 1] < result.minimum) result.minimum = arr[i + 1];
            if (arr[i] > result.maximum) result.maximum = arr[i];
        }
        i += 2; // Naikkan indeks sebanyak 2
    }

    return result;
}

int main() {
    vector<int> arr = {7, 3, 9, 2, 11, 5}; // Contoh array
    MinMax result = findMinMax(arr);

    // Tampilkan hasil
    cout << "Nilai Minimum: " << result.minimum << endl;
    cout << "Nilai Maksimum: " << result.maximum << endl;
    return 0;
}
