#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char judul[100];
    char penulis[100];
    int tahun_terbit;
    char nomor_rak[10];
} Buku;

void merge(Buku array[], int left, int mid, int right, int criterion) {
    int subArrayOne = mid - left + 1;
    int subArrayTwo = right - mid;

    Buku* leftArray = (Buku*)malloc(subArrayOne * sizeof(Buku));
    Buku* rightArray = (Buku*)malloc(subArrayTwo * sizeof(Buku));

    for (int i = 0; i < subArrayOne; i++) leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++) rightArray[j] = array[mid + 1 + j];

    int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (criterion == 1) {
            if (strcmp(leftArray[indexOfSubArrayOne].judul, rightArray[indexOfSubArrayTwo].judul) < 0) {
                array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            } else {
                array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
        } else if (criterion == 2) {
            if (strcmp(leftArray[indexOfSubArrayOne].penulis, rightArray[indexOfSubArrayTwo].penulis) < 0) {
                array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            } else {
                array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
        } else {
            if (leftArray[indexOfSubArrayOne].tahun_terbit < rightArray[indexOfSubArrayTwo].tahun_terbit) {
                array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            } else {
                array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    free(leftArray);
    free(rightArray);
}

void mergeSort(Buku array[], int begin, int end, int criterion) {
    if (begin < end) {
        int mid = begin + (end - begin) / 2;
        mergeSort(array, begin, mid, criterion);
        mergeSort(array, mid + 1, end, criterion);
        merge(array, begin, mid, end, criterion);
    }
}

int main() {
    Buku buku[] = {
        { "Belajar Algoritma", "Ahmad", 2018, "A101" },
        { "Dasar Pemrograman", "Budi", 2020, "B202" },
        { "Cerita Anak", "Cici", 2019, "C303" },
        { "Pemrograman Web Modern", "Dani", 2021, "D404" },
        { "Ilmu Komputer Dasar", "Edi", 2017, "E505" },
        { "Data Science Fundamentals", "Fajar", 2018, "F606" },
        { "Artificial Intelligence Basics", "Gita", 2019, "G707" },
        { "Machine Learning Mastery", "Hadi", 2020, "H808" },
        { "Network Security Essentials", "Ika", 2016, "I909" },
        { "Introduction to Robotics", "Johan", 2015, "J1010" },
        { "Graphic Design Fundamentals", "Kiki", 2018, "K1111" },
        { "Mobile App Development", "Lina", 2021, "L1212" },
        { "Digital Marketing Strategy", "Mira", 2019, "M1313" },
        { "Business Finance Basics", "Nita", 2017, "N1414" },
        { "Leadership and Management", "Oki", 2020, "O1515" },
        { "Strategic Planning Handbook", "Putri", 2018, "P1616" },
        { "Public Speaking Skills", "Qori", 2019, "Q1717" },
        { "Time Management Techniques", "Rama", 2016, "R1818" },
        { "Creative Writing Workshop", "Sari", 2021, "S1919" },
        { "Meditation for Beginners", "Tono", 2017, "T2020" }
    };
    int jumlahBuku = sizeof(buku) / sizeof(buku[0]);
    int input;

    do {
        printf("\nUrutkan berdasarkan:\n");
        printf("1. Judul\n");
        printf("2. Penulis\n");
        printf("3. Tahun Terbit\n");
        printf("4. Keluar\n");
        printf("Pilihan anda: ");
        scanf("%d", &input);

        if (input < 1 || input > 4) {
            printf("Pilihan tidak valid!\n");
        } else if (input == 4) {
            break;
        } else {
            mergeSort(buku, 0, jumlahBuku - 1, input);

            for (int i = 0; i < jumlahBuku; i++) {
                printf("Judul: %s, Penulis: %s, Tahun Terbit: %d, Nomor Rak: %s\n", buku[i].judul, buku[i].penulis, buku[i].tahun_terbit, buku[i].nomor_rak);
            }
        }
    } while (input != 4);

    return 0;
}
