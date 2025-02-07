/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1028

  Имеем массив, размер которого - количество X координат, в каждой ячейке держим количество звезд, находящихся не правее данной кординаты
  Поскольку координаты идут снизу вверх и справа налево, для каждой новой звезды - ее ранг равняется значению в массиве, соответствующему ее X координате,
  ведь все последующие звезды будут либо выше, либо правее
  
  Используем древо Фенвика для подсчета суммы за логарифмическое время
*/

#include <iostream>

#define MAX_STARS 15000
#define X_DIMENSION_SIZE 32000

using namespace std;

int sumTo(int a, int* fTree) {
    int result = 0;

    while (a >= 0) {
        result += fTree[a];
        a = (a & (a + 1)) - 1;
    }

    return result;
}

void update(int a, int delta, int* fTree, int n) {

    for (; a < n; a = (a | (a + 1)))
        fTree[a] += delta;

}

int main() {
    int n, x, y;
    cin >> n;

    int fTree[X_DIMENSION_SIZE + 1]{ 0 };

    int* rank = new int[n]{ 0 };

    for (int i = 0; i < n; i++) {

        cin >> x >> y;

        rank[sumTo(x, fTree)]++;

        update(x, 1, fTree, X_DIMENSION_SIZE + 1);
    }

    for (int i = 0; i < n; i++)

        cout << rank[i] << endl;

    return 0;
}
