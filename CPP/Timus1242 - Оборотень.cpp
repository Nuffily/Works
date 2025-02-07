/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1242

  Представляем связь между жителями ввиде графа и используем поиск в ширину

  Однако при таком подходе невиновными также будут засчитываться и множество лишних жителей, например, потомки предка оборотня, даже если они не связаны с ним

  Во избежание этого, создаем два направленных графа - для отображения потомков и предков, и проходимся по обоим поиском в ширину для всех жертв

  Только те, кто попал хоть в один BFS - точно не виновны
*/

#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <string>

using namespace std;

bool* isInnocent;

class Graph {

    int n;
    vector<int>* roots;

public:
    
    Graph(int n) {
        this->n = n;
        roots = new vector<int>[n + 1];
    }

    Graph() {}

    void addEdge(int from, int to) {
        roots[from].push_back(to);
    }

    void bfs(int victim) {

        queue<int> que;
        que.push(victim);

        isInnocent[victim] = true;
        int suspect;

        while (!(que.empty())) {

            suspect = que.front();
            que.pop();

            for (int i = 0; i < roots[suspect].size(); i++)

                if (!isInnocent[roots[suspect].at(i)]) {
                    isInnocent[roots[suspect].at(i)] = true;
                    que.push(roots[suspect].at(i));
                }
        }
    }
};

void printSuspectList(int n) {

    bool atLeastOne = false;

    for (int i = 1; i < n + 1; i++)
        if (!isInnocent[i]) {
            cout << i << " ";
            atLeastOne = true;
        }

    if (!(atLeastOne)) cout << 0;

    cout << endl;
}

int main() {
    int n, child, parent;
    string input;
    cin >> n;

    isInnocent = new bool[n + 1] { false };

    Graph descendants = Graph(n);
    Graph ancestors = Graph(n);

    while (true) {

        cin >> input;

        if (input == "BLOOD") break;
        else child = stoi(input);

        cin >> parent;

        descendants.addEdge(parent, child);
        ancestors.addEdge(child, parent);
    }

    int victim;

    while (cin >> victim) {
        ancestors.bfs(victim);
        descendants.bfs(victim);
    }

    printSuspectList(n);

    return 0;
}
