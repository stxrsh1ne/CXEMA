#include <iostream>
#include <cmath>

using namespace std;

double lagrangeInterpolation(double x, double xi[], double fi[], int n) {
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = fi[i];

        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (x - xi[j]) / (xi[i] - xi[j]);
            }
        }
        result += term;
    }
    return result;
}

double aitkenInterpolation(double x, double xi[], double fi[], int n, double epsilon, double** matrix) {
    for (int i = 0; i < n; i++) {
        matrix[i][0] = fi[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            matrix[i][j] = (matrix[i + 1][j - 1] * (xi[i] - x) - matrix[i][j - 1] * (xi[i + j] - x)) / (xi[i + j] - xi[i]);
        }

        if (abs(matrix[0][j] - matrix[0][j - 1]) < epsilon) {
            return matrix[0][j];
        }
    }
    return matrix[0][n - 1];
}

int main() {
    double x;
    double xi[] = { 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0 };
    double fi[] = { 2.7182, 3.0041, 3.3201, 3.6692, 4.0552, 4.4816, 4.9530, 5.4739, 6.0496, 6.6858, 7.3890 };

    cout << "Enter the x value for further calculation: ";

    //cin >> x;
    x = 1.43;
    double epsilon = 0.001;
    int n = sizeof(xi) / sizeof(xi[0]);

    double** matrix = new double* [n];

    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];
    }

    double lagrangeResult = lagrangeInterpolation(x, xi, fi, n);
    double aitkenResult = aitkenInterpolation(x, xi, fi, n, epsilon, matrix);
    double epsx = pow(2.71828, x);

    cout << "Correct value : f(" << x << ") = " << epsx << endl;
    cout << "Lagrange interpolation: f(" << x << ") = " << lagrangeResult << endl;
    cout << "Aitken interpolation: f(" << x << ") = " << aitkenResult << endl;

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}