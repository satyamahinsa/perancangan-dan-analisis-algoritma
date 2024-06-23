#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

// Class Vertex untuk merepresentasikan sebuah Vertex (Node)
class Vertex {
public:
  int src, dest, distance, cost;
};

// Class Graph untuk merepresentasikan sebuah Graph secara keseluruhan
class Graph {
public:
    int V, E; // V adalah jumlah vertex, E adalah jumlah edge
    vector<Vertex> vertexs;

    // Konstruktor
    Graph(int V, int E) : V(V), E(E) {}

    // Fungsi addEdge untuk menambahkan edge dari vertex asal ke vertex tujuan
    void addEdge(int u, int v, int d, int c) {
        Vertex vertex;
        vertex.src = u;
        vertex.dest = v;
        vertex.distance = d;
        vertex.cost = c;
        vertexs.push_back(vertex);
    }

  // Fungsi bellmanFord menggunakan algoritma Bellman-Ford 
  // untuk mencari jalur terpendek berdasarkan prioritas yang diinginkan
  void bellmanFord(int src, int dest, const string& priority) {
    vector<int> distance(V, INT_MAX);
    vector<int> cost(V, INT_MAX);
    vector<int> shortest_path(V, -1);
    distance[src] = 0;
    cost[src] = 0;

    // Melakukan kunjungan pada semua vertex sebanyak V-1 kali 
    // dan memperhitungkan semua vertex dalam graph
    for (int i = 1; i <= V - 1; i++) {
      for (const auto& vertex : vertexs) {
        int u = vertex.src;
        int v = vertex.dest;
        int d = vertex.distance;
        int c = vertex.cost;
        if (priority == "distance") {
          // Memperbarui distance jika jalur baru lebih pendek 
          // dan menghitung cost yang sesuai berdasarkan jalur distance terpendek
          if (distance[u] != INT_MAX && distance[u] + d < distance[v]) {
            distance[v] = distance[u] + d;
            cost[v] = cost[u] + c;
            shortest_path[v] = u;
          }
        } else if (priority == "cost") {
          // Memperbarui cost jika jalur baru lebih murah 
          // dan menghitung distance yang sesuai berdasarkan jalur cost terpendek
          if (cost[u] != INT_MAX && cost[u] + c < cost[v]) {
            cost[v] = cost[u] + c;
            distance[v] = distance[u] + d;
            shortest_path[v] = u;
          }
        }
      }
    }

    // Memeriksa apakah ada siklus negatif di dalam jalur yang sudah didapatkan
    for (const auto& vertex : vertexs) {
      int u = vertex.src;
      int v = vertex.dest;
      int d = vertex.distance;
      int c = vertex.cost;
      if (priority == "distance" && distance[u] != INT_MAX && distance[u] + d < distance[v]) {
        cout << "Graph contains a negative-weight cycle" << endl;
        return;
      } else if (priority == "cost" && cost[u] != INT_MAX && cost[u] + c < cost[v]) {
        cout << "Graph contains a negative-weight cycle" << endl;
        return;
      }
    }

    // Mencetak solusi
    if (priority == "distance") {
      // Jika distance dari sumber ke tujuan tidak terdefinisi (INT_MAX)
      if (distance[dest] == INT_MAX) {
        cout << "Tidak ada jalur dari kota " << src + 1 << " ke kota " << dest + 1 << endl;
      } else {
        // Jika jalur ditemukan, tampilkan total distance, cost, dan jalur terpendek
        cout << "Total Jarak: " << distance[dest] << " km" << endl;
        cout << "Total Biaya: " << cost[dest] << endl;
        cout << "Jalur Terpendek: ";
        printPath(shortest_path, dest);
      }
    } else if (priority == "cost") {
      // Jika cost dari sumber ke tujuan tidak terdefinisi (INT_MAX)
      if (cost[dest] == INT_MAX) {
        cout << "Tidak ada jalur dari kota " << src + 1 << " ke kota " << dest + 1 << endl;
      } else {
        // Jika jalur ditemukan, tampilkan total distance, cost, dan jalur terpendek
        cout << "Total Jarak: " << distance[dest] << " km" << endl;
        cout << "Total Biaya: " << cost[dest] << endl;
        cout << "Jalur Terpendek: ";
        printPath(shortest_path, dest);
      }
    }
  }

  // Fungsi rekursif untuk mencetak jalur terpendek dari sumber ke tujuan
  void printPath(const vector<int>& shortest_path, int vertex) {
    // Basis rekursif tercapai ketika vertex adalah vertex sumber
    if (shortest_path[vertex] == -1) {
      cout << vertex + 1;
      return;
    }
    printPath(shortest_path, shortest_path[vertex]);
    cout << " -> " << vertex + 1;
  }
};

int main() {
  int V = 10; // Jumlah vertex
  int E = 20; // Jumlah edge
  Graph graph(V, E); // Inisialisasi graph dengan V vertex dan E edge

  // Menambahkan edge dengan jarak dan ongkos
  graph.addEdge(0, 1, 3, 5);
  graph.addEdge(0, 2, 1, 2);
  graph.addEdge(0, 3, 7, 3);
  graph.addEdge(1, 4, 2, 1);
  graph.addEdge(1, 5, 10, 4);
  graph.addEdge(1, 6, 5, 6);
  graph.addEdge(2, 4, 3, 3);
  graph.addEdge(2, 5, 3, 8);
  graph.addEdge(2, 6, 5, 5);
  graph.addEdge(3, 4, 8, 1);
  graph.addEdge(3, 5, 2, 3);
  graph.addEdge(3, 6, 6, 7);
  graph.addEdge(4, 7, 7, 2);
  graph.addEdge(4, 8, 3, 1);
  graph.addEdge(5, 7, 4, 9);
  graph.addEdge(5, 8, 1, 6);
  graph.addEdge(6, 7, 9, 5);
  graph.addEdge(6, 8, 8, 7);
  graph.addEdge(7, 9, 3, 7);
  graph.addEdge(8, 9, 1, 4);

  int startCity, endCity;
  string priority;

  cout << "Enter start city (1-10): ";
  cin >> startCity;
  cout << "Enter end city (1-10): ";
  cin >> endCity;
  cout << "Enter priority (distance/cost): ";
  cin >> priority;

  // Memastikan input kota berada dalam rentang yang valid
  if (startCity < 1 || startCity > V || endCity < 1 || endCity > V) {
    cout << "Invalid Input" << endl;
    return -1;
  }

  // Menyesuaikan input ke indeks array (0-based index)
  startCity--;
  endCity--;

  graph.bellmanFord(startCity, endCity, priority);
  return 0;
}