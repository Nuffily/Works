/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1450

  Просто алгоритм Форда-Беллмана
*/

#include <iostream>

#define VERY_UNPROFITABLE -999999

using namespace std;

struct Pipeline {
    int from;
    int to;
    int profit;
};

class Graph {

public:
    int n;
    int m;

    vector< pair<int, int> > g[10000];

    Pipeline* edge;

    Graph(int n, int m) {
        this->n = n;
        this->m = m;

        edge = new Pipeline[m + 1];
    }

    Graph() {}

    void addEdge(Pipeline pipe, int i) {
        edge[i] = pipe;
    }

    int fordBellman(int from, int to) {

        int* maxProfit = new int[n + 1];

        for (int i = 1; i <= n; i++)
            maxProfit[i] = VERY_UNPROFITABLE;

        maxProfit[from] = 0;

        for (int z = 1; z < n; z++)
            for (int i = 1; i <= m; i++)
                if (maxProfit[edge[i].to] < maxProfit[edge[i].from] + edge[i].profit)
                    maxProfit[edge[i].to] = maxProfit[edge[i].from] + edge[i].profit;
            
        return maxProfit[to];
    }

};

int main() {

    int n, m, from, to, profit;

    cin >> n >> m;

    Graph graph = Graph(n, m);

    Pipeline pipe;

    for (int i = 1; i <= m; i++) {

        cin >> from >> to >> profit;
        pipe = { from, to, profit };

        graph.addEdge(pipe, i);
    }

    cin >> from >> to;

    int result = graph.fordBellman(from, to);

    if (result <= 0)
        cout << "No solution" << endl;

    else
        cout << result << endl;

    return 0;
}
