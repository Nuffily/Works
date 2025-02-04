/*
    Problem - https://acm.timus.ru/problem.aspx?space=1&num=1137

    Просто создаем граф из ребер всех маршрутов и создаем по нему Эйлеров путь
*/

#pragma comment(linker, "/STACK:4007772")
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

stack<int> answer;

class Graph {

public:
    int n;

    vector<int> roots[10000];

    Graph(int n) {
        this->n = n;
    }

    Graph() {}

    void euler(int v) {

        int u;

        for (int i = 0; i < roots[v].size(); i++) 
        {
            if (!roots[v].at(i)) continue;

            u = roots[v].at(i);
            roots[v].at(i) = 0;

            for (int j = 0; j < roots[v].size(); j++)
                if (roots[v].at(j) == u) roots[v].at(j) = 0;

            euler(u);
        }

        answer.push(v);
    }

};

int main() {

    Graph graph = Graph();

    int n, m, previous, cur;

    cin >> n;

    for (int i = 0; i < n; i++) {

        cin >> m >> previous;

        for (int j = 0; j < m; j++) {

            cin >> cur;
            graph.roots[previous].push_back(cur);
            previous = cur;
        }
    }

    graph.euler(previous);

    int size = answer.size();
    cout << size - 1 << " ";

    for (int i = 0; i < size; i++) {
        cout << answer.top() << " ";
        answer.pop();
    }

    cout << endl;

    return 0;
}
