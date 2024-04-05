#include <iostream>
using namespace std;

int main() {
    string arr[100];
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < arr[i].length() - 1; j++) {
            for (int k = j + 1; k < arr[i].length(); k++) {
                if (arr[i][j] > arr[i][k]) {
                    char temp = arr[i][j];
                    arr[i][j] = arr[i][k];
                    arr[i][k] = temp;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i] << endl;
    }

    return 0;
}
