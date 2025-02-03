/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1562
*/

#include <iostream>
#include <iomanip>
#include <cmath>

#define PI 3.14159265358979323846

using namespace std;

// Производная от линейной функции
double derivative(double a, double b, double e) {
    return (1 - 2 * e / (3 * a)) * b * b * e * e / (2 * a);
}

// По формуле Ньютона-Лейбница
double calculateIntegral(double width, double height, double left, double right) {
    return PI * (derivative(width, height, right) - derivative(width, height, left));
}

void printAnswer(double width, double height, int count) {

    double integral, left, right;

    for (int i = 0; i < count; i++) {

        left = (width / count) * i;
        right = (width / count) * (i + 1);
        integral = calculateIntegral(width, height, left, right);

        cout << integral << endl;
    }
}

int main() {

    cout << fixed << showpoint << setprecision(6);

    double a, b;
    int n;
    cin >> b >> a >> n;

    printAnswer(a, b, n);

    return 0;
}
