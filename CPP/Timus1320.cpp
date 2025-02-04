/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1320

  Чтобы разбиение существовало, достаточно того, чтобы в каждой компоненте связности было четное число ребер
  
  Собираем граф и запускаем поиск в ширину из каждой точки, которая еще не входила не в один поиск, то есть не была ни в одной проверенной компоненте
  С его помощью находим сумму степеней всех вершин, и если она кратна четырем, то количество ребер - двум
*/

#include <iostream>
#include <vector>
#include <queue>

#define MAX_ROOTS 1000

using namespace std;

bool check[MAX_ROOTS + 1]{ false };

class Graph {

public:
    int n;

    vector<int> root[MAX_ROOTS + 1];

    Graph(int n) {
        this->n = n;
    }

    Graph() {}

    int bfs(int start) {

        queue<int> que;
        que.push(start);
        check[start] = true;

        int current, sum = 0;

        while (!(que.empty())) {

            current = que.front();
            que.pop();

            for (int i = 0; i < root[current].size(); i++) {

                sum++;

                if (!check[root[current].at(i)]) {

                    check[root[current].at(i)] = true;
                    que.push(root[current].at(i));
                }
            }
        }
        return sum;
    }

    void addEdge(int first, int second) {
        root[first].push_back(second);
        root[second].push_back(first);
    }
};

int main() {

    int first, second;

    Graph graph = Graph(MAX_ROOTS + 1);

    while (cin >> first and first != 0) {
        cin >> second;
        graph.addEdge(first, second);
    }

    bool answer = true;

    for (int i = 1; i < 1001; i++) {
        if (!check[i])
            if (graph.bfs(i) % 4) answer = false;
    }

    cout << answer << endl;

    return 0;
}
