/*
  Problem - https://acm.timus.ru/status.aspx?space=1&num=1162&author=365504

  Представляем задачу как направленный граф, где вершины - это валюты, а ребра - точки обмена
  Таким образом, процесс обмена валют представляем как проход по графу

  Для каждой вершины определим число - максимальное количество данной валюты, которое может выменять Ник
  
  С помощью алгоритма Форда-Беллмана находим максимальные значения ко всем вершинам,
*/

#pragma comment(linker, "/STACK:4007772")
#include <iostream>
#include <vector>
using namespace std;

struct Interchange {
    int from;
    int to;
    long double rate;
    long double commision;

    double exchange(double quality) {
        return (quality - commision) * rate;
    }
};

class Graph {

public:

    int n;
    int m;

    vector<Interchange> ex;

    Graph(int n, int m) {
        this->n = n;
        this->m = m;
    }

    Graph() {}

    long double fordBellman(int s, double startQuality) {

        long double* maxPossibleQuality = new long double[n + 1] { 0 }; 

        maxPossibleQuality[s] = startQuality;

        Interchange current;

        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < m; j++) {

                current = ex.at(j);

                if (maxPossibleQuality[current.to] < ex.at(j).exchange(maxPossibleQuality[current.from]))
                    maxPossibleQuality[current.to] = ex.at(j).exchange(maxPossibleQuality[current.from]);
            }

        for (int j = 0; j < m; j++) {
            if (maxPossibleQuality[current.to] < ex.at(j).exchange(maxPossibleQuality[current.from]))
                return startQuality + 1;
        }

        return maxPossibleQuality[s];
    }
};

int main() {
    int n, m, s;
    long double v;
    cin >> n >> m >> s >> v;

    Graph base = Graph(n, m * 2);

    int a, b; 
    long double rab, cab, rba, cba;
    Interchange ab, ba;

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> rab >> cab >> rba >> cba;

        ab = { a, b, rab, cab };
        ba = { b, a, rba, cba };

        base.ex.push_back(ab);
        base.ex.push_back(ba);
    }

    if (base.fordBellman(s, v) > v)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
