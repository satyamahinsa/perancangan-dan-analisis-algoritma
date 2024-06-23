#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;

// Struktur untuk merepresentasikan titik dalam 2 dimensi
struct Point {
    double x, y;
};

// Fungsi untuk menghitung jarak antara dua titik (Euclidean Distance)
double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

// Fungsi untuk membandingkan dua titik berdasarkan koordinat x
bool compareX(Point p1, Point p2) {
    return p1.x < p2.x;
}

// Fungsi untuk membandingkan dua titik berdasarkan koordinat y
bool compareY(Point p1, Point p2) {
    return p1.y < p2.y;
}

// Fungsi rekursif untuk menemukan pasangan titik terdekat
pair<Point, Point> closestPairUtil(vector<Point>& points, int left, int right) {
    // Jika hanya ada dua titik, langsung kembalikan pasangan titik tersebut
    if (right - left == 1) {
        return make_pair(points[left], points[right]);
    }

    // Jika hanya ada tiga titik, hitung jarak semua pasangan dan kembalikan yang terdekat
    if (right - left == 2) {
        double d1 = dist(points[left], points[left + 1]);
        double d2 = dist(points[left + 1], points[right]);
        double d3 = dist(points[left], points[right]);
        if (d1 <= d2 && d1 <= d3) return make_pair(points[left], points[left + 1]);
        if (d2 <= d1 && d2 <= d3) return make_pair(points[left + 1], points[right]);

        return make_pair(points[left], points[right]);
    }

    // Temukan titik tengah
    int mid = (left + right) / 2;
    Point midPoint = points[mid];

    // Temukan pasangan terdekat di kedua bagian kiri dan kanan secara rekursif
    pair<Point, Point> closestLeft = closestPairUtil(points, left, mid);
    pair<Point, Point> closestRight = closestPairUtil(points, mid + 1, right);

    // Ambil pasangan terdekat dari kedua bagian
    pair<Point, Point> closestPair;
    double minDist;
    if (dist(closestLeft.first, closestLeft.second) <
        dist(closestRight.first, closestRight.second)) {
        closestPair = closestLeft;
        minDist = dist(closestLeft.first, closestLeft.second);
    } else {
        closestPair = closestRight;
        minDist = dist(closestRight.first, closestRight.second);
    }

    // Cari pasangan terdekat yang memotong garis pembagi
    vector<Point> strip;
    for (int i = left; i <= right; i++) {
        if (abs(points[i].x - midPoint.x) < minDist) {
            strip.push_back(points[i]);
        }
    }
    sort(strip.begin(), strip.end(), compareY);

    // Bandingkan jarak titik-titik dalam strip
    for (size_t i = 0; i < strip.size(); i++) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; j++) {
            double distance = dist(strip[i], strip[j]);
            if (distance < minDist) {
                minDist = distance;
                closestPair = make_pair(strip[i], strip[j]);
            }
        }
    }

    return closestPair;
}

// Fungsi untuk menemukan pasangan titik terdekat
pair<Point, Point> closestPair(vector<Point>& points) {
    // Urutkan titik berdasarkan koordinat x
    sort(points.begin(), points.end(), compareX);
    // Panggil fungsi rekursif untuk menemukan pasangan terdekat
    return closestPairUtil(points, 0, points.size() - 1);
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}}; // Contoh titik
    pair<Point, Point> closest = closestPair(points);
    cout << "Pasangan titik terdekat: (" << closest.first.x << ", " << closest.first.y << ") dan (" << closest.second.x << ", " << closest.second.y << ")" << endl;
    return 0;
}