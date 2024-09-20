#include <iostream>


void make_triagle(int n) {
    n = n * 2;
    int c = 0;
    int lc = 0;
    while (c < n) {
        if (c > n - c) {
                lc = n - c;
        }
        else {
                lc = c;
        } 
        for (int i = 0; i < lc; i++) {
                std::cout << '*';
        }
        std::cout << std::endl;
        ++c;
    }
}


int main() {
    int n;
    std::cin >> n;
    make_triagle(n);
    return 0;
}
