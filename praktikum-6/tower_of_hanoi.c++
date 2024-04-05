#include <iostream>
using namespace std;

void towerOfHanoi(int n, const char asal[], const char tujuan[], const char booster[]) { 
    if(n == 0) { 
        return; 
    } 
    towerOfHanoi(n - 1, asal, booster, tujuan); 
    cout << "Pindahkan gelang " << n << " dari " << asal << " ke " << tujuan << endl; 
    towerOfHanoi(n - 1, booster, tujuan, asal);
} 

int main() {
    int T;
    cin >> T;

    if(T >= 1 && T <= 5) {
        int ronde = 1;
        while(T--) {
            int n;
            cin >> n;

            if(n >= 1 && n <= 8) {
                cout << "Ronde " << ronde << ":" << endl;
                cout << "Langkah-langkah epik Anto dalam memindahkan gelang:" << endl; 
                towerOfHanoi(n, "Base of Power", "Tower of Triumph", "Booster Platform");
                ronde++;
            }
        }
    }

    return 0;
}