/*
  Problem - https://acm.timus.ru/problem.aspx?space=1&num=1069
*/

#include <iostream>
#include <string>
#include <set>

#define MAX_NODES 7500

using namespace std;

class Graph {

public:
    int num;

    set<int> roots[MAX_NODES + 1];

    Graph(int num) {
        this->num = num;
    }

    void reconstruct(int pCode[]) {

        bool used[MAX_NODES + 1]{ false };
        int meter = 1;

        for (int i = 1; i < num; i++) {

            for (int j = 1; j <= num; j++)
                used[j] = false;

            for (int j = 1; j < num; j++)
                used[pCode[j]] = true;

            meter = 1;
            while ((used[meter] == true) and (meter <= num)) meter++;

            roots[pCode[i]].insert(meter);
            roots[meter].insert(pCode[i]);

            pCode[i] = meter;
        }
    }

    void print() {

        for (int i = 1; i < num + 1; i++) {

            cout << i << ": ";

            for (auto j : roots[i])
                cout << j << " ";

            cout << endl;
        }
    }
};

int main() {

    int pCode[MAX_NODES + 1];
    int cur, num = 1;

    while (cin >> cur) 
        pCode[num++] = cur;
    
    Graph graph = Graph(num);
    
    graph.reconstruct(pCode);

    graph.print();

    return 0;
}
