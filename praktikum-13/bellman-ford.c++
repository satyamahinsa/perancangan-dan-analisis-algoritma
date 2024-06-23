#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Class Edge untuk merepresentasikan sebuah edge dalam graf
class Edge {
public:
    int src, dest, weight; // src: sumber, dest: tujuan, weight: bobot
};

// Class Graph untuk merepresentasikan sebuah graf
class Graph {
public:
    int V, E; // V untuk jumlah vertex dan E untuk jumlah edge
    vector<Edge> edges; // Vector untuk menyimpan edge

    // Constructor untuk inisialisasi graf dengan V sebagai jumlah vertex dan E sebagai jumlah edge
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    // Fungsi addEdge() untuk menambahkan edge ke graf 
    // yang dimana setiap edge memiliki jarak ke sumber, jarak ke tujuan, dan besar bobot.
    void addEdge(int u, int v, int w) {
        Edge edge;
        edge.src = u;
        edge.dest = v;
        edge.weight = w;
        edges.push_back(edge);
    }

    // Fungsi bellmanFord() untuk menjalankan algoritma Bellman-Ford dari vertex sumber
    void bellmanFord(int src) {
        vector<int> distance(V, INT_MAX); // Inisialisasi jarak semua vertex dengan nilai tak hingga
        distance[src] = 0; // Jarak dari sumber ke dirinya sendiri adalah 0

        // Lakukan perulangan terhadap semua vertex untuk mencari jarak terpendek ke vertex tujuan
        for (int i = 1; i <= V - 1; i++) {
            for (int j = 0; j < E; j++) {
                int u = edges[j].src;
                int v = edges[j].dest;
                int weight = edges[j].weight;

                // Jika jarak dari vertex sumber ke v melalui vertex penghubung u lebih kecil, maka perbarui jarak terpendek
                if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }

        // Memeriksa apakah ada siklus negatif
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                cout << "Graph contains a negative-weight cycle" << endl;
                return; // Jika ditemukan siklus negatif, hentikan fungsi
            }
        }

        // Cetak hasil akhir jarak dari sumber ke setiap vertex
        printSolution(distance);
    }

    // Fungsi printSolution() untuk mencetak solusi akhir, yaitu jarak terpendek dari vertex sumber ke setiap vertex
    void printSolution(const vector<int>& distance) {
        cout << "Vertex Distance from Source" << endl;
        
        for (int i = 0; i < V; i++) {
            if (distance[i] == INT_MAX) {
                cout << i << "\t\t" << "Infinity" << endl;
            } else {
                cout << i << "\t\t" << distance[i] << endl;
            }
        }
    }
};

int main() {
    int V = 7; // Jumlah vertex
    int E = 10; // Jumlah edge

    // Membuat objek graf dengan V vertex dan E edge
    Graph graph(V, E);

    // Menambahkan edge-edge ke dalam graf
    graph.addEdge(0, 1, 6);
    graph.addEdge(0, 2, 5);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 4, -1);
    graph.addEdge(2, 1, -2);
    graph.addEdge(2, 4, 1);
    graph.addEdge(3, 2, -2);
    graph.addEdge(3, 5, -1);
    graph.addEdge(4, 6, 3);
    graph.addEdge(5, 6, 3);

    int source = 0; // Vertex sumber
    graph.bellmanFord(source); // Menjalankan algoritma Bellman-Ford dari sumber
    return 0;
}



