/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1379
  Бинарный поиск и алгоритм Дейкстры
*/

#pragma comment(linker, "/STACK:4007772")
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>

#define TIMEBOUND 1440
#define TRUCK_WEIGHT 3000000
#define CUP_WEIGHT 100
#define UNREACHABLE 9999999

using namespace std;

const int inf = 10000000;

struct node {
    int to;
    int time;
    int limit;
};

class graph {

public:
    int n;

    vector<node> g[10000];

    graph(int nn) {
        n = nn;
    }

    graph() {}

    int dijkstra(int start, int finish, int limitation) {

        vector<int> d;
        d.push_back(0);

        for (int i = 1; i <= n; i++)
            d.push_back(UNREACHABLE);

        d[start] = 0;

        set< pair<int, int> > q;
        q.insert({0, start});

        while (!q.empty()) {

            int v = q.begin()->second;
            q.erase(q.begin());

            for (auto [u, t, l] : g[v]) {

                if (l < TRUCK_WEIGHT + CUP_WEIGHT * limitation) continue;

                if (d[u] > d[v] + t) {
                    q.erase({d[u], u});
                    d[u] = d[v] + t;
                    q.insert({d[u], u});
                }
            }
        }

        return d.at(finish);
    }

};

int main() {
    int n, m;

    cin >> n >> m;

    graph base = graph(n);

    int a, b, tim, limi;
    node abEdge, baEdge;

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> tim >> limi;

        abEdge = {b, tim, limi};
        base.g[a].push_back(abEdge);

        abEdge = {a, tim, limi};
        base.g[b].push_back(abEdge);
    }

    int l = 0;
    int r = 10000000;
    int median;


    // С помощью бинарного поиска ищем максимальное число кружек, которое возможно перевести
    // Выбираем число кружек, и ищем наибыстрейший путь с помощью алгоритма Дейскстры
    do {    
        median = (r + l) / 2 + 1;

        if (base.dijkstra(1, n, median) > TIMEBOUND) {
            r = median -1;
        }
        else {
            l = median;
        }

    } while (l != r);

    cout << l << endl;

    return 0;
}
