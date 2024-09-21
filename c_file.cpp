#include <iostream>

int find_determinant(int n, double * parr) {
        double koef;
        for (int i = 0; i < n; ++i) {
                for (int i2 = i + 1; i2 < n; ++i2) {
                        koef = parr[n * i2 + i] / parr[n * i + i];
                        for (int j = 0; j < n; ++j) {
                                parr[i2 * n + j] = parr[i2 * n + j] -  koef * parr[i * n + j];
                        }
                }       
        }
        double result = 1.0;
        for (int i = 0; i < n; ++i) {
                result = result * parr[i * n + i];
        }

	return result;
}



int main() {
	double * parr = new double[16]{1, 2, 3, 4, 0, 3, 4, 5, 4, 5, 6, 7, 0, 0, 0, 1};
        std::cout << find_determinant(4,  parr) << std::endl;
        return 0;
}








