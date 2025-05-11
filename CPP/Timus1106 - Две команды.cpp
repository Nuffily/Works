/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1106

  Представляем задачу ввиде графа. Вершины - люди, ребра - "друзья".

  Далее запускаем процесс, похожий на разбиение на две доли, с помощью поиска в ширину.
  Ну, и раз уж у каждого есть хоть один друг, нужное разбиение всегда будет существовать
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class Graph {

    int n;
    vector<int>* people;
    int* team;

public:

    Graph(int n) {
        this->n = n;
        people = new vector<int>[n + 1];
        this->team = new int[n + 1] {0};
    }

    void add(int first, int second) {
        people[first].push_back(second);
        people[second].push_back(first);
    }

    void fractingBFS(int start) {
        
        queue<int> que;

        if (!team[start]) {
            que.push(start);
            team[start] = 1;
        }

        int cur, next;

        while (!que.empty()) {
            cur = que.front();
            que.pop();

            for (int i = 0; i < people[cur].size(); i++) {
                next = people[cur].at(i);

                if (team[next] == 0) {
                    que.push(next);
                    team[next] = team[cur] * 2 % 3;
                }
            }
        }
    }

    int* getResult() {
        return team;
    }

    int getCountInTheFirstTeam() {
        int count = 0;
        for (int i = 1; i <= n; i++) 
            if (team[i] % 2)
                count++;
        return count;
    }
};



int main() {

    int n, cur;

    cin >> n;

    Graph graph = Graph(n);

    for (int i = 1; i <= n; i++)
        while (cin >> cur) {
            if (!cur) break;
            graph.add(i, cur);
        }

    for (int i = 1; i <= n; i++) {
        graph.fractingBFS(i);
    }

    int* team = graph.getResult();

    cout << graph.getCountInTheFirstTeam() << endl;

    for (int i = 1; i <= n; i++) 
        if (team[i] % 2)
            cout << i << " ";

    cout << endl;

    return 0;
}
