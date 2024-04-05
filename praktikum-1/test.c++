#include <iostream>
using namespace std;

int main() {
    bool isContinue = true;

    while(isContinue) {
        int num;
        cin >> num;

        if(num == 42) {
            isContinue = false;
        } else {
            cout << num << endl;
        }
    }
}